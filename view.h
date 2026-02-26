#include <stdio.h>
#include "types.h"

/*-----------------------------------------------------------
  Structure : view
  Purpose   : Stores data required for viewing MP3 metadata
------------------------------------------------------------*/
typedef struct
{
    /* Stores source MP3 file name */
    char *src_audio_fname;

    /* File pointer for MP3 file */
    FILE *fptr_audio_fname;

} view;

/*-----------------------------------------------------------
  Function : read_and_validate_view
------------------------------------------------------------*/
Status read_and_validate_view(char *argv[] , view *view_info);

/*-----------------------------------------------------------
  Function : open_files
------------------------------------------------------------*/
Status open_files(view *view_info);

/*-----------------------------------------------------------
  Function : skip_header
------------------------------------------------------------*/
Status skip_header(view *view_info);

/*-----------------------------------------------------------
  Function : endianess
------------------------------------------------------------*/
void endianess(void *ptr, int size);

/*-----------------------------------------------------------
  Function : do_view
------------------------------------------------------------*/
Status do_view(view *view_info);

/*-----------------------------------------------------------
  Function : print
------------------------------------------------------------*/
Status print(char *tag , char *data);