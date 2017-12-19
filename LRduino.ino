#include <Bounce2.h>
#include <LiquidCrystal.h>
#include <MIDI.h>

#include "display.h"
#include "button.h"
#include "encoder.h"
#include "midi_setup.h"

// Debounce
Bounce debouncer = Bounce();

int choice = 0;
int note = 127; //Max Note (range is 0-127)
int velocity = 63; //Mid Velocity (range is 0-127)
int channel = choice + 1; //MIDI Channel 1 (out of 16)

MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings);
void setup()
{
    MIDI.begin();
    // Serial.begin(115200);
    
    //Set up the LDCs number of columns and rows:
    lcd.begin(16, 2);
    //Print a message to the LCD.
    lcd.print(settings[choice]);
    //Make progress characters
    lcd = createLoadingBar(lcd);
    
    // Button
    pinMode(BUTTON_0_PIN, INPUT_PULLUP); 
    debouncer.attach(BUTTON_0_PIN);
    debouncer.interval(10); // interval in ms

    // Rotary Encoder
    pinMode(PinCLK,INPUT);
    pinMode(PinDT,INPUT);  
    pinMode(PinSW,INPUT);
    digitalWrite(PinSW, HIGH); // Pull-Up resistor for switch
    attachInterrupt (0,isr,FALLING); // interrupt 0 always connected to pin 2 on Arduino UNO
  
}

void loop()
{   
    // Update the Bounce instance :
    debouncer.update();
    // Get the updated value :
    int BUTTON_0_VALUE = debouncer.read();

    if ((BUTTON_0_VALUE == LOW) && (millis() - BUTTON_0_DEBOUNCE_LAST >= DEBOUNCE_PERIOD))
    {   

        //Set up the LCDs number of columns and rows:
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,0);
        //Print a message to the LCD.
        choice = choice + 1;

        if (choice >= NUM_SETTINGS) {
            choice = 0;
        }

        // Serial.print("Choice: ");
        // Serial.print(choice);
        // Serial.print("  Setting: ");
        // Serial.println(settings[choice]);

        lcd.print(settings[choice]);

        BUTTON_0_DEBOUNCE_LAST = millis();
    }

    //Move cursor to second line
    lcd.setCursor(0,1);
    //Clear the line each time it reaches the end
    //with 16 " " (spaces)
    lcd.print("                ");

    channel = choice + 1;
    
    // Rotary Encoder
    if (!(digitalRead(PinSW))) {   // check if button is pressed
        if (RotaryPosition[channel] == 63) {  // check if button was already pressed
        } else {
            RotaryPosition[channel]=63; // Reset position to ZERO
            // MIDI.sendControlChange(note, RotaryPosition, channel);
            MIDI.sendNoteOn(note, RotaryPosition[channel], channel);
        }
    }
    // Runs if rotation was detected
    if (TurnDetected)  {
        PrevPosition[channel] = RotaryPosition[channel]; // Save previous position in variable
        if (rotationdirection) {
            RotaryPosition[channel]=RotaryPosition[channel]-1; // decrease Position by 1
            // Serial.print("RotaryPosition[channel]: ");
            // Serial.println(RotaryPosition[channel]);
        }
        
        else {
            RotaryPosition[channel]=RotaryPosition[channel]+1; // increase Position by 1
            // Serial.print("RotaryPosition[channel]: ");
            // Serial.println(RotaryPosition[channel]);
        }

        TurnDetected = false;  // do NOT repeat IF loop until new rotation detected

        // Which direction to move
        if ((PrevPosition[channel] + 1) == RotaryPosition[channel]) { // Move motor CW
            MIDI.sendControlChange(note, RotaryPosition[channel], channel);
        }

        if ((RotaryPosition[channel] + 1) == PrevPosition[channel]) { // Move motor CCW
            MIDI.sendControlChange(note, RotaryPosition[channel], channel);
        }
    }
}
