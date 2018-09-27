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
int State = 0;
int buttonpushed = 0;
void setup() {
  for (int i = 9; i < 13; i++)
    pinMode(i, OUTPUT);
  for (int i = 3; i < 7; i++)
    pinMode(i, INPUT);
  pinMode(PBuzzer, OUTPUT);
  noTone(PBuzzer);
  Wire.begin();
}

void Flash(int blinkLed) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    if (State == LOW) {
      State = HIGH;
      tone(PBuzzer, 250);
    } else {
      State = LOW;
      noTone(PBuzzer);
    }
    digitalWrite(blinkLed, State);
  }
}

void Off(int led) {
  digitalWrite(led, LOW);
  noTone(PBuzzer);
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
  int stack = 0;
 while(true){
   Flash(Rled);//빨강버튼 반짝반짝
   if (buttonpushed) {
     if(Bbut==HIGH){
       buttonpushed = 0;
     }
   } else{
     if (Bbut==LOW){
       buttonpushed = 1;
       Off(Rled);
       break;
     }
   else if (Rbut == 0) {Wrong(); continue;}
   else if (Gbut == 0) {Wrong(); continue;}
   else if (Ybut == 0) {Wrong(); continue;}
  }
 }

 buttonpushed = 0;
 delay(500);

 while(true){
   Flash(Yled);
   Flash(Gled);
   if (buttonpushed) {
     if(Rbut==HIGH){
       buttonpushed = 0;
     }
   } else{
     if (Rbut==LOW){
       buttonpushed = 1;
       stack = 1;
       if (stack = 1){
        if (Gbut==LOW) {Off(Yled); Off(Gled); break;}
        else if (Rbut == 0) {Wrong(); stack = 0; continue;}
        else if (Bbut == 0) {Wrong(); stack = 0; continue;}
        else if (Ybut == 0) {Wrong(); stack = 0; continue;}
       }
     }
    }
  }
  tone(PBuzzer, 700);
  delay(1000);
  noTone(PBuzzer);
}

void loop() {
  Rbut_start();//빨강버튼 반짝반짝
}