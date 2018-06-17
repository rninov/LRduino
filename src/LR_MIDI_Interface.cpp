/*
    LRDuino - The open-source modular controller for photo post-processing
    Copyright (C) 2018  Ben Trew

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    https://github.com/Bixx
*/

#include "Arduino.h"
#include "LR_MIDI_Interface.h"
#include <MIDI.h>

LR_MIDI_Interface::LR_MIDI_Interface()
{
    _note = 127; // Max Note (range 0-127) - will remain fixed
    _velocity = 64; // Mid Velocity (range 0-127) - changes adjustment value
    _channel = 1; // MIDI Channel (1-16) - changes adjustment
    
};

// void LR_MIDI_Interface::updateAdjustment(int choice, int adjValue)
// {
//     _velocity = adjValue;
//     _channel = choice + 1;
//     MIDI.sendNoteOn(_note, _velocity, _channel);
// }