#include "Arduino.h"
#include "LR_Button.h"
#include <Bounce2.h>


LR_Button::LR_Button(int pin, String adjustments[])
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
    // _adjustments_len = sizeof(adjustments)/sizeof(adjustments[0]);
    _adjustments_len = sizeof(adjustments);
    _adjustments = new String[_adjustments_len];
    _adjustments = adjustments;
    // _adjustments = adjustments;
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
        Serial.print("_adjustments_len: ");
        Serial.print(_adjustments_len);
        Serial.print("\n");
        Serial.print("first element:: ");
        Serial.print(_adjustments[0]);
        Serial.print("\n");
        Serial.print("second element: ");
        Serial.print(_adjustments[1]);
        Serial.print("\n");
        Serial.print("third element: ");
        Serial.print(_adjustments[3]);
        Serial.print("\n");

        _choice = _choice + 1;
        
        if (_choice >= _adjustments_len) {
            _choice = 0;
        }

        Serial.print("_choice: ");
        Serial.print(_choice);
        Serial.print("\n");

        // Serial.print("Choice: ");
        // Serial.print(choice);
        // Serial.print("  Setting: ");
        // Serial.println(settings[choice]);

        _DEBOUNCE_LAST = millis();
    };

    return _adjustments[_choice];
};

int LR_Button::getChoice()
{
    return _choice;
};