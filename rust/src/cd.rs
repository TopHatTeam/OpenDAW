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

unsafe extern "C" 
{
    unsafe fn burn_initialize() -> i32;
    unsafe fn burn_drive_scan() -> i32;
    unsafe fn burn_drive_open(dev_path: *const c_char) -> *mut std::ffi::c_void;
    unsafe fn burn_disc_create() -> *mut std::ffi::c_void;
    unsafe fn burn_track_append_data(disc: *mut std::ffi::c_void, data: *const u8, size: usize) -> i32;
    unsafe fn burn_disc_write(disc: *mut std::ffi::c_void) -> i32; 
    unsafe fn burn_drive_close(drive: *mut std::ffi::c_void);
    unsafe fn burn_finalize();
}

pub struct Track<'a> 
{
    pub data: &'a [u8],
    pub size: usize,
}

pub struct AudioCD 
{
    tracks: Vec<Track<'static>>,
}

impl AudioCD 
{
    pub fn new() -> Self 
    {
        Self { tracks: Vec::new() }
    }

    pub fn add_tracks(&mut self, track: Track<'static>)
    {
        self.tracks.push(track);
    }

    pub unsafe fn burn(&self, device_path: &str) -> i32 
    {
        /* WE NEED TODO THE FOLLOWING 
        1. initalize libburn
        2. open device_path
        3. create new session
        4. append tracks
        5. burn disc
        6. finalize
        */

        if burn_initialize() != 0 
        {
            return -1;
        }

        if burn_drive_scan() != 0 
        {
            return -2;
        }

        let c_device = std::ffi::CString::new(device_path).unwrap();
        let drive = burn_drive_open(c_device.as_ptr());

        if drive.is_null()
        {
            return -3;
        }

        let disc = burn_disc_create();
        if disc.is_null()
        {
            burn_drive_close(drive);
            return -4;
        }

        for track in &self.tracks 
        {
            if burn_track_append_data(disc, track.data.as_ptr(), track.size) != 0 
            {
                burn_drive_close(drive);
                return -5;
            }
        }

        if burn_disc_write(disc) != 0 
        {
            burn_drive_close(drive);
            return -6;
        }

        println!("Burning {} track(s) to {}", self.tracks.len(), device_path);

        burn_drive_close(drive);
        burn_finalize();
        
        0
    }
}

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
