#include<stdio.h>
#include"types.h"
#include"view.h"
#include<string.h>

/*-----------------------------------------------------------
  Function : read_and_validate_view
  Purpose  : Validate MP3 file before viewing operation
------------------------------------------------------------*/
Status read_and_validate_view(char *argv[] , view *view_info)
{
    /* Check if audio file argument is provided */
    if(argv[2] == NULL)
    {
        printf("No Audio file exits\n");
        return e_failure;
    }

    /* Validate file extension (.mp3) */
    int len = strlen(argv[2]);
    if(len < 4 || strcmp(&argv[2][len - 4], ".mp3") != 0)
    {
        printf("Audio file extension in not valid!\n");
        return e_failure;
    }

    /* Store audio file name into structure */
    view_info->src_audio_fname = argv[2];

    return e_success;
}

/*-----------------------------------------------------------
  Function : open_files
  Purpose  : Open MP3 file in binary read mode
------------------------------------------------------------*/
Status open_files(view *view_info)
{
    /* Open file in binary read mode */
    view_info->fptr_audio_fname = fopen(view_info->src_audio_fname, "rb");

    /* Check if file opened successfully */
    if(view_info->fptr_audio_fname == NULL)
    {
        perror("fopen");
        fprintf(stderr,"Error : Unable to open file %s\n", view_info->src_audio_fname);
        return e_failure;
    }

    return e_success;
}

/*-----------------------------------------------------------
  Function : skip_header
  Purpose  : Skip first 10 bytes (ID3 header)
------------------------------------------------------------*/
Status skip_header(view *view_info)
{
    /* ID3v2 header size is fixed 10 bytes */
    fseek(view_info->fptr_audio_fname, 10 , SEEK_SET);

    return e_success;
}

/*-----------------------------------------------------------
  Function : do_view
  Purpose  : Read and display MP3 metadata
------------------------------------------------------------*/
Status do_view(view *view_info)
{
    /* Open file */
    if(open_files(view_info) == e_failure)
    {
        printf("Failed to open file!\n");
        return e_failure;
    }

    /* Read first 3 bytes to verify ID3 version */
    char version[4]; 
    fread(version, 3, 1, view_info->fptr_audio_fname);
    version[3] = '\0';

    /* Skip ID3 header */
    if(skip_header(view_info) == e_failure)
    {
        printf("ERROR : ");
        return e_failure;
    }

    /* Print heading */
    printf("----------------------------------------------\n");
    printf("\t          SONG INFO              \n");
    printf("----------------------------------------------\n");

    /* Loop to extract 6 important metadata frames */
    for(int i = 0; i < 6; )
    {
        char buff[5];           // To store Frame ID (e.g., TIT2)
        unsigned int size = 0;  // To store frame size

        /* Read Frame ID (4 bytes) */
        fread(buff, 1, 4, view_info->fptr_audio_fname);
        buff[4] = '\0';

        /* Read frame size (4 bytes) */
        fread(&size, 1, 4, view_info->fptr_audio_fname);

        /* Convert Big Endian to Little Endian */
        endianess(&size, 4);

        /* Skip 3 bytes (flags + encoding) */
        fseek(view_info->fptr_audio_fname, 3, SEEK_CUR);

        /* Allocate space for metadata text */
        char data[size];

        /* Read actual metadata */
        fread(data, size - 1, 1, view_info->fptr_audio_fname);
        data[size - 1] = '\0';

        /* Print only if frame is one of required tags */
        if(print(buff, data) == e_success)
            i++;
    }

    printf("----------------------------------------------\n");

    return e_success;
}

/*-----------------------------------------------------------
  Function : endianess
  Purpose  : Convert Big Endian to Little Endian
------------------------------------------------------------*/
void endianess(void *ptr , int size)
{
    char *cptr = (char *)ptr;

    /* Reverse byte order */
    for(int i = 0; i < size/2; i++)
    {
        char temp = cptr[i];
        cptr[i] = cptr[size - 1 - i];
        cptr[size - 1 - i] = temp;
    }
}

/*-----------------------------------------------------------
  Function : print
  Purpose  : Print metadata based on Frame ID
------------------------------------------------------------*/
Status print(char *tag , char *data)
{
    /* Compare frame ID and print corresponding field */

    if (strcmp(tag, "TIT2") == 0)
        printf("TITLE\t:\t%s\n", data);

    else if (strcmp(tag, "TYER") == 0)
        printf("YEAR\t:\t%s\n", data);

    else if (strcmp(tag, "TALB") == 0)
        printf("ALBUM\t:\t%s\n", data);

    else if (strcmp(tag, "TPE1") == 0)
        printf("ARTIST\t:\t%s\n", data);

    else if (strcmp(tag, "COMM") == 0)
        printf("COMMENT\t:\t%s\n", data);

    else if (strcmp(tag, "TCON") == 0)
        printf("GENRE\t:\t%s\n", data);

    else
        return e_failure;

    return e_success;
}