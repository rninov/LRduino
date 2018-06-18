/*
    LRduino - The open-source modular controller for photo post-processing
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
#include "LR_Encoder.h"
#include <Encoder.h>

// Encoder will not use interrupts as human usage should be slow enough. Allows use of encoder on any pin.
#define ENCODER_DO_NOT_USE_INTERRUPTS

LR_Encoder::LR_Encoder(int pinCLK, int pinDT, int pinSW, int adjustments_len)
{
    // Pins
    _pinCLK = pinCLK;
    _pinDT = pinDT;
    _pinSW = pinSW;

    // Currently selected adjustment
    _choice = 0;

    // Initialise position array
    _adjustments_len = adjustments_len;
    _position = new int[_adjustments_len];

    unsigned int i = 0;
    for (i = 0; i < _adjustments_len; i++) {
        _position[i] = 64;
    }

    // Encoder
    _enc = new Encoder(_pinCLK, _pinDT);
    _enc->write(_position[0]); // Set initial encoder position to centre of MIDI range for first adjustment
    
    // Encoder switch
    pinMode(_pinSW,INPUT);
    digitalWrite(_pinSW, HIGH); // Pull-Up resistor for switch

};


int LR_Encoder::update(int choice)
{   
    // If the adjustment choice has changed, get the last known position
    if (_choice == choice) {
    } else {
        _choice = choice;
        _enc->write(_position[_choice]);
    }
    
    // Update the adjustment with the new position
    long newPos = _enc->read();
    if (newPos != _position[_choice]) {
        _position[_choice] = newPos;
    }

    // Check if button is pressed
    if (!(digitalRead(_pinSW))) {   
        if (_position[_choice] == 64) {  // check if button was already pressed
        } else {
            _position[_choice] = 64;
            _enc->write(_position[_choice]); // Reset position
        }
    }

    return _position[_choice];
}