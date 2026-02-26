#include <stdio.h>
#include "types.h"
#include <string.h>
#include "edit.h"
#include "view.h"
#include <stdlib.h>

/*-----------------------------------------------------------
  Function : read_and_validate_edit
  Purpose  : Validate user input for editing operation
------------------------------------------------------------*/
Status read_and_validate_edit(char *argv[], Edit *edit, int argc)
{
    /* Minimum arguments check */
    if (argc < 5)
    {
        printf("ERROR: Insufficient arguments\n");
        return e_failure;
    }

    /* Map user option to ID3 frame ID */
    if (strcmp(argv[2], "-t") == 0)
        strcpy(edit->editing, "TIT2");
    else if (strcmp(argv[2], "-y") == 0)
        strcpy(edit->editing, "TYER");
    else if (strcmp(argv[2], "-a") == 0)
        strcpy(edit->editing, "TALB");
    else if (strcmp(argv[2], "-A") == 0)
        strcpy(edit->editing, "TPE1");
    else if (strcmp(argv[2], "-c") == 0)
        strcpy(edit->editing, "COMM");
    else if (strcmp(argv[2], "-g") == 0)
        strcpy(edit->editing, "TCON");
    else
    {
        printf("ERROR: Unsupported edit option\n");
        return e_failure;
    }

    /* Validate new data */
    if (argv[3] == NULL)
    {
        printf("ERROR: New data not provided\n");
        return e_failure;
    }
    strcpy(edit->new_data, argv[3]);

    /* Validate MP3 file */
    if (argv[4] == NULL || strstr(argv[4], ".mp3") == NULL)
    {
        printf("ERROR: Invalid MP3 file\n");
        return e_failure;
    }

    edit->audio_file_name = argv[4];

    return e_success;
}

/*-----------------------------------------------------------
  Function : open_file
  Purpose  : Open original MP3 and temporary file
------------------------------------------------------------*/
Status open_file(Edit *edit)
{
    /* Open original file in binary read mode */
    edit->fptr_audio = fopen(edit->audio_file_name, "rb");
    if (edit->fptr_audio == NULL)
    {
        perror("ERROR opening audio file");
        return e_failure;
    }

    /* Create temporary file in binary write mode */
    edit->temp_file_name = "temp.mp3";
    edit->fptr_temp = fopen(edit->temp_file_name, "wb");
    if (edit->fptr_temp == NULL)
    {
        perror("ERROR opening temp file");
        return e_failure;
    }

    return e_success;
}

/*-----------------------------------------------------------
  Function : copy_header_bytes
  Purpose  : Copy first 10 bytes (ID3 header)
------------------------------------------------------------*/
Status copy_header_bytes(Edit *edit, int size)
{
    char buffer[10];

    if (fread(buffer, size, 1, edit->fptr_audio) != 1)
        return e_failure;

    if (fwrite(buffer, size, 1, edit->fptr_temp) != 1)
        return e_failure;

    return e_success;
}

/*-----------------------------------------------------------
  Function : edit_new_data
  Purpose  : Parse frames and edit selected frame
------------------------------------------------------------*/
Status edit_new_data(Edit *edit)
{
    char tag[5];
    int original_size;
    int size;
    char flag[3];

    /* Loop through frames */
    while (fread(tag, 4, 1, edit->fptr_audio) == 1)
    {
        tag[4] = '\0';

        /* Read frame size */
        fread(&original_size, 4, 1, edit->fptr_audio);
        size = original_size;
        endianess(&size, 4);   // Convert Big Endian → Little Endian

        /* Read flags */
        fread(flag, 3, 1, edit->fptr_audio);

        /* Allocate memory for frame data */
        char *data = malloc(size);
        if (data == NULL)
        {
            printf("Memory allocation failed\n");
            return e_failure;
        }

        fread(data, size - 1, 1, edit->fptr_audio);
        data[size - 1] = '\0';

        /* If current tag matches requested tag */
        if (strcmp(tag, edit->editing) == 0)
        {
            /* Write frame ID */
            fwrite(tag, 4, 1, edit->fptr_temp);

            /* Calculate new size */
            int new_size = strlen(edit->new_data) + 1;
            int new_size_be = new_size;
            endianess(&new_size_be, 4);   // Convert back to Big Endian

            /* Write updated size */
            fwrite(&new_size_be, 4, 1, edit->fptr_temp);

            /* Write flags */
            fwrite(flag, 3, 1, edit->fptr_temp);

            /* Write new data */
            fwrite(edit->new_data, new_size - 1, 1, edit->fptr_temp);

            free(data);
            break;  // Exit loop after editing
        }
        else
        {
            /* Copy frame as it is */
            fwrite(tag, 4, 1, edit->fptr_temp);
            fwrite(&original_size, 4, 1, edit->fptr_temp);
            fwrite(flag, 3, 1, edit->fptr_temp);
            fwrite(data, size - 1, 1, edit->fptr_temp);
        }

        free(data);
    }

    /* Copy remaining file content */
    char buffer;
    while (fread(&buffer, 1, 1, edit->fptr_audio) == 1)
    {
        fwrite(&buffer, 1, 1, edit->fptr_temp);
    }

    /* Close files */
    fclose(edit->fptr_audio);
    fclose(edit->fptr_temp);

    /* Replace original file safely */
    remove(edit->audio_file_name);
    rename("temp.mp3", edit->audio_file_name);

    return e_success;
}

/*-----------------------------------------------------------
  Function : do_edit_operation
  Purpose  : Main editing controller
------------------------------------------------------------*/
Status do_edit_operation(Edit *edit)
{
    if (open_file(edit) == e_failure)
        return e_failure;

    if (copy_header_bytes(edit, 10) == e_failure)
        return e_failure;

    if (edit_new_data(edit) == e_failure)
        return e_failure;

    printf("Editing successfully completed\n");

    return e_success;
}