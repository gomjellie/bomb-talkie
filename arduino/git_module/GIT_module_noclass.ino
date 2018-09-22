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

void setup() {
  Serial.begin(9600);

  for (int i = 9; i < 13; i++)
    pinMode(i, OUTPUT);

  pinMode(PBuzzer, OUTPUT);
  digitalWrite(PBuzzer, LOW);

  for (int i = 3; i < 7; i++)
    pinMode(i, INPUT);

  Wire.begin();
}

void Flash(int blinkLed) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    if (State == LOW) {
      State = HIGH;
      tone(PBuzzer, 250);
    } else {
      State = LOW;
      noTone(PBuzzer);
    }
    digitalWrite(blinkLed, State);
    digitalWrite(PBuzzer, State);

  }
}

void Off(int led) {
  digitalWrite(led, LOW);
}

void Wrong() {
  digitalWrite(PBuzzer, HIGH);
  delay(200);
  digitalWrite(PBuzzer, LOW);
  delay(200);
  digitalWrite(PBuzzer, HIGH);
  delay(200);
  digitalWrite(PBuzzer, LOW);
  delay(200);
  digitalWrite(PBuzzer, HIGH);
  delay(200);
  digitalWrite(PBuzzer, LOW);
}

void Rbut_start() {
  boolean switch1 = 0;
  boolean switch2 = 0;


  Flash(Rled); //빨강버튼 반짝반짝

  while (true) {
    while (true) {
      if (digitalRead(Bbut) == LOW) break;
      else if (digitalRead(Gbut) == LOW) Wrong();
      else if (digitalRead(Rbut) == LOW) Wrong();
      else if (digitalRead(Ybut) == LOW) Wrong();
// 1차, 파랑버튼 누르기 완료     
    }
    Off(Rled); //빨강끄기

    delay(1000);

    Flash(Gled); //초록 켜기
    delay(500);
    Flash(Yled); //노랑 켜기
    while (true) {
      if (digitalRead(Rbut) == LOW) {
        switch1 = 1;
        continue;
      } //빨강, 초록순으로 누르기
      if (switch1 == 1) {
        if (digitalRead(Gbut) == LOW) break;
        else if (digitalRead(Rbut) == LOW) {
          Wrong();
          switch1 == 0;
          continue;
        }
        else if (digitalRead(Bbut) == LOW) {
          Wrong();
          switch1 == 0;
          continue;
        }
        else if (digitalRead(Ybut) == LOW) {
          Wrong();
          switch1 == 0;
          continue;
        }
      } else if (digitalRead(Gbut) == LOW) Wrong();
      else if (digitalRead(Rbut) == LOW) Wrong();
      else if (digitalRead(Ybut) == LOW) Wrong();
    }
    //2차 해제 완료!
    Off(Gled);
    Off(Yled);

    delay(1000);

    Flash(Yled);
    delay(500);
    Flash(Bled);
    delay(500);
    Flash(Rled);
//세개 빤짝빤짝
    while (true) //파랑, 빨강 초록 순 누르기
    {
      if (digitalRead(Bbut) == LOW) {
        switch1 = 1;
        continue;
      } //파랑
      if (switch1 == 1) {
        if (digitalRead(Rbut == LOW)) {
          switch2 = 1;
          continue;
        } //빨강
        else if (digitalRead(Gbut) == LOW) {
          Wrong();
          switch1 == 0;
          continue;
        }
        else if (digitalRead(Bbut) == LOW) {
          Wrong();
          switch1 == 0;
          continue;
        }
        else if (digitalRead(Ybut) == LOW) {
          Wrong();
          switch1 == 0;
          continue;
        }
      }
      if (switch1 == 1 && switch2 == 1) {
        if (digitalRead(Gbut == LOW)) break; //초록
        else if (digitalRead(Rbut) == LOW) {
          Wrong();
          switch1 == 0;
          switch2 == 0;
          continue;
        }
        else if (digitalRead(Bbut) == LOW) {
          Wrong();
          switch1 == 0;
          switch2 == 0;
          continue;
        }
        else if (digitalRead(Ybut) == LOW) {
          Wrong();
          switch1 == 0;
          switch2 == 0;
          continue;
        }
      } else if (digitalRead(Gbut) == LOW) Wrong();
      else if (digitalRead(Rbut) == LOW) Wrong();
      else if (digitalRead(Ybut) == LOW) Wrong();
    }
    Off(Rled);
    Off(Yled);
    Off(Bled);
    //Correct() 추가하기

  }
}

void loop() {
  Rbut_start();
}