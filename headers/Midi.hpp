// ---------------------------------------------------------
//
//  OpenDAW
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      Midi functionality for the DAW
//
// ---------------------------------------------------------

#ifndef MIDI_HPP
#define MIDI_HPP

#include <fmt/std.h>
#include <string>
#include <cstdlib>
#include "AudioCore.h"
#include "RtMidi.h"

/*TODO: The rest of this header*/

// -- MIDI definitions -- 
#define MIDI_NOTE_ON            0x90
#define MIDI_NOTE_OFF           0x80
#define MIDI_AFTERTOUCH         0xA0
#define MIDI_CONTROL_CHANGE     0xB0
#define MIDI_PROGRAM_CHANGE     0xC0
#define MIDI_PITCH_BEND         0xE0

using std::string;

typedef enum 
{
    MPL_ACOUSTIC_BASS_DRUM  = 35,
    MPL_ELECTRIC_BASS_DRUM  = 36,
    MPL_SIDE_STICK          = 37,
    MPL_ACOUSTIC_SNARE      = 38,
    MPL_HAND_CLAP           = 39,
    MPL_ELECTRIC_SNARE      = 40,
    MPL_LOW_FLOOR_TOM       = 41,
    MPL_CLOSED_HI_HAT       = 42,
    MPL_HIGH_FLOOR_TOM      = 43,
    MPL_PEDAL_HI_HAT        = 44,
    MPL_LOW_TOM             = 45,
    MPL_OPEN_HI_HAT         = 46,
    MPL_LOW_MID_TOM         = 47,
    MPL_HI_MID_TOM          = 48,
    MPL_CRASH_CYMBAL_1      = 49,
    MPL_HIGH_TOM            = 50,
    MPL_RIDE_CYMBAL_1       = 51,
    MPL_CHINA_CYMBAL        = 52,
    MPL_RIDE_BELL           = 53,
    MPL_TAMBOURINE          = 54,
    MPL_SPLASH_CYMBAL       = 55,
    MPL_COWBELL             = 56,
    MPL_CRASH_CYMBAL_2      = 57,
    MPL_VIBRASLAP           = 58,
    MPL_RIDE_CYMBAL_2       = 59,
    MPL_HI_BONGO            = 60,
    MPL_LOW_BONGO           = 61,
    MPL_MUTE_HI_CONGA       = 62,
    MPL_OPEN_HI_CONGA       = 63,
    MPL_LOW_CONGA           = 64,
    MPL_HIGH_TIMBALE        = 65,
    MPL_LOW_TIMBALE         = 66,
    MPL_HIGH_AGOGO          = 67,
    MPL_LOW_AGOGO           = 68,
    MPL_CABASA              = 69,
    MPL_MARACAS             = 70,
    MPL_SHORT_WHISTLE       = 71,
    MPL_LONG_WHISTLE        = 72,
    MPL_SHORT_GUIRO         = 73,
    MPL_LONG_GUIRO          = 74,
    MPL_CLAVES              = 75,
    MPL_HI_WOOD_BLOCK       = 76,
    MPL_LOW_WOOD_BLOCK      = 77,
    MPL_MUTE_CUICA          = 78,
    MPL_OPEN_CUICA          = 79,
    MPL_MUTE_TRIANGLE       = 80,
    MPL_OPEN_TRIANGLE       = 81,
    MPL_UNDEFINED           = 0         
    
} MIDI_PERCUSSION_LAYOUT;

class MIDIDevice
{
public:
    MIDIDevice();
    ~MIDIDevice() 
    {
        delete midiin;
        delete midiout;
    }
    int         getid() const { return id; }
    RtMidiIn*   GetMidiIn() const { return midiin; }
    RtMidiOut*  GetMidiOut() const { return midiout; }
    void        SetMidiIn(RtMidiIn* in) { midiin = in; }        /* must be a void because we're not returning anything*/
    void        SetMidiOut(RtMidiOut* out) { midiout = out; }   

    string portName;
    unsigned int nPorts;
private:
    int         id;
    RtMidiIn*   midiin;
    RtMidiOut*  midiout;
};

#endif  