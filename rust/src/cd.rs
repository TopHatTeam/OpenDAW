// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//  Created by Andrew Skatzes on 8/15/25.
//  cd.rs
//
//  Description:
//      CD SUPPORT 
//
// ---------------------------------------------------------

use std::fs::File;
use std::io::{Read, Seek, SeekFrom};
use std::os::raw::{c_char, c_uint};
use std::ffi::CStr;
use std::u8;
use std::ptr;

const CD_SAMPLERATE: usize          = 44100;
const CD_CHANNELS: usize            = 2;
const CD_BITDEPTH: usize            = 16;
const CD_SAMPLES_PER_SECTOR: usize  = 588;
const CD_SECTOR_SIZE: usize         = CD_SAMPLES_PER_SECTOR * (CD_BITDEPTH / 8) * CD_CHANNELS;

#[no_mangle]
pub unsafe extern "C" fn read_cd_sector(        /* God damn that's a mouth full */
    device_path: *const c_char,
    sector: c_uint,
    buffer: *mut u8
) -> i32 
{
    if device_path.is_null() || buffer.is_null()
    {
        return -1; // Invalid arguments
    }

    let path_cstr = unsafe {CStr::from_ptr(device_path)};
    let path_str = match path_cstr.to_str()
    {
        Ok(s) => s,
        Err(_) => return -2,
    };

    match File::open(path_str)
    {
        Ok(mut file) => 
        {
            let offset = sector as u64 * CD_SECTOR_SIZE as u64;
            if let Err(_) = file.seek(SeekFrom::Start(offset))
            {
                return -3;
            }
        
            let buf_slice = unsafe { std::slice::from_raw_parts_mut(buffer, CD_SECTOR_SIZE)};
            if let Err(_) = file.read_exact(buf_slice)
            {
            return -4;
            }
            0
        }   
        Err(_) => -5,
    }
}

#[no_mangle]
pub unsafe extern "C" fn burn_cd(
    device_path: *const c_char,
    buffer: *const u8,
    size: c_uint
) -> i32 
{
    if device_path.is_null() || buffer.is_null()
    {
        return -1; // NOPE NOT ALLOWED because i said so
    }

    /* We have to say unsafe like we're letting our parents know we're leaving */
    let path_cstr = unsafe {CStr::from_ptr(device_path)};
    let path_str = match path_cstr.to_str()
    {
        Ok(s) => s,
        Err(_) => return -2,
    };

    // We need to implement CD Burning here

    println!("Burning {} bytes to device: {}", size, path_str);

    0
}