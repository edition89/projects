#define light 4
#define volume 7
#define r 3
#define g 5
#define b 6

bool flag = false;

void setup() {
  Serial.begin(9600);
  pinMode(light, INPUT);
  pinMode(volume, INPUT);
}

void loop() {
  analogWrite(r, map(analogRead(A0), 0, 1023, 0, 255) * flag);
  analogWrite(g, map(analogRead(A1), 0, 1023, 0, 255) * flag);
  analogWrite(b, map(analogRead(A2), 0, 1023, 0, 255) * flag);
  if(digitalRead(volume) == true && digitalRead(light) == true){
    delay(300); 
    for(int i = 0; i < 500; i++){
      delay(1);
      if(digitalRead(volume) == true && digitalRead(light) == true){
        flag = !flag;
        break;
      }
    }
       
  }
  if(digitalRead(light) == false) flag = false;
  Serial.print(map(analogRead(r), 0, 1023, 0, 255));
  Serial.print("          ");
  Serial.println(flag);
}
