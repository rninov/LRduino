/*
    LRDuino - The open-source modular controller for Lightroom, powered by Arduino
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


LR_Encoder::LR_Encoder(int pinCLK, int pinDT, int pinSW, int adjustments_len)
{
    // void *_isr = LR_Encoder::isr;

    // Pins
    _pinCLK = pinCLK;
    _pinDT = pinDT;
    _pinSW = pinSW;

    pinMode(_pinCLK,INPUT);
    pinMode(_pinDT,INPUT);  
    pinMode(_pinSW,INPUT);
    digitalWrite(_pinSW, HIGH); // Pull-Up resistor for switch
    // attachInterrupt(0, isr, FALLING); // interrupt 0 always connected to pin 2 on Arduino UNO
    setup(_pinCLK);

    // Initialise value arrays
    _adjustments_len = adjustments_len;
    _RotaryPosition = new int[_adjustments_len];
    _PrevPosition = new int[_adjustments_len];

    unsigned int i = 0;
    for (i = 0; i < _adjustments_len; i++) {
        _RotaryPosition[i] = 64;
        _PrevPosition[i] = 64;
    }

    _choice = 0;
    _channel = _choice + 1;
};


void LR_Encoder::setup(int pin)
{
    attachInterrupt(pin, isr, FALLING);
}


void LR_Encoder::update(int choice)
{
    _choice = choice;

    _channel = _choice + 1;

    // if (!(digitalRead(_pinSW))) {   // check if button is pressed
    //     if (_RotaryPosition[_channel] == 63) {  // check if button was already pressed
    //     } else {
    //         _RotaryPosition[_channel]=63; // Reset position to ZERO
    //         // MIDI.sendNoteOn(note, RotaryPosition[_channel], _channel);
    //         Serial.print("Rotary button clicked, sending ");
    //         Serial.print(_RotaryPosition[_channel]);
    //     }
    // }
    // Runs if rotation was detected
    if (_TurnDetected)  {
        Serial.print("Turn detected");
        // Serial.print(choice);
        _PrevPosition[_channel] = _RotaryPosition[_channel]; // Save previous position
        if (_rotationdirection) {
            _RotaryPosition[_channel]=_RotaryPosition[_channel]-1; // decrease Position by 1
        }
        
        else {
            _RotaryPosition[_channel]=_RotaryPosition[_channel]+1; // increase Position by 1
        }

        _TurnDetected = false;  // do not repeat

        // Which direction to move
        if ((_PrevPosition[_channel] + 1) == _RotaryPosition[_channel]) { // Move CW
            // MIDI.sendControlChange(note, _RotaryPosition[_channel], _channel);
            Serial.print("Encoder turned CW, sending ");
            Serial.print(_RotaryPosition[_channel]);
        }

        if ((_RotaryPosition[_channel] + 1) == _PrevPosition[_channel]) { // Move CCW
            // MIDI.sendControlChange(note, _RotaryPosition[_channel], _channel);
            Serial.print("Encoder turned CCW, sending ");
            Serial.print(_RotaryPosition[_channel]);
        }
    }
}

void LR_Encoder::isr()
{
    delay(4);
    if (digitalRead(_pinCLK))
        _rotationdirection = !digitalRead(_pinDT);
    else
        _rotationdirection = digitalRead(_pinDT);
    _TurnDetected = true;
}