// ---------------------------------------------------------
//
//  OpenDAW
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      Includes the definitions for Rust bindings to C
//
// ---------------------------------------------------------

#ifndef RUSTLIB_H
#define RUSTLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif 

// -- Macros -- 
#define STRINGIFY(x) #x 
#define TOSTRING(x) STRINGIFY(x)

#define RUSTLIB_VERSION(x, y, z) TOSTRING(x) "." TOSTRING(y) "." TOSTRING(z) 

// -- Struct binding definitions --

typedef struct Buffer;
typedef struct Command;
typedef struct BurnTocEntry;
typedef struct Isrc;
typedef struct BurnCDText;
typedef struct BurnSource;
typedef struct BurnSession;
typedef struct BurnTrack;
typedef struct BurnDisc;
typedef struct BurnFormatDescr;
typedef struct BurnFeatureDescr;
typedef struct BurnDrive;

// -- Enum binding defintions --

typedef enum BurnDiscStatus;

// -- Rust bindings definitions --

BurnDrive* safe_burn_drive_new();

/**
 * @brief This function frees the memory of heap used by the struct "BurnDrive" 
 * @note This function is declared in "cd.rs" and called from that rust library
 * @param ptr Pointer to the BurnDrive struct
 * @returns void
 */
void safe_burn_drive_free(struct BurnDrive* ptr);

/**
 * @brief 
 */
const char* safe_burn_drive_name(const struct BurnDrive* ptr);

void safe_burn_drive_string_free(char* ptr);

int32_t read_cd_sector(const char* device_path, uint32_t sector, uint8_t* buffer);

#ifdef __cplusplus 
}
#endif

#endif 