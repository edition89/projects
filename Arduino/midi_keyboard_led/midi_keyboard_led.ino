#include "MIDIUSB.h"

#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif


Adafruit_MPR121 cap = Adafruit_MPR121();

int len = 12;
byte dval = 0;
uint16_t currtouched = 0;
byte kpdNote[12] = { 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47 }; //Массив нот

byte buttonState[12] = {0}; //--Массив состояния кнопок

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}


void setup() {
  Serial.begin(115200);
  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  cap.begin(0x5A);
  
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() {
  currtouched = cap.touched();
  Serial.println(currtouched);

  //-------------------------------------

  for (byte i = 0; i < len; i++) {                        //--Построчно считываем каждый столбец--
    dval = (currtouched >> i) & 1;                        //--И при нажатой кнопке передаём ноту--
    if ( dval == 1 && buttonState[i] == LOW ) {
      noteOn(5, kpdNote[i], 64);
      MidiUSB.flush();
    }
    if ( dval == 0 && buttonState[i] == HIGH ) {
      noteOff(5, kpdNote[i], 64); 
      MidiUSB.flush();     
    }
    buttonState[i] = dval;

  }
}
