// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//  Created by Andrew Skatzes on 8/19/25.
//  projectfile.hpp
//
//  Description:
//      the project file header structure
//
// ---------------------------------------------------------

#include "headers/projectfile.h"

bool create_project_file(const char* filepath)
{

    FILE* file;
    file = fopen(filepath, "wb");

    if (file == NULL)
    {
        printf("Failed to create file at: %s\n", filepath);
        return false;
    }

    fclose(file);
    return true;
}

bool read_project_file(const char* filepath, project_file_t ptr)
{
    /* Create the pointer to the file*/
    FILE* file; 
    
    /*Let's open the binary to this file*/
    file = fopen(filepath, "rb");

    /* Checking to see if file is NULL in that case we return false*/
    if (file == NULL)
    {
        printf("Failed to read file: %s\n", filepath);
        return false;
    }

    /* creating a local 6-byte charater buffer */
    char buffer[6];

    /* use use fread because it's binary. Only use fgets for non-binary text
        we're checking if it's 6 bytes and check if it says the secret code word 'ashley'
    */
    if (fread(buffer, 1, 6, file) != 6 && memcmp(buffer, "ashley", 6) != 0)
    {   
        printf("Failed to find identifier in specified file: %s\n", filepath);
        return false;
    }

    /* We close the file before returning true*/
    fclose(file);
    return true;
}
