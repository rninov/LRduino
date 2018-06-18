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

#ifndef LR_Button_h
#define LR_Button_h

#include "Arduino.h"
#include <Bounce2.h>

class LR_Button
{
  public:
    LR_Button(int pin, String adjustments[], int adjustments_len);
    String getSelectedAdjustment();
    int getChoice();

  private:
    // pin
    int _pin;

    // Debounce
    Bounce _debouncer;
    const int _DEBOUNCE_PERIOD = 500;
    unsigned long _DEBOUNCE_LAST;
    int _DEBOUNCE_CURRENT_VALUE;

    // Selection
    String* _adjustments;
    int _adjustments_len;
    int _choice;
};

#endif