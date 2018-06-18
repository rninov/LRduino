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
#include "LR_Button.h"
#include <Bounce2.h>


LR_Button::LR_Button(int pin, String adjustments[], int adjustments_len)
{
    // Initialise
    _DEBOUNCE_LAST = 0;

    // Add pin
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP); 
    _debouncer = Bounce();
    _debouncer.attach(_pin);
    _debouncer.interval(10); // interval in ms

    // Load adjustments
    _adjustments_len = adjustments_len;
    _adjustments = new String[_adjustments_len];
    _adjustments = adjustments;
    _choice = 0;
};

String LR_Button::getSelectedAdjustment()
{
    // Update the Bounce instance :
    _debouncer.update();
    // Get the updated value :
    _DEBOUNCE_CURRENT_VALUE = _debouncer.read();

    if ((_DEBOUNCE_CURRENT_VALUE == LOW) && (millis() - _DEBOUNCE_LAST >= _DEBOUNCE_PERIOD))
    {   
        _choice = _choice + 1;
        
        if (_choice >= _adjustments_len) {
            _choice = 0;
        }

        _DEBOUNCE_LAST = millis();
        Serial.print("Pushed");
    };

    return _adjustments[_choice];
};

int LR_Button::getChoice()
{
    return _choice;
};