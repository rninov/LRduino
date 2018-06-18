/*
    LRduino - The open-source modular controller for photo post-processing
    Copyright (C) 2018  Ben Trew

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    https://github.com/Bixx
*/

#include "src/LR_Button.h"
#include "src/LR_Display.h"
#include "src/LR_Encoder.h"

String adj[] = {"Exposure", "Contrast", "Brightness", "Shadows", "Highlights"};
int adjlen = sizeof(adj) / sizeof(adj[0]);

LR_Button button0(0, adj, adjlen);
LR_Display display0(7, 8, 9, 10, 11, 12);
LR_Encoder encoder0(2, 3, 4, adjlen);

// To be moved into library
struct MIDISettings : public midi::DefaultSettings
{
    static const long BaudRate = 115200;
};
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MIDISettings);

int _note;
int _velocity; 
int _channel;
int _velocity_prev; 
int _channel_prev;
// \ To be moved into library

void setup()
{
    // To be moved into library
    MIDI.begin();
    _note = 127;
    _velocity = 64;
    _channel = 1;
    _velocity_prev = 64;
    _channel_prev = 1;
    // \ To be moved into library
}

void loop()
{   

    display0.update(button0.getSelectedAdjustment());

    _channel = button0.getChoice() + 1;
    _velocity = encoder0.update(button0.getChoice());

    // To be moved into library
    if (!((_velocity_prev == _velocity) && (_channel_prev = _channel))) {
        MIDI.sendNoteOn(_note, _velocity, _channel);
        _velocity_prev = _velocity;
        _channel_prev = _channel;
    }
    // \ To be moved into library

}
