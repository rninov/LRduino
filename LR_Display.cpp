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