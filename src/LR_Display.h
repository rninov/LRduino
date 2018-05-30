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

#ifndef LR_Display_h
#define LR_Display_h

#include "Arduino.h"
#include <LiquidCrystal.h>

class LR_Display
{
  public:
    LR_Display(int pin0, int pin1, int pin2, int pin3, int pin4, int pin5);
    void update(String selected_adjustment);

  private:
    // Pins
    int _pin0;
    int _pin1;
    int _pin2;
    int _pin3;
    int _pin4;
    int _pin5;

    // LCD
    LiquidCrystal *_lcd;
    String _selected_adjustment;
      
};

#endif