const int DEBOUNCE_PERIOD = 500;
unsigned long BUTTON_0_DEBOUNCE_LAST = 0;

const int NUM_SETTINGS = 5;
String settings[NUM_SETTINGS] = {
    "Exposure",
    "Contrast",
    "Brightness",
    "Shadows",
    "Highlights",
  };

const int BUTTON_0_PIN = 0;