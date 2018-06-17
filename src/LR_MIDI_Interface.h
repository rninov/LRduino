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

#ifndef LR_MIDI_Interface_h
#define LR_MIDI_Interface_h

#include "Arduino.h"
#include <MIDI.h>

class LR_MIDI_Interface
{
  public:
    LR_MIDI_Interface();
    // void updateAdjustment(int choice, int adjValue);

  private:   
    int _note; // Max Note (range 0-127) - will remain fixed
    int _velocity; // Mid Velocity (range 0-127) - changes adjustment value
    int _channel; // MIDI Channel (1-16) - changes adjustment
};


#endif