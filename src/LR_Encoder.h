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

#ifndef LR_Encoder_h
#define LR_Encoder_h

#include "Arduino.h"
#include <Encoder.h>

class LR_Encoder
{
  public:
    LR_Encoder(int pinCLK, int pinDT, int pinSW, int adjustments_len);
    int update(int choice);
  private:

    // Pins
    int _pinCLK;
    int _pinDT;
    int _pinSW;

    // Selection
    int _adjustments_len;
    int _choice;

    // Encoder
    Encoder* _enc;
    int* _position;
};


#endif