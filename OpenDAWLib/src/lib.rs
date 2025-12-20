// ---------------------------------------------------------
//
//  OpenDAW
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      Rust driver support for OpenDAW
//
// ---------------------------------------------------------

// I know this file has a shit ton of comments but it's useful for me to remember how rust works

mod cd;

use std::os::raw::{c_char};
use std::u8;


// Third-party dependencies

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

#[repr(C)]
pub struct Track<'a> 
{
    pub data: &'a [u8],
    pub size: usize,
}

#[repr(C)]
pub struct AudioCD 
{
    tracks: Vec<Track<'static>>,
}

pub fn add(left: u64, right: u64) -> u64 {
    left + right
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


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
}