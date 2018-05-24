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
    };

    return _adjustments[_choice];
};

int LR_Button::getChoice()
{
    return _choice;
};