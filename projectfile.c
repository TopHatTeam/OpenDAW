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
#include "headers/Common.h"

bool create_project_file(const char* filepath)
{

    FILE* file;
    file = fopen(filepath, "wb");

    if (file == NULL)
    {
        printf("Failed to create file at: %s\n", filepath);
        fclose(file);
        return false;
    }
    
    struct project_file_t output_file = { 
        .header = { "ashley" } 
    };

    if (fwrite(&output_file, sizeof output_file, 1, file) != 1)
    {
        printf("Failed to write to file at: %s\n", filepath);
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}

project_file_t* read_project_file(const char* filepath)
{
    /* Create the pointer to the file*/
    FILE* file; 
    
    /*Let's open the binary to this file*/
    file = fopen(filepath, "rb");

    /* Checking to see if file is NULL in that case we return false*/
    if (!file)
    {
        printf("Failed to read file: %s\n", filepath);
        fclose(file);
        return NULL;
    }

    /* creating a local 7-byte charater buffer */
    char buffer[7];

    /* use use fread because it's binary. Only use fgets for non-binary text
        we're checking if it's 7 bytes and check if it says the secret code word 'ashley'
    */
    if (fread(buffer, 1, 7, file) != 7 || memcmp(buffer, "ashley", 7) != 0)
    {   
        printf("Failed to find identifier in specified file: %s\n", filepath);
        fclose(file);
        return NULL;
    }

    /* we need to allocate memory here because we're need to keep this information
        into memory
    */
    project_file_t* pfile = malloc(sizeof *pfile);
    if (!pfile)
    {
        printf("Failed to allocate memory for project file information at: %s\n", filepath);
        fclose(file);
        return NULL;
    }


    /* next we need to allocate memory for header information*/
    pfile->header = malloc(sizeof *pfile);
    if (!pfile->header)
    {
        printf("Failed to allocate memory for header information at: %s\n", filepath);
        free(pfile); /* so we don't create a memory leak*/
        fclose(file);
        return NULL;
    }

    /* Only way to modify a char array and safer because we know the array size*/
    strncpy(pfile->header->identifier, "ashley", sizeof(pfile->header->identifier));
    pfile->header->identifier[sizeof(pfile->header->identifier)-1] = '\0';

    /* We close the file before returning true*/
    fclose(file);
    return pfile;
}
