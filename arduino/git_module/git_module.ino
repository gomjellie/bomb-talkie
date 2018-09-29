#include "Wire.h"
#include "math.h"

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
int stacks = 1; // 왠진 모르겠는데 1을 더해야 맞는다...... 0 + 7000 이 처음에 6999로 저장되서 그냥 시작을 1로 함
int idx = 0;
int stage = 0;
int ans[4] = { // 정답 answer
        7000,
        7400,
        7430,
        7437,
};
const int final_stage = 3;

void on_start();
void on_button_clicked();
void on_red_clicked();
void on_green_clicked();
void on_yellow_clicked();
void update_button_stat();
int check_ans();
void loop();

void setup(){
  pinMode(Rled, OUTPUT);
  pinMode(Gled, OUTPUT);
  pinMode(Bled, OUTPUT);
  pinMode(Yled, OUTPUT);

  pinMode(Rbut, INPUT_PULLUP);
  pinMode(Gbut, INPUT_PULLUP);
  pinMode(Gbut, INPUT_PULLUP);
  pinMode(Ybut, INPUT_PULLUP);

  Serial.begin(9600);
  // Wire.begin(77);
}

void on_start() {
  digitalWrite(Rled, HIGH);
  digitalWrite(Gled, HIGH);
  digitalWrite(Bled, HIGH);
  digitalWrite(Yled, HIGH);
}

void on_button_clicked() {
  if (!button_stat[Rbut]) {
    while (!button_stat[Rbut]) {
      digitalWrite(Rled, LOW);
      update_button_stat();
    }
    digitalWrite(Rled, HIGH);
    on_red_clicked();
  }
  if (button_stat[Bbut]) {
    // blue button doesn't work
  }
  if (!button_stat[Gbut]) {
    while (!button_stat[Gbut]) {
      digitalWrite(Gled, LOW);
      update_button_stat();
    }
    digitalWrite(Gled, HIGH);
    on_green_clicked();
  }
  if (!button_stat[Ybut]) {
    while (!button_stat[Ybut]) {
      digitalWrite(Yled, LOW);
      update_button_stat();
    }
    digitalWrite(Yled, HIGH);
    on_yellow_clicked();
  }
}

void on_red_clicked() {
  Serial.println("Red pressed");
  stacks += Rbut * pow(10, final_stage-idx);
  Serial.println(Rbut * pow(10, final_stage-idx));
  Serial.println("added");
  Serial.print("stack :"); Serial.println(stacks);
  idx++;
}

void on_green_clicked() {
  Serial.println("Green pressed");
  stacks += Gbut * pow(10, final_stage-idx);
  Serial.println(Gbut * pow(10, final_stage-idx));
  Serial.println("added");
  Serial.print("stack :"); Serial.println(stacks);
  idx++;
}

void on_yellow_clicked() {
  Serial.println("Yellow pressed");
  stacks += Ybut * pow(10, final_stage-idx);
  Serial.println(Ybut * pow(10, final_stage-idx));
  Serial.println("added");
  Serial.print("stack :"); Serial.println(stacks);
  idx++;
}

void update_button_stat() {
  button_stat[Rbut] = digitalRead(Rbut);
  button_stat[Gbut] = digitalRead(Gbut);
  button_stat[Ybut] = digitalRead(Ybut);
}

int check_ans() {
  /**
   * 정답 체크
   * 아직 idx가 다 안찼으면 :   -1 리턴
   * idx가 다 찼는데 틀렸으면 :  0 리턴
   * idx가 다 찼고 맞았으면 :   1 리턴
   */
  if (idx-1 != stage) {
    if (idx-1 > stage) {
      Serial.print("WTF!!!!!!!!!!! idx :");Serial.print(idx); Serial.print(" stage: "); Serial.println(stage);
      // 발생하면 안되는 상황이지만 혹시 모르니 처리해둠
      return 2;
    }
    return -1;
  }
  if (stacks == ans[stage]) {
    return 1;
  }
  return 0;
}

int len_helper(unsigned x) {
  if      (x >= 10000)  return 4;
  else if (x >= 1000)   return 3;
  else if (x >= 100)    return 2;
  else if (x >= 10)     return 1;
  return 0;
}

void show_hint() {
  int hint = ans[stage] / pow(10, final_stage - stage);
  Serial.print("hint :"); Serial.println(hint);
  int len = len_helper(hint);
  for (int i = len; i >= 0; i--) {
    int button_color = int(hint / pow(10, i)) % int(10);
    Serial.print("button_color :"); Serial.println(button_color);
    switch (button_color) {
      case Rbut:
        digitalWrite(Rled, LOW);
        delay(200);
        digitalWrite(Rled, HIGH);
        delay(200);
        break;
      case Bbut:
        digitalWrite(Bled, LOW);
        delay(200);
        digitalWrite(Bled, HIGH);
        delay(200);
        break;
      case Gbut:
        digitalWrite(Gled, LOW);
        delay(200);
        digitalWrite(Gled, HIGH);
        delay(200);
        break;
      case Ybut:
        digitalWrite(Yled, LOW);
        delay(200);
        digitalWrite(Yled, HIGH);
        delay(200);
        break;
      default:
        break;
    }
  }
}

bool key_input_finished = false;

void loop() {
  on_start();
  show_hint();

  key_input_finished = false;
  while (!key_input_finished) {
    update_button_stat();
    on_button_clicked();
    int progress_status = check_ans();

    switch (progress_status) {
      case -1:
        break;
      case 0:
        key_input_finished = true;
        Serial.println("idx is full but wrong..... setting idx = 0");
        stacks = 1;
        idx = 0;
        break;
      case 1:
        key_input_finished = true;
        Serial.print("right answer! stage: ");
        Serial.println(stage);
        stacks = 1;
        idx = 0;
        stage++;
        break;
      default:
        // on error
        stacks = 1;
        idx = 0;
        break;
    }
    delay(100);
  }

  if (stage == 3) {
    exit(0);
  }
}
