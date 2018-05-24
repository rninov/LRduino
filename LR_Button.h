#ifndef LR_Button_h
#define LR_Button_h

#include "Arduino.h"
#include <Bounce2.h>

class LR_Button
{
  public:
    LR_Button(int pin, String adjustments[]);
    String getSelectedAdjustment();
    int getChoice();
  private:
    // const int DEBOUNCE_PERIOD = 500;
    // unsigned long BUTTON_0_DEBOUNCE_LAST = 0;
    // const int NUM_SETTINGS = 5;
    // String _settings[NUM_SETTINGS] = {
    //     "Exposure",
    //     "Contrast",
    //     "Brightness",
    //     "Shadows",
    //     "Highlights",
    //   };
    
    // int BUTTON_0_PIN = 0;

    // pin
    int _pin;

    // Debounce
    Bounce _debouncer;
    const int _DEBOUNCE_PERIOD = 500;
    unsigned long _DEBOUNCE_LAST;
    int _DEBOUNCE_CURRENT_VALUE;

    // Selection
    String* _adjustments;
    // String *_adjustments;
    int _adjustments_len;
    int _choice;
};



#endif