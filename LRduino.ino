// #include <MIDI.h>

// #include "encoder.h"
// #include "midi_setup.h"

#include "src/LR_Button.h"
#include "src/LR_Display.h"
#include "src/LR_Encoder.h"

String adj[] = {"Exposure", "Contrast", "Brightness", "Shadows", "Highlights"};
int adjlen = sizeof(adj) / sizeof(adj[0]);

LR_Button button0(0, adj, adjlen);
LR_Display display0(7, 8, 9, 10, 11, 12);
LR_Encoder encoder0(2, 3, 4, adjlen);

String selection = "";

// int note = 127; //Max Note (range is 0-127)
// int velocity = 63; //Mid Velocity (range is 0-127)
// // int channel = choice + 1; //MIDI Channel 1 (out of 16)
// int channel = 1; //MIDI Channel 1 (out of 16)

// MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings);
void setup()
{
    // MIDI.begin();
    Serial.begin(115200);

    encoder0.setup(2);
  
}

void loop()
{   
    selection = button0.getSelectedAdjustment();

    display0.update(selection);

    encoder0.update(button0.getChoice());

    // channel = choice + 1;
    
    // // Rotary Encoder
    // if (!(digitalRead(PinSW))) {   // check if button is pressed
    //     if (RotaryPosition[channel] == 63) {  // check if button was already pressed
    //     } else {
    //         RotaryPosition[channel]=63; // Reset position to ZERO
    //         // MIDI.sendControlChange(note, RotaryPosition, channel);
    //         MIDI.sendNoteOn(note, RotaryPosition[channel], channel);
    //     }
    // }
    // // Runs if rotation was detected
    // if (TurnDetected)  {
    //     PrevPosition[channel] = RotaryPosition[channel]; // Save previous position in variable
    //     if (rotationdirection) {
    //         RotaryPosition[channel]=RotaryPosition[channel]-1; // decrease Position by 1
    //         // Serial.print("RotaryPosition[channel]: ");
    //         // Serial.println(RotaryPosition[channel]);
    //     }
        
    //     else {
    //         RotaryPosition[channel]=RotaryPosition[channel]+1; // increase Position by 1
    //         // Serial.print("RotaryPosition[channel]: ");
    //         // Serial.println(RotaryPosition[channel]);
    //     }

    //     TurnDetected = false;  // do NOT repeat IF loop until new rotation detected

    //     // Which direction to move
    //     if ((PrevPosition[channel] + 1) == RotaryPosition[channel]) { // Move motor CW
    //         MIDI.sendControlChange(note, RotaryPosition[channel], channel);
    //     }

    //     if ((RotaryPosition[channel] + 1) == PrevPosition[channel]) { // Move motor CCW
    //         MIDI.sendControlChange(note, RotaryPosition[channel], channel);
    //     }
    // }
}
