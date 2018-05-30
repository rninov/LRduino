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

#include "Arduino.h"
#include "LR_Display.h"
#include <LiquidCrystal.h>

LR_Display::LR_Display(int pin0, int pin1, int pin2, int pin3, int pin4, int pin5)
{
    // Add pin
    _pin0 = pin0;
    _pin1 = pin1;
    _pin2 = pin2;
    _pin3 = pin3;
    _pin4 = pin4;
    _pin5 = pin5;
    
    //Initialize the library with the numbers of the interface pins
    _lcd = new LiquidCrystal(_pin0, _pin1, _pin2, _pin3, _pin4, _pin5);

    _lcd -> begin(16, 2);
    
};

void LR_Display::update(String selected_adjustment)
{
    if (_selected_adjustment != selected_adjustment)
    {
        // Clear the LCD
        _lcd -> setCursor(0,0);
        _lcd -> print("                ");
        _lcd -> setCursor(0,1);
        _lcd -> print("                ");

        // Print the adjustment
        _lcd -> setCursor(0,0);    
        _lcd -> print(selected_adjustment);

        _selected_adjustment = selected_adjustment;
    }
}