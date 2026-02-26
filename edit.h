#include <stdio.h>
#include "types.h"

/*-----------------------------------------------------------
  Structure : Edit
  Purpose   : Stores all information required for editing
              MP3 metadata (ID3 tags)
------------------------------------------------------------*/
typedef struct _Edit_data
{
    /* Stores the frame ID to be edited 
       Example: TIT2, TALB, TPE1 etc. */
    char editing[5];         

    /* Stores the new metadata value provided by user */
    char new_data[50];       

    /* Stores original MP3 file name */
    char *audio_file_name;   

    /* File pointer for original MP3 file */
    FILE *fptr_audio;
    
    /* Stores temporary file name */
    char *temp_file_name;    

    /* File pointer for temporary MP3 file */
    FILE *fptr_temp;

} Edit;

/*-----------------------------------------------------------
  Function : check_operation
------------------------------------------------------------*/
OperationType check_operation(char *argv[]);

/*-----------------------------------------------------------
  Function : read_and_validate_edit
------------------------------------------------------------*/
Status read_and_validate_edit(char *argv[], Edit *edit, int argc);

/*-----------------------------------------------------------
  Function : do_edit_operation
------------------------------------------------------------*/
Status do_edit_operation(Edit *edit);

/*-----------------------------------------------------------
  Function : open_file
------------------------------------------------------------*/
Status open_file(Edit *edit);

/*-----------------------------------------------------------
  Function : copy_header_bytes
------------------------------------------------------------*/
Status copy_header_bytes(Edit *edit, int size);

/*-----------------------------------------------------------
  Function : edit_new_data
------------------------------------------------------------*/
Status edit_new_data(Edit *edit);