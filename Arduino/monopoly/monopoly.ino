#if 1

#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>

#define MINPRESSURE 200
#define MAXPRESSURE 1000

#define RST_PIN         19
#define SS_PIN          10

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP = 6, XM = A2, YP = A1, YM = 7; //ID=0x9341
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
MFRC522 mfrc522(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

long number = 0;
long numberOld;
unsigned long hex = 0;
int pixel_x, pixel_y;     //Touch_getXY() updates global vars
unsigned int flag = 0;
unsigned int arr[8] = {0};


//Переменные
byte sector         = 0;
byte blockAddr      = 1;
byte trailerBlock   = 3;
byte status;
byte buffer[18];
byte size = sizeof(buffer);

byte dataBlock[]    = {
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};

bool Touch_getXY(void)
{
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);   //because TFT control pins
  digitalWrite(XM, HIGH);
  bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
  if (pressed) {
    pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
    pixel_y = map(p.y, TS_TOP, TS_BOT, tft.height(), 0);
  }
  return pressed;
}

void cut_number(long number) {
  tft.fillRect(0, 210, 320, 40, WHITE);
  tft.fillRect(0, 180, 40, 100, WHITE);
  int arr_num[5];
  if (number < 0) {
    number = number * -1;
    tft.fillRect(23, 205, 7, 40, BLUE);
    tft.fillTriangle(20, 245, 26, 265, 33, 245, BLUE);
  }
  else if (number > 0) {
    tft.fillRect(23, 205, 7, 40, RED);
    tft.fillTriangle(20, 205, 26, 185, 33, 205, RED);
  }
  else if (number == 0) {
    tft.fillRect(23, 225, 7, 20, BLUE);
    tft.fillRect(23, 205, 7, 20, RED);
    tft.fillTriangle(20, 245, 26, 265, 33, 245, BLUE);
    tft.fillTriangle(20, 205, 26, 185, 33, 205, RED);
  }

  tft.setTextColor(BLACK);
  tft.setTextSize(5);
  for (int i = 5; i >= 0; i--) {
    arr_num[i - 1] = number % 10;
    number = number / 10;
  }
  for (int i = 0; i < 5; i++) {
    tft.setCursor(50 + 52 * i, 210);
    tft.print(arr_num[i]);
  }
}

void change_text(unsigned int flag) {
  tft.fillRect(0, 330, 320, 60, WHITE);
  tft.setTextColor(BLACK);
  tft.setTextSize(7);
  if (flag == 0) {
    tft.setCursor(58, 330);
    tft.print("OBMEN");
  }
  else if (flag == 1) {
    tft.setCursor(58, 330);
    tft.print("SCHET");
  }
  else if (flag == 2) {
    tft.setCursor(58, 330);
    tft.print("SBROS");
  }
  else if (flag == 3) {
    tft.setCursor(80, 330);
    tft.print("NO $");
  }
  else if (flag == 4) {
    tft.setCursor(80, 330);
    tft.print("FAIL");
  }
  else if (flag == 5) {
    tft.setCursor(15, 330);
    tft.print("SUCCESS");
  }
}

void exchange() {
  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  // Аутентификация
  
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    change_text(4);
  }
  ////////////////////////////
  // Читаем данные из блока
  status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    change_text(4);
  }
  dump_byte_array(buffer, 16);

  for (int i = 0; i < 4; i++) {
    hex = hex << 8 | dataBlock[12 + i];
  }
  switch (flag) {
    case 0:
      if (number * -1 > hex) {
        change_text(3);
        goto jump;
      }
      else {
        hex = hex + number;
        if (hex > 99999) hex = 99999;
        pereschet();
      }
      break;
    case 1:
      cut_number(hex);
      number = hex;
      change_text(5);
      goto jump;
      break;
    case 2:
      dataBlock[12] = {0x00};
      dataBlock[13] = {0x00};
      dataBlock[14] = {0x05};
      dataBlock[15] = {0xDC};
      break;
  }
  // Аутентификация
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    change_text(4);
  }
  // Записываем данные в блок
  status = mfrc522.MIFARE_Write(blockAddr, dataBlock, 16);
  if (status != MFRC522::STATUS_OK) {
    change_text(4);
  }
  // Читаем данные снова, чтобы проверить, что запись прошла успешно
  status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    change_text(4);
  }
  byte count = 0;
  for (byte i = 0; i < 16; i++) {
    if (buffer[i] == dataBlock[i])
      count++;
  }
  if (count == 16) {
    change_text(5);
    jump:
    flag = false;
    delay(1000);
  }
  else {
    change_text(4);
  }
  number = 0;
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}


void pereschet() {
  for (int i = 0; i < 8; i++) {
    arr[i] = hex % 16;
    hex /= 16;
  }
  for (int i = 0; i < 4; i++) {
    dataBlock[12 + i] = arr[7 - 1 - i * 2] | arr[7 - i * 2] << 4;
  }
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    dataBlock[i] = buffer[i];
  }
}

void setup(void)
{    
  Serial.begin(9600);  
  SPI.begin();
  mfrc522.PCD_Init();
  uint16_t ID = tft.readID();
  for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

  dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_43dB);
  mfrc522.PCD_AntennaOn ();
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  Serial.println("Calibrate for your Touch Panel");
  if (ID == 0xD3D3) ID = 0x9486; // write-only shield
  tft.begin(ID);
  tft.cp437(true);
  tft.setRotation(0);            //PORTRAIT

  tft.fillScreen(WHITE);
  for (int i = 0; i < 480; i += 3) {
    for (int j = 0; j < 320; j += 3) {
      tft.drawPixel(j, i, 0xEF7D);
    }
  }
  tft.fillRoundRect(20, 60, 280, 80, 3, RED);
  tft.fillCircle(160, 60, 46, RED);
  tft.fillRoundRect(24, 64, 272, 72, 2, WHITE);
  tft.fillCircle(160, 60, 42, WHITE);
  tft.fillRoundRect(28, 68, 264, 64, 1, RED);
  tft.fillCircle(160, 60, 38, RED);
  tft.setCursor(40, 85);
  tft.setTextColor(WHITE);
  tft.setTextSize(5);
  tft.print("MONOPOLY");
  for (int i = 0; i < 5; i++) {
    tft.fillTriangle(40 + 52 * i, 190, 63 + 52 * i, 160, 86 + 52 * i, 190, RED);    
    tft.drawLine(63 + 52 * i, 160, 86 + 52 * i, 190, 0xB000);
    tft.drawLine(63 + 52 * i, 161, 85 + 52 * i, 190, 0xB000);
    tft.drawLine(63 + 52 * i, 162, 84 + 52 * i, 190, 0xB000);
    tft.drawLine(40 + 52 * i, 190, 63 + 52 * i, 160, 0xFAAA);
    tft.drawLine(41 + 52 * i, 190, 63 + 52 * i, 161, 0xFAAA);
    tft.drawLine(42 + 52 * i, 190, 63 + 52 * i, 162, 0xFAAA);
  }
  for (int i = 0; i < 5; i++) {
    tft.fillTriangle(40 + 52 * i, 260, 63 + 52 * i, 290, 86 + 52 * i, 260, RED);
  }
  change_text(flag);
  cut_number(number);
/*
  for (int i = 0; i < 480; i += 20) {
    for (int j = 0; j < 320; j += 20) {
      tft.drawRect(j, i, 20, 20, GREEN);
    }
  }
*/
  tft.fillRoundRect(-5, 430, 140, 55, 5, RED);
  tft.fillRoundRect(140, 430, 40, 55, 5, RED);
  tft.fillRoundRect(185, 430, 140, 55, 5, RED);
  tft.fillRoundRect(-5, 433, 137, 55, 3, WHITE);
  tft.fillRoundRect(143, 433, 34, 55, 3, WHITE);
  tft.fillRoundRect(188, 433, 140, 55, 3, WHITE);
  tft.setTextSize(4);
  tft.setCursor(7, 443);
  tft.print("OBMEN");
  tft.setCursor(150, 443);
  tft.print("S");
  tft.setCursor(197, 443);
  tft.print("SCHET");
}

/* two buttons are quite simple
*/
void loop(void)
{
  if (Touch_getXY()) {
    if (pixel_y > 313 && pixel_y < 341 && flag == 0) {
      if (pixel_x > 34 && pixel_x < 78 && number < 90000) number = number + 10000;
      else if (pixel_x > 87 && pixel_x < 128 && number < 99000) number = number + 1000;
      else if (pixel_x > 140 && pixel_x < 180 && number < 99900) number = number + 100;
      else if (pixel_x > 193 && pixel_x < 230 && number < 99990) number = number + 10;
      else if (pixel_x > 241 && pixel_x < 285 && number < 99999) number = number + 1;
    }
    if (pixel_y > 212 && pixel_y < 238 && flag == 0) {
      if (pixel_x > 34 && pixel_x < 78 && number > -90000) number = number - 10000;
      else if (pixel_x > 87 && pixel_x < 128 && number > -99000) number = number - 1000;
      else if (pixel_x > 140 && pixel_x < 180 && number > -99900) number = number - 100;
      else if (pixel_x > 193 && pixel_x < 230 && number > -99990) number = number - 10;
      else if (pixel_x > 241 && pixel_x < 285 && number > -99999) number = number - 1;
    }
    if (pixel_y > 27 && pixel_y < 66 && pixel_x > -4 && pixel_x < 118) {
      flag = 0;
      number = 0;
      change_text(flag);
    }
    if (pixel_y > 234 && pixel_y < 315 && pixel_x > 9 && pixel_x < 27) {
      flag = 0;
      number = number * -1;
      change_text(flag);
    }
    if (pixel_y > 30 && pixel_y < 64 && pixel_x > 176 && pixel_x < 302) {
      flag = 1;
      number = 0;
      change_text(flag);
    }
    if (pixel_y > 30 && pixel_y < 59 && pixel_x > 134 && pixel_x < 163) {
      flag = 2;
      number = 1500;
      change_text(flag);
    }
    if (!(numberOld == number)) cut_number(number);
  Serial.print("Number: "); 
  Serial.println(number);
  }
  numberOld = number;
  exchange();
  //Serial.println(number);
  //Serial.println(flag);
  //Serial.println(pixel_x);
  //Serial.println(pixel_y);
}
#endif
