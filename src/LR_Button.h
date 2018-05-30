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