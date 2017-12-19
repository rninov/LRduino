// Rotary Encoder
int RotaryPosition[NUM_SETTINGS] = {63,63,63,63,63};
int PrevPosition[NUM_SETTINGS] = {63,63,63,63,63};

volatile boolean TurnDetected;  // need volatile for Interrupts
volatile boolean rotationdirection;  // CW or CCW rotation

const int PinCLK=2;   // Generating interrupts using CLK signal
const int PinDT=3;    // Reading DT signal
const int PinSW=4;    // Reading Push Button switch

// Interrupt routine runs if CLK goes from HIGH to LOW
void isr ()  {
    delay(4);  // delay for Debouncing
    if (digitalRead(PinCLK))
      rotationdirection= !digitalRead(PinDT);
    else
      rotationdirection= digitalRead(PinDT);
    TurnDetected = true;
}