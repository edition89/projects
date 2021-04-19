#define CLK 7
#define DT 8
#define SW 9
#include "GyverEncoder.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
Encoder enc1(CLK, DT, SW);

#define PIN            6
#define NUMPIXELS      8*2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x27,20,4);

int value = 0;
int R = 0;
int G = 0;
int B = 0;
int var = 1;
bool CASE = true;


void setup() {
lcd.init(); 
  
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

pixels.begin();

Serial.begin(9600);
enc1.setType(TYPE2);   

  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("PUSH BUTTON");
  lcd.setCursor(2,1);
  lcd.print("VALUE = ");
  tri(value + 1);
}
void loop() {
enc1.tick();
if (enc1.isRight()) value--;
if (enc1.isLeft())  value++;
if(value < 0) value = NUMPIXELS - 1;
if(value > NUMPIXELS - 1) value = 0;
if (enc1.isPress()) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("$$CHOOSE COLOR$$");
  lcd.setCursor(4,1);
  lcd.print("RED = ");
  lcd.setCursor(10,1);
  lcd.print(R);
  while(CASE) {   
    switch(var){
    case 1:
      enc1.tick();
      if (enc1.isRight()) R -= 5;
      if (enc1.isLeft())  R += 5;
      R = predel(R);
      if (enc1.isTurn()) { 
      lcd.setCursor(4,1);
      lcd.print("RED = ");
      tri(R);
      }
      if(enc1.isPress()) {
        var++;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("$$CHOOSE COLOR$$");
        lcd.setCursor(2,1);
        lcd.print("GREEN = ");
        lcd.setCursor(10,1);
        lcd.print(G);
      }
    break;
    case 2:
      enc1.tick();
      if (enc1.isRight()) G -= 5;
      if (enc1.isLeft())  G += 5;
      G = predel(G);
      if (enc1.isTurn()) { 
      lcd.setCursor(2,1);
      lcd.print("GREEN = ");
      tri(G);
      }
      if(enc1.isPress()) {
        var++;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("$$CHOOSE COLOR$$");
        lcd.setCursor(3,1);
        lcd.print("BLUE = ");
        lcd.setCursor(10,1);
        lcd.print(B);
      }
      break;
      case 3:
      enc1.tick();
      if (enc1.isRight()) B -= 5;
      if (enc1.isLeft())  B += 5;
      B = predel(B);
      if (enc1.isTurn()) { 
      lcd.setCursor(3,1);
      lcd.print("BLUE = ");
      tri(B);
      }
      if(enc1.isPress()) {
      var = 1;
      CASE = !CASE;
      }  
      break;
  }
  }
  CASE = !CASE;
  setcolor(value, R, G, B);
  R = 0;
  G = 0;
  B = 0;
  
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("PUSH BUTTON");
  lcd.setCursor(2,1);
  lcd.print("VALUE = ");
  tri(value + 1);
}
  if (enc1.isTurn()) {       // если был совершён поворот (индикатор поворота в любую сторону)
  tri(value + 1);
  }  
}


int predel(int a) {
  if(a > 255) a = 0;
  if(a < 0) a = 255;
  return a;
}

void setcolor(int num, int r, int g, int b) {
  pixels.setPixelColor(num, pixels.Color(r,g,b));
    pixels.show();
}



void tri(int a) {
  lcd.setCursor(10,1);
  lcd.print(a/100);
  lcd.setCursor(11,1);
  lcd.print((a/10)%10);
  lcd.setCursor(12,1);
  lcd.print(a%10);
}
/*
if (enc1.isRightH()) value += 5;  // если было удержание + поворот направо, увеличиваем на 5
if (enc1.isLeftH()) value -= 5; // если было удержание + поворот налево, уменьшаем на 5  
if (enc1.isTurn()) {       // если был совершён поворот (индикатор поворота в любую сторону)
Serial.println(value);   // выводим значение при повороте
} */
