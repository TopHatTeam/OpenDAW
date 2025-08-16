// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//  Created by Andrew Skatzes on 8/16/25.
//  rustlib.h
//
//  Description:
//      Includes the definitions for Rust bindings to C
//
// ---------------------------------------------------------

#ifndef RUSTLIB_H
#define RUSTLIB_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif 

// -- Macros -- 
#define STRINGIFY(x) #x 
#define TOSTRING(x) STRINGIFY(x)

#define RUSTLIB_VERSION(x, y, z) TOSTRING(x) "." TOSTRING(y) "." TOSTRING(z) 


// -- Rust bindings definitions --

int32_t read_cd_sector(const char* device_path, uint32_t sector, uint8_t* buffer);

#ifdef __cplusplus 
}
#endif

#endif 