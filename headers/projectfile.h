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
    char* identifier[6]     // the specific identifier for the file header
} file_header_t;

typedef struct project_file_t
{
    file_header_t* header;
} project_file_t;

bool create_project_file(const char* filepath);

/**
 * @brief This function reads the project file and loads it into memory
 * @param filepath The path to where the file is located
 * @param ptr A pointer to project_file_t structure
 * @returns True if we successfully read the file and false if otherwise
 */
bool read_project_file(const char* filepath, project_file_t* ptr);

#ifdef __cplusplus
}
#endif

#endif