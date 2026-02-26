/* Project Title   : MP3 Tag Reader and Editor
   Name            : YDNS PAVAN
   Batch ID        : 25036A+39

    ------------------------------------------------------------------------
    Project Description:
    ------------------------------------------------------------------------
    This project is a command-line based MP3 Tag Reader and Editor.
    It allows the user to view and modify metadata (ID3 tags) 
    stored inside an MP3 file.

    The program reads MP3 files in binary mode and extracts
    information such as:
        - Title
        - Artist
        - Album
        - Year
        - Genre
        - Comment

    The user can also edit these fields safely using a temporary file
    mechanism to avoid corruption of the original MP3 file. 
    
    Resources Used:
    
    - C Programming
    - Structures
    - File Handling (Binary Mode)
    - Command Line Arguments
    - Dynamic Memory Allocation
    - Endian Conversion
    */

#include <stdio.h>
#include "types.h"
#include <string.h>
#include "view.h"
#include "edit.h"

/* Function to identify operation type from command line */
OperationType check_operation_type(char *argv[]);

int main(int argc, char *argv[])
{
    /* Check for minimum required arguments */
    if (argc < 2)
    {
        printf("ERROR: Insufficient Arguments\n");
        return e_failure;
    }

    /* Determine operation type (-v / -e / -h) */
    OperationType op_type = check_operation_type(argv);

    /* -------------------- VIEW OPERATION -------------------- */
    if (op_type == e_view)
    {
        view view_info;   // Structure to hold viewing related data

        /* Validate input file */
        if (read_and_validate_view(argv, &view_info) == e_success)
        {
            /* Perform viewing of ID3 tags */
            if (do_view(&view_info) == e_success)
                return e_success;
            else
                return e_failure;
        }
        else
        {
            printf("ERROR: View validation failed\n");
            return e_failure;
        }
    }

    /* -------------------- EDIT OPERATION -------------------- */
    else if (op_type == e_edit)
    {
        Edit edit;   // Structure to hold editing related data

        printf(":::::::::::: Editing Mode Selected ::::::::::::\n");

        /* Validate edit arguments */
        if (read_and_validate_edit(argv, &edit, argc) == e_success)
        {
            /* Perform edit operation */
            if (do_edit_operation(&edit) == e_success)
                return e_success;
            else
                return e_failure;
        }
        else
        {
            printf("ERROR: Edit validation failed\n");
            return e_failure;
        }
    }

    /* -------------------- HELP OPERATION -------------------- */
    else if (op_type == e_help)
    {
        printf("\nUsage Instructions:\n");
        printf("\nFor viewing  : ./a.out -v <file.mp3>\n");
        printf("For editing  : ./a.out -e <operation> <data_to_update> <file.mp3>\n");

        printf("\nAvailable edit options:\n");
        printf("\t-t : Edit Title\n");
        printf("\t-y : Edit Year\n");
        printf("\t-a : Edit Album\n");
        printf("\t-A : Edit Artist\n");
        printf("\t-c : Edit Comment\n");
        printf("\t-g : Edit Genre\n");

        printf("\n(Note: Use double quotes for text data)\n");
        return e_success;
    }

    /* -------------------- UNSUPPORTED OPTION -------------------- */
    else
    {
        printf("ERROR: Unsupported arguments\n");
        printf("\nUse -h for help\n");
        return e_failure;
    }
}

/*-----------------------------------------------------------
  Function : check_operation_type
  Purpose  : Identify operation based on user input
------------------------------------------------------------*/
OperationType check_operation_type(char *argv[])
{
    /* Compare second argument with supported options */

    if (strcmp(argv[1], "-v") == 0)
        return e_view;

    else if (strcmp(argv[1], "-e") == 0)
        return e_edit;

    else if (strcmp(argv[1], "-h") == 0)
        return e_help;

    else
        return e_unsupported;
}