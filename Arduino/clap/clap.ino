int Count=0; //Переменная для хранения значений с датчика звука
int Relay=1; //Переменная для хранения состояния реле
void setup() {
  pinMode(13, OUTPUT); //переводим пин 3 в  режим выхода
  pinMode(9, OUTPUT);
}
  
void loop() {
  Count=analogRead(A1); //читаем значения

  if(Relay == 1)
  {
    int sensorValue = analogRead(A0);
  // 
  float voltage = sensorValue - 40 ;
  if (voltage <= 2)
  {
    voltage=0;
  }
   if (voltage >= 255)
  {
    voltage=255;
  }
  // 
  Serial.println(voltage);
  analogWrite(9, voltage);
  delay(30);
  }
  if(Relay == 0)
  {
    analogWrite(9, LOW);
  }
  if(Count > 2 )
  {
    delay(250); //ожидаем 250 милисекунд для повторного хлопка
    for(int t=0; t<=500; t++)
    {
      delay(1);
      Count=analogRead(A1); //считываем значение
      if(Count > 2 )
      {
        Relay=!Relay; //меняем состояние реле
        break; //Выходим из цикла после второго хопка
        delay(100); //Пауза
      }
    }
  }
digitalWrite(13,Relay);
}
