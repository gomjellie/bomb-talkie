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

int SRbut;
int SBbut;
int SGbut;
int SYbut;

unsigned long targetMillis = 0;
const long interval = 1000;
unsigned long previousMillis = 0;
int State = 0;
int buttonpushed = 0;

void setup() {
  for (int i = 9; i < 13; i++){
    pinMode(i, OUTPUT);
  }
  for (int i = 3; i < 7; i++){
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(PBuzzer, OUTPUT);
  noTone(PBuzzer);
  Wire.begin(7);
}

void Flash(int blinkLed) {
  unsigned long currentMillis = millis();
  if ( currentMillis >= targetMillis){
    targetMillis = currentMillis + interval;
    if (State == LOW) {
      State = HIGH;
      tone(PBuzzer, 250);
    } else {
      State = LOW;
      noTone(PBuzzer);
    }
  }
  else if (currentMillis < targetMillis) {
    //previousMillis = currentMillis;
    digitalWrite(blinkLed, State);
  }
}

void Off(int led) {
  digitalWrite(led, LOW);
  noTone(PBuzzer);
}

void Correct(){
  Wire.write('S');
}

void Wrong() {
  //신호 보낼 것@!@!@!@
  Wire.write('F');
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

void Rled_1() { //빨강 하나 반짝반짝 =>> 파란버튼 클릭
  while(buttonpushed == 0){
    updateSBut();
    Flash(Rled);
    if(SBbut == 0){Off(Rled); delay(10); buttonpushed = 1;}
    if(SRbut == 0 || SGbut ==0 || SYbut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
    Wire.write(4);
    //else if(Gbut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
    //else if(Ybut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
  }
  buttonpushed = 0;
}
void YGled_2() { //노랑, 초록 반짝반짝 =>> 빨강 초록 클릭
  int stack = 0;
  while(buttonpushed == 0){
    updateSBut();
    Flash(Yled);
    Flash(Gled);
     if (SRbut == 0){stack = 1;}
     if (SBbut == 0 || SGbut ==0 || SYbut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
     if (stack == 1){
       if (SGbut == 0){Off(Yled); Off(Gled); delay(10); Correct(); buttonpushed = 1;}
       if (SBbut == 0 || SRbut ==0 || SYbut == 0){Wrong(); delay(10); buttonpushed = 0; stack = 0; continue;}
     }
  }
}
 
void updateSBut(){
  SRbut = digitalRead(Rbut);
  SBbut = digitalRead(Bbut);
  SGbut = digitalRead(Gbut);
  SYbut = digitalRead(Ybut);
}
  
void loop() {
 Rled_1();
 delay(500);
 YGled_2();
}