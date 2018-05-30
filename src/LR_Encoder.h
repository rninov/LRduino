#ifndef LR_Encoder_h
#define LR_Encoder_h

#include "Arduino.h"

class LR_Encoder
{
  public:
    LR_Encoder(int pinCLK, int pinDT, int pinSW, int adjustments_len);
    void update(int choice);
    void setup(int pin);
  private:

    // Pins
    int _pinCLK;
    int _pinDT;
    int _pinSW;

    // Selection
    int _adjustments_len;
    int _choice;
    int _channel;

    // Encoder
    int *_RotaryPosition;
    int *_PrevPosition;
    
    volatile boolean _TurnDetected;
    volatile boolean _rotationdirection;

    void isr();
    // void* _isr;
    
};



#endif