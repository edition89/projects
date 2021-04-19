#define BLYNK_PRINT Serial                
#include <ESP8266WiFi.h>                // Подключаем библиотеку ESP82
#include <BlynkSimpleEsp8266.h>         // Подключаем библиотеку BlynkSimpleEsp8266

char auth[] = "qSGup94bF-N0lraMOva-0U_6i0GODUV5";
char ssid[] = "AceOfSpades";
char pass[] = "8JyxR7PhcDi";

int PWMA=5;
int PWMB=4;
int DA=0;
int DB=2;
 
void setup()
{ 
 Serial.begin(9600);                    // Установка последовательной связи на скорости 9600
 Blynk.begin(auth, ssid, pass); 
 pinMode(PWMA, OUTPUT);                 // Устанавливаем PWMA как выход
 pinMode(PWMB, OUTPUT);                 // Устанавливаем PWMB как выход
 pinMode(DA, OUTPUT);                   // Устанавливаем DA как выход
 pinMode(DB, OUTPUT);                   // Устанавливаем DB как выход
} 
 
void loop()
{ 
Blynk.run(); 
} 
 
// Считываем данные джойстика 
BLYNK_WRITE(V1) 
{
  int x = param[0].asInt(); 
  int y = param[1].asInt();  
  Serial.print(x);
  Serial.print(" ");
  Serial.println(y);
 
if(x==-1 && y==-1){             
  digitalWrite(PWMA, LOW); 
  digitalWrite(DA, LOW); 
     
  digitalWrite(PWMB, HIGH); 
  digitalWrite(DB, HIGH); 
 
}else if(x==-1 && y==0){        
  digitalWrite(PWMA, 450); 
  digitalWrite(DA, HIGH); 
  digitalWrite(PWMB, 450); 
  digitalWrite(DB, LOW); 
 
}else if(x==-1 && y==1){            
  digitalWrite(PWMA, LOW); 
  digitalWrite(DA, LOW); 
    
  digitalWrite(PWMB, HIGH); 
  digitalWrite(DB, LOW); 
 
}else if(x==0 && y==-1){        
  digitalWrite(PWMA, HIGH); 
  digitalWrite(DA, HIGH); 
     
  digitalWrite(PWMB, HIGH); 
  digitalWrite(DB, HIGH);
 
}else if(x==0 && y==0){        
  digitalWrite(PWMA, LOW); 
  digitalWrite(DA, LOW); 
     
  digitalWrite(PWMB, LOW); 
  digitalWrite(DB, LOW); 
 
}else if(x==0 && y==1){        
  digitalWrite(PWMA, HIGH); 
  digitalWrite(DA, LOW); 
    
  digitalWrite(PWMB, HIGH); 
  digitalWrite(DB, LOW); 
 
}else if(x==1 && y==-1){             
  digitalWrite(PWMA, HIGH); 
  digitalWrite(DA, HIGH); 
     
  digitalWrite(PWMB, LOW); 
  digitalWrite(DB, LOW); 
 
}else if(x==1 && y==0){        
  digitalWrite(PWMA, 450); 
  digitalWrite(DA, LOW); 
  digitalWrite(PWMB, 450); 
  digitalWrite(DB, HIGH); 
 
}else if(x==1 && y==1){        
  digitalWrite(PWMA, HIGH); 
  digitalWrite(DA, LOW); 
   
  digitalWrite(PWMB, LOW); 
  digitalWrite(DB, LOW);
 } 
}
