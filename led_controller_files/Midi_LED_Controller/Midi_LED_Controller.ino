// TODO: install FastLED Library by Daniel Garcia. Refer to video: https://youtu.be/3bhiUGFt6as 
#include <FastLED.h>

// TODO: define how many LEDs you have on your strip. This example below would be for 50 leds on your strip
#define NUM_LEDS 50

// TODO: define which pin you selected for your data pin. If you followed the video, the default is '2'
#define DATA_PIN 2

// TODO: define your piano offset. This is the lowest midi note that will react to your LED strip.
// For example, the lowest note on a standard 88 key piano (A0) has a midi note value of 21.
// Make your offset the lowest midi note number you want to show. If you have more notes than lights, I'd make it higher.
// Use this site as a refernce: https://inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies 
#define OFFSET 21

// TODO: define your fade speed. This value will set how fast a note fades to black after pressing it.
// NOTE: The higher the number, the FASTER it will fade. 0 will make the note never fade. 
// I like 30 as a good start. 100 will make it near instant.
#define FADE_SPEED 30

// the array of leds to control
CRGB leds[NUM_LEDS];

// the incoming note
char incomingMidiNote;

void setup() {
  // put your setup code here, to run once:

  // set up Fast LED library
  // NOTE: You may need to change 'NEOPIXEL' to another constant depending on the led strip you are using. Refer to (add link)
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // begin serial, listening for inputs
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  // read the incoming midi note
  incomingMidiNote = Serial.read();

  // 0 is the value it reads if no notes are incoming
  if(incomingMidiNote > 0) {
    // get the note to show by getting the note and subtracting the offset
    int noteToShow = incomingMidiNote - OFFSET;

    // glow up the note to a rainbow color
    leds[noteToShow] = GetRainbowNote(noteToShow);

    // glow up the note to a white color.
    // leds[noteToShow] = GetWhiteNote(noteToShow);
  }

  // fade the led note to black, according to the fade speed
  // 10 miliseconds is a good delay time not to lag the arduino
  EVERY_N_MILLISECONDS(10) {
    fadeToBlackBy(leds, NUM_LEDS, FADE_SPEED);
    FastLED.show();
  }
}

// Get a rainbow note
CRGB GetRainbowNote(int midiNote) {
  // NOTE: 12 is for the 12 notes on the piano scale. You can mess around with the 'patternLength'
  int patternLength = 12;
  int hue = ((double)(midiNote % patternLength) / patternLength) * 360;
  return CHSV(hue, 255, 255);
}

// Get a white note. Use this as a reference to make your own colors!
CRGB GetWhiteNote(int midiNote) {
  return CRGB(255, 255, 255);
}