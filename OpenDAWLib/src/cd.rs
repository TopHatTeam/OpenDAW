// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//  Created by Andrew Skatzes on 8/16/25.
//  cd.rs
//
//  Description:
//      Rust CD support
//
// ---------------------------------------------------------

use std::fs::File;
use std::io::{Read, Seek, SeekFrom};
use std::os::raw::{c_char, c_uint};
use std::ffi::CStr;
use std::u8;
use std::ptr;
use libc::{pthread_mutex_t, off_t};

/*
    basically rewritting libburn to Rust... i must hate my self
*/

pub const CD_SAMPLERATE: usize              = 44100;
pub const CD_CHANNELS: usize                = 2;
pub const CD_BITDEPTH: usize                = 16;
pub const CD_SAMPLES_PER_SECTOR: usize      = 588;
pub const CD_SECTOR_SIZE: usize             = CD_SAMPLES_PER_SECTOR * (CD_BITDEPTH / 8) * CD_CHANNELS;
pub const LIBBURN_PACK_NUM_TYPES: usize     = 0x10;

#[repr(C)]
pub struct BurnTocEntry 
{

}

#[repr(C)]
pub struct Isrc 
{
    pub has_isrc: c_int,
    pub country: [c_char; 2],
    pub owner: [c_char; 3],
    pub year: c_uchar,
    pub serial: c_uint,
}

#[repr(C)]
pub struct BurnCDText
{
    pub payload: [*mut c_uchar; LIBBURN_PACK_NUM_TYPES],
    pub length: [c_int; LIBBURN_PACK_NUM_TYPES],
    pub flags: c_int,
}

#[repr(C)]
pub struct BurnSource
{

}

#[repr(C)]
pub struct BurnSession
{

}

#[repr(C)]
pub struct BurnTrack 
{
    pub refcnt: c_int,
    pub entry: *mut BurnTocEntry,
    pub indices: c_uchar,
    /* lba address of the index. CD only. 0x7fffffff means undefined index.
	   To be programmed relative to track source start before burning,
           but to hold absolute addresses after burning or reading.
	*/
    pub index: [c_int; 100],
    pub offset: c_int,
    pub offsetcount: c_int,
    pub tail: c_int,
    pub tailcount: c_int,
    pub pad: c_int,
    pub fill_up_media: c_int,
    pub default_size: off_t,
    pub source: *mut BurnSource,
    pub eos: c_int,
    pub sourcecount: off_t,
    pub writecount: off_t,
    pub written_sectors: off_t,
    pub open_ended: c_int,
    pub track_data_done: c_int,
    pub end_on_premature_eoi: c_int,
    pub mode: c_int,
    pub pregap1: c_int,
    pub pregap2: c_int,
    pub pregap2_size: c_int,
    pub postgap: c_int,
    pub postgap_size: c_int,
    pub isrc: Isrc,
    pub swap_source_bytes: c_int,
    pub cdxa_conversion: c_int,
    pub cdtext: [*mut BurnCDText; 8],
}

#[repr(C)]
pub struct BurnDisc 
{
    pub sessions: c_int,
    pub session: *mut *mut BurnSession,
    pub refcnt: c_int,

    /* #ifdef libburn_disc_with_incomplete_session */

    #[cfg(feature = "libburn_disc_with_incomplete_session")]
    pub incomplete_sessions: c_int,

    /* #endif */
}

#[repr(C)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum BurnDiscStatus
{
    /* The current status is not yet know */
    BurnDiscUnready     = 0,

    /*  The drive holds a blank disc. It is ready for writing from scratch.
	    Unused multi-session media:
	      CD-R, CD-RW, DVD-R, DVD-RW, DVD+R, BD-R
	    Blanked multi-session media (i.e. treated by burn_disc_erase())
	      CD-RW, DVD-RW
	    Overwriteable media with or without valid data
	      DVD-RAM, DVD+RW, formatted DVD-RW, BD-RE
	*/
    BurnDiscBlank       = 1,

    /* There is no disc at all in the drive*/
    BurnDiscEmpty       = 2,

    /*  There is an incomplete disc in the drive. It is ready for appending
	    another session.
	    Written but not yet closed multi-session media
	      CD-R, CD-RW, DVD-R, DVD-RW, DVD+R, BD-R
	*/
    BurnDiscAppendable  = 3,

    /*  There is a disc with data on it in the drive. It is usable only for
	    reading.
	    Written and closed multi-session media
	      CD-R, CD-RW, DVD-R, DVD-RW, DVD+R, BD-R
	    Read-Only media
	      CD-ROM, DVD-ROM, BD-ROM
	    Note that many DVD-ROM drives report any written media
	    as Read-Only media and not by their real media types.
	*/
    BurnDiscFull        = 4,

    /* ts A61007 */
        /* @since 0.2.4 */
	/* The drive was not grabbed when the status was inquired */
    BurnDiscUngrabbed   = 5,

    /* ts A61020 */
        /* @since 0.2.6 */
	/* The media seems to be unsuitable for reading and for writing */
    BurnDiscUnsuitable  = 6,

    /* Safeguard here just encase something bad happens */
    BurnDiscUndefined   = 7,
}

#[repr(C)]
pub struct BurnFormatDescr
{
    pub type_f: c_int,
    pub size: off_t,
    pub tdp: c_uint,
}

#[repr(C)]
pub struct BurnFeatureDescr
{
    pub feature_code: u16,
    pub flags: c_uchar,
    pub data_length: c_uchar,
    pub data: *mut u8,
    pub next: *mut BurnFeatureDescr,
}

#[repr(C)]
pub struct BurnDrive
{
    pub device_role: c_int,
    pub bus_no: c_int,
    pub host_no: c_int,
    pub id: c_int, 
    pub channel: c_int,
    pub lun: c_int,
    pub devname: *mut c_char,

    pub phys_if_std: c_int,
    pub phys_if_name: [c_char; 80],

    pub global_index: c_int,
    
    pub access_lock: pthread_mutex_t,

    pub status: BurnDiscStatus,
    pub erasable: c_int,

    pub current_profile: c_int,
    pub current_profile_text: [c_char; 80],
    pub current_is_cd_profile: c_int,
    pub current_is_supported_profile: c_int,
    pub current_is_guessed_profile: c_int,

    pub all_profiles: [c_uchar; 256],
    pub num_profiles: c_int, 

    pub features: *mut BurnFeatureDescr,

    pub current_has_feat21h: c_int,
    pub was_feat21h_failure: c_int,
    pub current_feat21h_link_size: c_int,
    pub current_feat23h_byte4: c_int,
    pub current_feat23h_byte8: c_int,
    
    /* Flags from feature 002Fh feature descriptor mmc5r03c.pdf 5.3.25 :
	     bit1= DVD-RW supported
	     bit2= Test Write available
	     bit3= DVD-R DL supported
	     bit6= Buffer Under-run Free recording available (page 05h BUFE)
	   Value -1 indicates that no 002Fh was current in the features list.
	*/
    pub current_feat2fh_byte4: c_int,

    pub drive_serial_number: *mut c_char,
    pub drive_serial_number_len: c_int,

    pub media_serial_number: *mut c_char,
    pub media_serial_number_len: c_int,

    pub next_track_damaged: c_int,

    /* whether a DVD-RW media holds an incomplete session */
    pub needs_close_session: c_int,

    pub needs_sync_cache: c_int,

    pub do_stream_recording: c_int,

    pub stream_recording_start: c_int,

    pub last_lead_in: c_int,
    pub last_lead_out: c_int,
    pub num_opc_tables: c_int,
    pub bg_format_status: c_int,
    pub disc_id: c_uint,
    pub disc_bar_code: [c_char; 9],
    pub disc_app_code: c_int,
    pub disc_info_valid: c_int,

    pub format_descr_type: c_int,
    pub format_curr_max_size: off_t,
    pub format_curr_blsas: c_uint,
    pub best_format_type: off_t, 

    pub num_format_descr: c_int,
    pub format_descriptors: [BurnFormatDescr; 32],
    
    pub release: c_int,

    pub silent_on_scsi_error: c_int,
    pub had_particular_error: c_int,
    pub stdio_fd: c_int,
    pub nwa: c_int, /* Next writable address */
    pub alba: c_int, /* absolute lba */
    pub start_lba: c_int,
    pub end_lba: c_int,

    pub do_simulate: c_int,
    pub complete_session: c_int,
    pub state_of_last_session: c_int,

    pub last_track_no: c_int, 
    pub sent_default_page_05: c_int,
    pub media_capacity_remaining: off_t,
    pub media_lba_limt: c_int,
    pub media_read_capacity: c_int,
    pub mr_capacity_trusted: c_int,
    pub role_5_nwa: c_int, /* Next Writeable Address for drive_role == 5 */
    pub do_no_immed: c_int,
    pub toc_temp: c_int,


    /* #ifdef Libburn_disc_with_incomplete_session */

    #[cfg(feature = "libburn_disc_with_imcomplete_session")]
    pub incomplete_sessions: c_int,

    /* #endif */
}


/*
    `#[no_mangle]` ensures the Rust compiler does not mangle the function name. 
    Normally, Rust changes function names into unique internal symbols for linking.
    This attribute makes the symbol literally "read_cd_sector" in the compiled binary,
    which allows C or other languages that use C-style linking to call it reliably.
*/
#[no_mangle]
pub extern "C" fn read_cd_sector(
    device_path:    *const c_char,  /* Raw pointer to a C-style string (const char*) pointing to the device path. 
                                         Must be NUL-terminated. */
    sector:         c_uint,         /* Logical sector number on the CD to read. Unsigned 32-bit integer. */
    buffer:         *mut u8,        /* Raw pointer to a pre-allocated output buffer where the sector data will be written. 
                                         Must be at least `CD_SECTOR_SIZE` bytes. */
) -> i32    /* Returns 0 on success, negative integers indicate different error conditions. */
{
    /* Validate input pointers to avoid undefined behavior:
       Dereferencing NULL pointers in Rust is UB, especially across FFI boundaries.
       Returns -1 if either pointer is null. */
    if device_path.is_null() || buffer.is_null() 
    {
        return -1; 
    }

    /* Convert the raw `*const c_char` into a Rust `CStr` (immutable C string view). 
       Unsafe block is required because Rust cannot verify:
       1. That the pointer is valid.
       2. That the pointer points to a NUL-terminated string.
       Dereferencing an invalid pointer or non-NUL-terminated string would be UB.
    */
    let path_cstr = unsafe { CStr::from_ptr(device_path) };

    /* Convert `CStr` to a Rust `&str`. This performs UTF-8 validation:
       - `Ok(s)` -> Valid UTF-8 string slice.
       - `Err(_)` -> Invalid UTF-8; return -2 to indicate a conversion error.
       This ensures we can safely use Rust string operations and pass the path to File APIs. */
    let path_str = match path_cstr.to_str() 
    {
        Ok(s) => s,
        Err(_) => return -2,
    };

    /* Attempt to open the device file for reading. This may fail for reasons such as:
       - File/device does not exist.
       - Permission denied.
       - Device is busy.
       The returned Result contains a `File` on success or `std::io::Error` on failure. */
    match File::open(path_str)
    {
        Ok(mut file) =>
        {
            /* Calculate byte offset for the requested sector:
               - CD sectors have a fixed size (`CD_SECTOR_SIZE`), usually 2048 bytes for data sectors.
               - Multiply the sector index by the sector size to locate the exact byte in the device.
               - Cast to u64 to prevent overflow in large CDs. */
            let offset = sector as u64 * CD_SECTOR_SIZE as u64;

            /* Seek to the desired sector in the file/device:
               - `SeekFrom::Start(offset)` moves the cursor to an absolute position.
               - If seeking fails (e.g., offset exceeds device size or device doesn't support seeking),
                 log the error and return -3. */
            if let Err(e) = file.seek(SeekFrom::Start(offset))
            {
                eprintln!("Failed to seek to sector {}: {}", sector, e);
                return -3; 
            }

            /* Convert the raw buffer pointer into a Rust mutable slice for safe access:
               - `from_raw_parts_mut` creates a `&mut [u8]` pointing to memory of length `CD_SECTOR_SIZE`.
               - Unsafe because Rust cannot verify:
                 1. That the pointer is valid.
                 2. That the buffer is large enough.
                 3. That no other mutable references exist to the same memory.
               This allows safe Rust I/O operations on the buffer. */
            let buf_slice = unsafe { std::slice::from_raw_parts_mut(buffer, CD_SECTOR_SIZE) };

            /* Read exactly `CD_SECTOR_SIZE` bytes into the buffer:
               - `read_exact` ensures we fill the entire buffer or return an error.
               - If fewer bytes are read or an I/O error occurs (e.g., device removed),
                 log the error and return -4.
               - On success, the buffer now contains the raw CD sector data. */
            if let Err(e) = file.read_exact(buf_slice)
            {
                eprintln!("Failed to read sector {}: {}", sector, e);
                return -4; 
            }

            /* Successfully read the sector. */
            0
        }
        Err(_) =>
        {
            /* Failed to open the device:
               - Likely causes include non-existent path, permission denied, or inaccessible device.
               - Log the error for diagnostics and return -5. */
            eprintln!("Failed to open device at path: {}", path_str);
            -5 
        }
    }
}

extern "C"
{
    /* Expose the C/C++ function of read_cd_sector */
    fn read_cd_sector(device_path: *const c_char, sector: c_uint, buffer: *mut u8) -> i32;
}