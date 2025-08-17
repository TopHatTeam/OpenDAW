// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//  Created by Andrew Skatzes on 8/16/25.
//  Midi.cpp
//
//  Description:
//      Midi functionality for the Daw
//
// ---------------------------------------------------------

#include "headers/Midi.hpp"

MIDIDevice::MIDIDevice() 
{
    midiin  = nullptr;
    midiout = nullptr;

    try 
    {
        midiin = new RtMidiIn();
    }
    catch (RtMidiError &err)
    {
        err.printMessage();
        delete midiin;
        delete midiout;
    }

    nPorts = midiin->getPortCount();
    for ( unsigned int i=0; i < nPorts; i++)
    {
        try 
        {
            portName = midiin->getPortName(i);
        }
        catch (RtMidiError &err)
        {
            err.printMessage();
            delete midiin;
            delete midiout;
        }
    }

    try 
    {
        midiout = new RtMidiOut();
    }
    catch (RtMidiError &err)
    {
        err.printMessage();
        delete midiin;
        delete midiout;
    }

    nPorts = midiout->getPortCount();
    for (unsigned int i=0; i < nPorts; i++)
    {
        try
        {
            portName = midiout->getPortName(i);
        }
        catch (RtMidiError &err)
        {
            err.printMessage();
            delete midiin;
            delete midiout;
        }
    }
}
