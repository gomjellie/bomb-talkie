#include "Wire.h"

#define Rled 10
#define Bled 11
#define Gled 12 // todo : 12 번 납땜 접촉불량 해결
#define Yled 9

#define Rbut 7
#define Bbut 6 // blue button 연결된 초록색선 선문제인지 버튼 문제인지 모르겠음 일단 파란 버튼 제외하고 만듬
#define Gbut 4
#define Ybut 3

#define PBuzzer 2

int button_stat[8] = {0, };

void setup(){
  pinMode(Rled, OUTPUT);
  pinMode(Gled, OUTPUT);
  pinMode(Bled, OUTPUT);
  pinMode(Yled, OUTPUT);

  pinMode(Rbut, INPUT_PULLUP);
  pinMode(Gbut, INPUT_PULLUP);
  pinMode(Gbut, INPUT_PULLUP);
  pinMode(Ybut, INPUT_PULLUP);

//  randNumber = random(3);
  Serial.begin(9600);
  // Wire.begin(77);
}

void on_start() {
  digitalWrite(Rled, HIGH);
  digitalWrite(Gled, HIGH);
  digitalWrite(Bled, HIGH);
  digitalWrite(Yled, HIGH);
}

void on_button_button_clicked() {
//  digitalWrite();
}

void get_clicked_btn() {
  if (button_stat[Rbut] == 0 | button_stat[Gbut] == 0 | button_stat[Ybut] == 0 | button_stat[Bbut] == 0) {
    button_stat[Bbut] = 1;
  } else {
    button_stat[Bbut] = digitalRead(Bbut);
  }
  button_stat[Rbut] = digitalRead(Rbut);
  button_stat[Gbut] = digitalRead(Gbut);
  button_stat[Ybut] = digitalRead(Ybut);
  Serial.println(digitalRead(Bbut));

  if (button_stat[Rbut] == 0 | button_stat[Gbut] == 0 | button_stat[Ybut] == 0) {
    button_stat[Bbut] = 1;
  }

  if (!button_stat[Rbut]) {
    Serial.println("Rbut pressed");
  }

//  if (button_stat[Bbut]) {
//    Serial.println("Bbut pressed");
//  }
  if (!button_stat[Gbut]) {
    Serial.println("Gbut pressed");
  }
  if (!button_stat[Ybut]) {
    Serial.println("Ybut pressed");
  }
}

void loop(){
  on_start();
  get_clicked_btn();

  on_button_button_clicked();

  delay(100);
}