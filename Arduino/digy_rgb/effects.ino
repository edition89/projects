void colorWipe(uint32_t c, uint8_t wait, uint8_t step) {
  for (uint16_t i = 0; i < strip.numPixels(); i += step) {
    if (!flag) break;
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
  flag = true;
}

void rainbow(uint8_t wait) {
  uint8_t i, j;

  for (j = 0; j < 256; j++) {
    if (!flag) break;
    for (i = 0; i < strip.numPixels(); i++) {
      if (!flag) break;
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
  flag = true;
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint8_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    if (!flag) break;
    for (i = 0; i < strip.numPixels(); i++) {
      if (!flag) break;
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
  flag = true;
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (uint8_t j = 0; j < 10; j++) { //do 10 cycles of chasing
    if (!flag) break;
    for (uint8_t q = 0; q < 3; q++) {
      if (!flag) break;
      for (uint8_t i = 0; i < strip.numPixels(); i = i + 3) {
        if (!flag) break;
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint8_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
  flag = true;
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (uint8_t j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    if (!flag) break;
    for (uint8_t q = 0; q < 3; q++) {
      if (!flag) break;
      for (uint8_t i = 0; i < strip.numPixels(); i = i + 3) {
        if (!flag) break;
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint8_t i = 0; i < strip.numPixels(); i = i + 3) {
        if (!flag) break;
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
  flag = true;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

void pixel(uint32_t c, uint8_t wait) {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    if (!flag) break;
    if (i == LED_COUNT - 1) {
      strip.setPixelColor(0, c);
      strip.setPixelColor(i, 0, 0, 0);
    }
    else {
      strip.setPixelColor(i + 1, c);
      strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
    delay(wait);
  }
  flag = true;
}

void threePixel(uint32_t c, uint8_t wait) {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    if (!flag) break;
    if (i == LED_COUNT - 3) {
      strip.setPixelColor(0, c);
      strip.setPixelColor(i + 2, c);
      strip.setPixelColor(i + 1, c);
      strip.setPixelColor(i, 0, 0, 0);
    }
    else if (i == LED_COUNT - 2) {
      strip.setPixelColor(1, c);
      strip.setPixelColor(0, c);
      strip.setPixelColor(i + 1, c);
      strip.setPixelColor(i, 0, 0, 0);
    }
    else if (i == LED_COUNT - 1) {
      strip.setPixelColor(2, c);
      strip.setPixelColor(1, c);
      strip.setPixelColor(0, c);
      strip.setPixelColor(i, 0, 0, 0);
    }
    else {
      strip.setPixelColor(i + 3, c);
      strip.setPixelColor(i + 2, c);
      strip.setPixelColor(i + 1, c);
      strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
    delay(wait);
  }
  flag = true;
}

void doublePixel(uint32_t c, uint8_t wait) {
  for (uint8_t i = 0; i < int(LED_COUNT/2); i++) {
    if (!flag) break;
    if (i == int(LED_COUNT/2) - 1) {
      strip.setPixelColor(0, c);
      strip.setPixelColor(i, 0, 0, 0);
      strip.setPixelColor(0 + int(LED_COUNT/2), c);
      strip.setPixelColor(i + int(LED_COUNT/2), 0, 0, 0);
    }
    else {
      strip.setPixelColor(i + 1, c);
      strip.setPixelColor(i, 0, 0, 0);
      strip.setPixelColor(i + 1 + int(LED_COUNT/2), c);
      strip.setPixelColor(i + int(LED_COUNT/2), 0, 0, 0);
    }
    strip.show();
    delay(wait);
  }
  flag = true;
}

void flicker() {                          //-m9-FLICKER EFFECT
  uint8_t random_bright = random(0, 255);
  uint8_t random_delay = random(10, 100);
  uint8_t random_bool = random(0, random_bright);
  if (random_bool < 10) {
    for (uint8_t i = 0 ; i < LED_COUNT; i++ ) {
      if (!flag) break;
      strip.setPixelColor(i, random_bright, random_bright, random_bright);
    }
    strip.show();
    delay(random_delay);
  }
  flag = true;
}
