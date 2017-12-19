// MIDI
#include <MIDI.h>

struct MySettings : public midi::DefaultSettings
{
  static const long BaudRate = 115200;
};

int note = 127; //Max Note (range is 0-127)
int velocity = 63; //Mid Velocity (range is 0-127)
int channel = 1; //MIDI Channel 1 (out of 16)