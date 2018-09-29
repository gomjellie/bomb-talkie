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
  if (!button_stat[Rbut]) {
    while (!button_stat[Rbut]) {
      digitalWrite(Rled, LOW);
      get_clicked_btn();
    }
    Serial.println("Rbut pressed");
  }
  if (button_stat[Bbut]) {
    // blue button doesn't work
  }
  if (!button_stat[Gbut]) {
    while (!button_stat[Gbut]) {
      digitalWrite(Gled, LOW);
      get_clicked_btn();
    }
    Serial.println("Gbut pressed");
  }
  if (!button_stat[Ybut]) {
    while (!button_stat[Ybut]) {
      digitalWrite(Yled, LOW);
      get_clicked_btn();
    }
    Serial.println("Ybut pressed");
  }
}

void on_yellow_clicked() {

}

void on_green_clicked() {

}

void on_yellow_clicked() {

}

void get_clicked_btn() {
//  if (button_stat[Rbut] == 0 | button_stat[Gbut] == 0 | button_stat[Ybut] == 0 | button_stat[Bbut] == 0) {
//    button_stat[Bbut] = 1;
//  } else {
//    button_stat[Bbut] = digitalRead(Bbut);
//  }
  button_stat[Rbut] = digitalRead(Rbut);
  button_stat[Gbut] = digitalRead(Gbut);
  button_stat[Ybut] = digitalRead(Ybut);

//  if (button_stat[Rbut] == 0 | button_stat[Gbut] == 0 | button_stat[Ybut] == 0) {
//    button_stat[Bbut] = 1;
//  }


}

void loop(){
  on_start();
  get_clicked_btn();
  on_button_button_clicked();
  delay(100);
}
