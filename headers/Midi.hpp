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