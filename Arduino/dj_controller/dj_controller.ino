#define CLK 15 //Энкодер
#define DT 14
#define SW 16

#define PIN        6 //Neopixel
#define NUMPIXELS 32

#define ARRENC 6 // Массив действий энкодера
#define DOUBLEARR 16 // Смешение на массив

#define ROWS 4 // Столбцы
#define COLS 4 // Строки

#include <TM1638lite.h>

#include "GyverEncoder.h"
#include "MIDIUSB.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

Encoder enc1(CLK, DT, SW, TYPE2);
TM1638lite tm(4, 7, 8);

byte byteTwo = 0; // Значения громкости deckA
byte byteThree = 0; // Значения громкости deckB
byte dval = 0; // Текущие значение кнопки
byte pval = 0; // Текущие значение потенциометра

bool arrEnc[ARRENC] = {true, true, true, true, true, true};

byte deckA[COLS][ROWS] = { //Массив состояния кнопок левой панели
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}
};

byte deckB[COLS][ROWS] = { //Массив состояния кнопок правой панели
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}
};

byte mainDigital[COLS][ROWS] = { //Массив состояния кнопок ценртальной панели
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}
};

byte potPrVal1[COLS][ROWS] = { //Массив состояниея потенциометров 1
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}
};

byte potPrVal2[COLS][ROWS] = { //Массив состояниея потенциометров 1
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}
};

byte pitch[2] = {0, 0}; //Чтение питча

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  tm.reset();
  pixels.begin();
  pixels.setBrightness(64);
}

void loop() {
  midiEventPacket_t rx;
  rx = MidiUSB.read();
  enc1.tick();

  if (enc1.isTurn()) {     // если был совершён поворот (индикатор поворота в любую сторону)
    if (enc1.isRight() && arrEnc[0]) changeEncoder(0, arrEnc[0]); // Удержание и поворт
    if (enc1.isLeft() && arrEnc[1]) changeEncoder(1, arrEnc[1]);

    if (enc1.isRightH() && arrEnc[2]) changeEncoder(2, arrEnc[2]); // Поворот
    if (enc1.isLeftH() && arrEnc[3]) changeEncoder(3, arrEnc[3]);

    if (enc1.isSingle() && arrEnc[4]) changeEncoder(4, arrEnc[4]); // Двойной клик
    if (enc1.isDouble() && arrEnc[5]) changeEncoder(5, arrEnc[5]); // Тройной клик

    for (byte i = 0; i < ARRENC; i++ )if (!arrEnc[i]) changeEncoder(i, arrEnc[i]);

  }

  if (rx.header != 0) { //VuMetr
    if (rx.byte1 == 191 && rx.byte2 == 0) byteTwo = rx.byte3;
    if (rx.byte1 == 191 && rx.byte2 == 1) byteThree = rx.byte3;
    vuMetr();
    Serial.print("Received: ");
      Serial.print(rx.header, HEX);
      Serial.print("-");
      Serial.print(rx.byte1, HEX);
      Serial.print("-");
      Serial.print(rx.byte2, HEX);
      Serial.print("-");
      Serial.println(rx.byte3, HEX);
  }


  //Аналоговые значения. Main1
  for (byte col = 0; col < COLS; col++) {       //-Цикл чтения значений потенциометров Столбцы
    for (byte row = 0; row < ROWS; row++) {       //-Цикл чтения значений потенциометров Строки
      //pval = analogRead(*Значения с модуля мультиплексера аналоговых значений*) / 8;
      if (abs(pval - potPrVal1[col][row]) > 10) {                              //--Если текущее значение отл. от прошлого
        controlChange(3, 1 * col + row, pval);
        potPrVal1[col][row] = pval;
      }
    }
  }

  //Аналоговые значения. Main2
  for (byte col = 0; col < COLS; col++) {       //-Цикл чтения значений потенциометров Столбцы
    for (byte row = 0; row < ROWS; row++) {       //-Цикл чтения значений потенциометров Строки
      //pval = analogRead(*Значения с модуля мультиплексера аналоговых значений*) / 8;
      if (abs(pval - potPrVal2[col][row]) > 10) {                              //--Если текущее значение отл. от прошлого
        controlChange(4, DOUBLEARR + 1 * col + row, pval);
        potPrVal2[col][row] = pval;
      }
    }
  }

  //Цифровые значения. DeckA
  for (byte col = 0; col < COLS; col++) {                          //-Цикл чтения значений кнопок Столбцы
    for (byte row = 0; row < ROWS; row++) {                         //-Цикл чтения значений кнопок Строки
      //dval = *Значения с модуля мультиплексера цифровых значений*
      if ( dval == HIGH && deckA[col][row] == LOW ) {
        noteOn(0, 1 * col + row , 64);
        MidiUSB.flush();
      }
      if ( dval == LOW && deckA[col][row] == HIGH ) {
        noteOff(0, 1 * col + row, 64);
        MidiUSB.flush();
      }
      deckA[col][row] = dval;
    }
  }

  //Цифровые значения. DeckB
  for (byte col = 0; col < COLS; col++) {                          //-Цикл чтения значений кнопок Столбцы
    for (byte row = 0; row < ROWS; row++) {                         //-Цикл чтения значений кнопок Строки
      //dval = *Значения с модуля мультиплексера цифровых значений*
      if ( dval == HIGH && deckB[col][row] == LOW ) {
        noteOn(1, DOUBLEARR + 1 * col + row , 64);
        MidiUSB.flush();
      }
      if ( dval == LOW && deckB[col][row] == HIGH ) {
        noteOff(1, DOUBLEARR + 1 * col + row, 64);
        MidiUSB.flush();
      }
      deckB[col][row] = dval;
    }
  }

  //Цифровые значения. DeckB
  for (byte col = 0; col < COLS; col++) {                          //-Цикл чтения значений кнопок Столбцы
    for (byte row = 0; row < ROWS; row++) {                         //-Цикл чтения значений кнопок Строки
      //dval = *Значения с модуля мультиплексера цифровых значений*
      if ( dval == HIGH && mainDigital[col][row] == LOW ) {
        noteOn(2, 2 * DOUBLEARR + 1 * col + row , 64);
        MidiUSB.flush();
      }
      if ( dval == LOW && mainDigital[col][row] == HIGH ) {
        noteOff(2, 2 * DOUBLEARR + 1 * col + row, 64);
        MidiUSB.flush();
      }
      mainDigital[col][row] = dval;
    }
  }
}
