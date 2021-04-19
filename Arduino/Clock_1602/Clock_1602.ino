//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

unsigned long time;

byte l_on[8] = 
{

  B00000,
  B00000,
  B00011,
  B00011,
  B00011,
  B00011,
  B00000,
  B00000
};

byte r_on[8] = 
{

  B00000,
  B00000,
  B11000,
  B11000,
  B11000,
  B11000,
  B00000,
  B00000
};

byte l_off[8] = 
{

  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte r_off[8] = 
{

  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};


byte LT[8] = 
{

  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte UB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte RT[8] =
{

  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte LL[8] =
{


  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111
};
byte LB[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};
byte LR[8] =
{


  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100
};
byte MB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte block[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

void setup()
{  
  lcd.init();                      // initialize the lcd 

  lcd.createChar(0,LT);
  lcd.createChar(1,UB);
  lcd.createChar(2,RT);
  lcd.createChar(3,LL);
  lcd.createChar(4,LB);
  lcd.createChar(5,LR);
  lcd.createChar(6,MB);
  lcd.createChar(7,block);
  /*lcd.createChar(8,l_on);
  lcd.createChar(9,r_on);
  lcd.createChar(10,l_off);
  lcd.createChar(11,r_off);*/
  
  // Print a message to the LCD.
  lcd.backlight();
   
  lcd.clear();
  Serial.begin(9600);
  displayNumber(0,0,0,0);
   
}


int mine, sec;
void loop()
{
  time = millis();
  time = time / 1000;
  mine = (time / 60) % 60;
  sec = time % 60;
  displayNumber(mine / 10, mine % 10, sec / 10, sec % 10);
  
}
void displayNumber(int decmine, int mine, int decsec, int sec){
    
    
    printDigits( decmine, 1);
    printDigits( mine, 5);
    printDigits( decsec, 9);
    printDigits( sec, 13);
    if(millis() % 1000 > 500) ON();
    else OFF();
    
}

void ON(){
  lcd.setCursor(8,0); 
  lcd.print("\xA5");
  lcd.setCursor(8,1); 
  lcd.print("\xA5");
}

void OFF(){
  lcd.setCursor(8,0); 
  lcd.print(" ");
  lcd.setCursor(8,1); 
  lcd.print(" ");
}

void custom0(int x){ 

  lcd.setCursor(x,0); 
  lcd.write(0);  
  lcd.write(1);  
  lcd.write(2);
  lcd.setCursor(x, 1); 
  lcd.write(3);  
  lcd.write(4);  
  lcd.write(5);
}

void custom1(int x){
  lcd.setCursor(x,0);
  lcd.write(1);
  lcd.write(2);
  lcd.print(" ");
  lcd.setCursor(x,1);
  lcd.write(4);
  lcd.write(7);
  lcd.write(4);
}

void custom2(int x){
  lcd.setCursor(x,0);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(4);
}

void custom3(int x){
  lcd.setCursor(x,0);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(4);
  lcd.write(4);
  lcd.write(5); 
}

void custom4(int x){
  lcd.setCursor(x,0);
  lcd.write(3);
  lcd.write(4);
  lcd.write(7);
  lcd.setCursor(x, 1);
  lcd.print(" ");
  lcd.print(" ");
  lcd.write(7);
}

void custom5(int x){
  lcd.setCursor(x,0);
  lcd.write(3);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, 1);
  lcd.write(4);
  lcd.write(4);
  lcd.write(5);
}

void custom6(int x){
  lcd.setCursor(x,0);
  lcd.write(0);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
}

void custom7(int x){
  lcd.setCursor(x,0);
  lcd.write(1);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.print(" ");
  lcd.print(" ");
  lcd.write(7);
}

void custom8(int x){
  lcd.setCursor(x,0);
  lcd.write(0);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
}

void custom9(int x){
  
  lcd.setCursor(x,0);
  lcd.write(0);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, 1);
  lcd.print(" ");
  lcd.print(" ");
  lcd.write(7);

}
void printDigits(int digits, int x){

  if (digits == 0) custom0(x);
  else if (digits == 1) custom1(x);
  else if (digits == 2) custom2(x);
  else if (digits == 3) custom3(x);
  else if (digits == 4) custom4(x);
  else if (digits == 5) custom5(x);
  else if (digits == 6) custom6(x);
  else if (digits == 7) custom7(x);
  else if (digits == 8) custom8(x);
  else if (digits == 9) custom9(x); 

}
