#include "Wire.h"

#define Rled 12
#define Bled 11
#define Gled 10
#define Yled 9

#define Rbut 6
#define Bbut 5
#define Gbut 4
#define Ybut 3

#define PBuzzer 2
const long interval = 1000;
unsigned long previousMillis = 0;
unsigned long currentMillis = millis();
int State = 0;

void setup() {
  Serial.begin(9600);

  for (int i = 9; i < 13; i++)
    pinMode(i, OUTPUT);

  pinMode(PBuzzer, OUTPUT);
  noTone(PBuzzer);

  for (int i = 3; i < 7; i++)
    pinMode(i, INPUT);

  Wire.begin();
}

void Flash(int blinkLed) {

  if (currentMillis - previousMillis >= interval) {


    if (State == LOW) {
      State = HIGH;
      tone(PBuzzer, 250);
    } else {
      State = LOW;
      noTone(PBuzzer);
    }
    digitalWrite(blinkLed, State);
    digitalWrite(PBuzzer, State);
    Serial.print(blinkLed);
    Serial.println(" is working");
    previousMillis = currentMillis;

  }
}

void Off(int led) {
  digitalWrite(led, LOW);
}

void Wrong() {
  //신호 보낼 것@!@!@!@
  tone(PBuzzer, 500);
  delay(200);
  noTone(PBuzzer);
  delay(200);
  tone(PBuzzer, 500);
  delay(200);
  noTone(PBuzzer);
  delay(200);
  tone(PBuzzer, 500);
  delay(200);
  noTone(PBuzzer);
}

void Rbut_start() {
  boolean switch1 = 0;
  boolean switch2 = 0;

 while(true){
   Flash(Rled);//빨강버튼 반짝반짝
   if (Bbut==0) break;
   else if (Rbut == 0) {Wrong(); continue;}
   else if (Gbut == 0) {Wrong(); continue;}
   else if (Ybut == 0) {Wrong(); continue;}
 }
//Off(Rled);

}

void loop() {
  Rbut_start();
}