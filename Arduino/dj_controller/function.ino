void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void vuMetr() {
  pixels.clear();
  for (byte i = 0; i < NUMPIXELS / 2; i++) {
    if (i < byteTwo) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      if (i > 8) {
        pixels.setPixelColor(i, pixels.Color(255, 255, 0));
        if (i > 12)pixels.setPixelColor(i, pixels.Color(0, 255, 0));
      }
    }
    else pixels.setPixelColor(i, pixels.Color(0, 0, 0));

    if (i < byteThree) {
      pixels.setPixelColor(i + 16, pixels.Color(255, 0, 0));
      if (i > 4) {
        pixels.setPixelColor(i + 16, pixels.Color(255, 255, 0));
        if (i > 6)pixels.setPixelColor(i + 16, pixels.Color(0, 255, 0));
      }
    }
    else pixels.setPixelColor(i + 16, pixels.Color(0, 0, 0));
  }
  pixels.show();
}

void changeEncoder(int i, bool flag) {
  if(flag) noteOn(13, i, 64);
  else noteOff(13, i, 64);
  MidiUSB.flush();
  arrEnc[i] = !arrEnc[i];
}
