// ---------------------------------------------------------
//
//  OpenDAW
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      the project file header structure
//
// ---------------------------------------------------------

#ifndef PROJECTFILE_H
#define PROJECTFILE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#if defined(__linux__)

    #include <unistd.h>

#elif defined(_WIN32)

#endif

typedef struct file_header_t
{
    char* identifier[7];     // the specific identifier for the file header
} file_header_t;

typedef struct project_file_t
{
    file_header_t* header;
} project_file_t;

bool create_project_file(const char* filepath);

/**
 * @brief This function reads the project file and loads it into memory
 * @param filepath The path to where the file is located
 * @returns The project_file_t pointer
 */
project_file_t* read_project_file(const char* filepath);

#ifdef __cplusplus
}
#endif

#endif