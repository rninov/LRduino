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