/*
 * pin 3 dist in 1
 * pin 4 dist in 2
 * pin 5 motor in 4
 * pin 6 motor in 3
 * pin 7 dist in 3
 * pin 8 dist in 4
 * pin 9 motor in 2
 * pin 10 motor in 1
 * pin 11 servo
 * pin 12 Trig
 * pin 13 Echo
 * 
 * OUT 2 and OUT 4 Vcc, OUT 1 and OUT 3 GND FORWARD
 * OUT 1 and OUT 3 Vcc, OUT 2 and OUT 4 GND BACK
 */

 #define OUT1 10
 #define OUT2 9
 #define OUT3 6
 #define OUT4 5

 #define D1 3
 #define D1 4
 #define D1 7
 #define D1 8

 #include <Ultrasonic.h>
 #include <Servo.h>
 
 Ultrasonic ultrasonic(12, 13);
 Servo myservo; 
 
 int distance;
 int pos = 0;
 int left;
 int right;


void dist() {
distance = ultrasonic.read();
delay(10); 
}

void pusk() {
  digitalWrite(OUT1, LOW);
  digitalWrite(OUT3, LOW);
  for(int i = 0; i < 255; i += 10) {
    analogWrite(OUT2, i);
    analogWrite(OUT4, i);
    delay(10);
  }
}

void setup() {
  myservo.attach(11);
  myservo.write(90);
  delay(5000);
  Serial.begin(9600);
}

void loop() {
  Serial.println(ultrasonic.read());
  digitalWrite(OUT2, HIGH);
  digitalWrite(OUT4, HIGH);
  digitalWrite(OUT1, LOW);
  digitalWrite(OUT3, LOW);
  delay(200);
  if(ultrasonic.read() < 30) {
  myservo.write(30);
  delay(300); 
  left = ultrasonic.read();   
  myservo.write(150);
  delay(300); 
  right = ultrasonic.read(); 
  delay(200);
  myservo.write(90);
  digitalWrite(OUT2, LOW);
  digitalWrite(OUT4, LOW);
  digitalWrite(OUT1, HIGH);
  digitalWrite(OUT3, HIGH);
  delay(1000);
    if(left < right - 5) {  
    digitalWrite(OUT3, LOW);
    digitalWrite(OUT4, LOW);
    digitalWrite(OUT1, LOW);
    digitalWrite(OUT2, HIGH); 
    delay(1000);
    }
    else {
    digitalWrite(OUT2, LOW);
    digitalWrite(OUT1, LOW);
    digitalWrite(OUT3, LOW);
    digitalWrite(OUT4, HIGH); 
    delay(1000);
    } 
  myservo.write(90);
  }
}
