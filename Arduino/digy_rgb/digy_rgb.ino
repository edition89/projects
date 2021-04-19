#include <Adafruit_NeoPixel.h>

#define PIN 1
#define LED_COUNT 30

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

uint8_t ledMode = 0;
bool flag = true;

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(255);
  GIMSK = 0b00100000;
  PCMSK = 0b00000001;
  sei();
}

void loop() {
  switch (ledMode) {
    case  0: colorWipe(strip.Color(255, 0, 0), 50, 1); break;            // Красный
    case  2: colorWipe(strip.Color(0, 255, 0), 50, 1); break;            // Зеленый
    case  4: colorWipe(strip.Color(0, 0, 255), 50, 1); break;            // Синий
    case  6: colorWipe(strip.Color(255, 255, 0), 50, 2); break;            // Желтый
    case  8: colorWipe(strip.Color(255, 0, 255), 50, 2); break;            // Фиолетовый
    case  10: colorWipe(strip.Color(0, 255, 255), 50, 2); break;            // Бюрюзовый
    case  12: colorWipe(strip.Color(255, 255, 255), 50, 2); break;            // Белый
/*
    case  14: theaterChase(strip.Color(255, 0, 0), 50); break;            // Красные прыжки
    case  16: theaterChase(strip.Color(0,   255,   0), 50); break;            // Зеленые прыжки
    case  18: theaterChase(strip.Color(  0,   0, 127), 50); break;            // Синие прыжки
    case  20: theaterChase(strip.Color(255, 255, 0), 50); break;            // Желтые прыжки
    case  22: theaterChase(strip.Color(255,   0,   255), 50); break;            // Фиолетовые прыжки
    case  24: theaterChase(strip.Color(  0,   255, 255), 50); break;            // Бюрюзовые прыжки
    case  26: theaterChase(strip.Color(  255,   255, 255), 50); break;            // Белые прыжки
*/    
    case  14: rainbow(20); break;            // Радуга
    case  16: rainbowCycle(20); break;            // Радуга круговая

    /*
    case  32: theaterChaseRainbow(50); break;            // прыжки радуга

    case  34: pixel(strip.Color(255, 0, 0), 50);; break;            // Красный огонек
    case  36: pixel(strip.Color(0, 255, 0), 50); break;            // Зеленый огонек
    case  38: pixel(strip.Color(0, 0, 255), 50); break;            // Синий огонек
    case  40: pixel(strip.Color(255, 255, 0), 50); break;            // Желтый огонек
    case  42: pixel(strip.Color(255, 0, 255), 50); break;            // Фиолетовый огонек
    case  44: pixel(strip.Color(0, 255, 255), 50); break;            // Бюрюзовый огонек
    case  46: pixel(strip.Color(255, 255, 255), 50); break;            // Белый огонек

    case  48: threePixel(strip.Color(255, 0, 0), 50);; break;            // Красные огонки
    case  50: threePixel(strip.Color(0, 255, 0), 50); break;            // Зеленые огонки
    case  52: threePixel(strip.Color(0, 0, 255), 50); break;            // Синие огонки
    case  54: threePixel(strip.Color(255, 255, 0), 50); break;            // Желтые огонки
    case  56: threePixel(strip.Color(255, 0, 255), 50); break;            // Фиолетовые огонки
    case  58: threePixel(strip.Color(0, 255, 255), 50); break;            // Бюрюзовые огонки
    case  60: threePixel(strip.Color(255, 255, 255), 50); break;            // Белые огонки

    case  62: doublePixel(strip.Color(255, 0, 0), 50);; break;            // Красный двойной огонек
    case  64: doublePixel(strip.Color(0, 255, 0), 50); break;            // Зеленый двойной огонек
    case  66: doublePixel(strip.Color(0, 0, 255), 50); break;            // Синий двойной огонек
    case  68: doublePixel(strip.Color(255, 255, 0), 50); break;            // Желтый двойной огонек
    case  70: doublePixel(strip.Color(255, 0, 255), 50); break;            // Фиолетовый двойной огонек
    case  72: doublePixel(strip.Color(0, 255, 255), 50); break;            // Бюрюзовый двойной огонек
    case  74: doublePixel(strip.Color(255, 255, 255), 50); break;            // Белый двойной огонек
*/
    case  18: flicker(); break;            // случайный стробоскоп
    case  20: colorWipe(strip.Color(0, 0, 0), 50, 1); break; // Выкл
  }
}


ISR(PCINT0_vect) {
  colorWipe(strip.Color(0, 0, 0), 50, 1);
  ledMode++;
  if (ledMode > 21) ledMode = 0;
  flag = !flag;
}
