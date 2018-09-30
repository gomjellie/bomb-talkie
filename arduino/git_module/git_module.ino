#include "Wire.h"
#include "math.h"

#define RED_LED_PORT    10
#define BLUE_LED_PORT   11
#define GREEN_LED_PORT  12 // todo : 12 번 납땜 접촉불량 해결
#define YELLOW_LED_PORT  9

#define RED_BUTTON_PORT    7
#define BLUE_BUTTON_PORT   6
#define GREEN_BUTTON_PORT  4
#define YELLOW_BUTTON_PORT 3

#define PBuzzer 2

#define STAT_LED_BLUE_PORT  15 // A1
#define STAT_LED_GREEN_PORT 16 // A2
#define STAT_LED_RED_PORT  17 // A3

#define FAIL -1
#define NORMAL 0
#define SUCCESS 1

int bombState = NORMAL; //해당 모듈의 해제 성공 여부.
//loop 구간에서 이 변수값을 성공 여부에 따라 0, 1, -1 등의 값으로 설정해주는것을 권장

int button_stat[8] = {0, };
int stacks = 1; // 왠진 모르겠는데 1을 더해야 맞는다...... 0 + 7000 이 처음에 6999로 저장되서 그냥 시작을 1로 함
int idx = 0;
int stage = 0;
int ans[4] = { // 정답 answer
        7000,
        7400,
        7430,
        7436,
};
int ans_helper[8][4] = {
        // [input_button][wrong_count]
        {0, },
        {0, },
        {0, },
        {RED_BUTTON_PORT, YELLOW_BUTTON_PORT, YELLOW_BUTTON_PORT, RED_BUTTON_PORT}, // YELLOW BUTTON CLICK
        {YELLOW_BUTTON_PORT, RED_BUTTON_PORT, GREEN_BUTTON_PORT, YELLOW_BUTTON_PORT}, // GREEN BUTTON CLICK
        {0, },
        {BLUE_BUTTON_PORT, BLUE_BUTTON_PORT, BLUE_BUTTON_PORT, BLUE_BUTTON_PORT}, // BLUE BUTTON CLICK
        {GREEN_BUTTON_PORT, GREEN_BUTTON_PORT, RED_BUTTON_PORT, GREEN_BUTTON_PORT}, //RED BUTTON
};
int wrong_count = 0;
const int final_stage = 3;

void on_start();
void on_button_clicked();
void on_red_clicked();
void on_green_clicked();
void on_yellow_clicked();
void on_blue_clicked();
void update_button_stat();
int check_ans();
void loop();
void blink_led(int led_pin, int milliseconds);
void show_hint();
void bombState_send();

void setup(){
  pinMode(RED_LED_PORT, OUTPUT);
  pinMode(GREEN_LED_PORT, OUTPUT);
  pinMode(BLUE_LED_PORT, OUTPUT);
  pinMode(YELLOW_LED_PORT, OUTPUT);

  pinMode(RED_BUTTON_PORT, INPUT_PULLUP);
  pinMode(GREEN_BUTTON_PORT, INPUT_PULLUP);
  pinMode(BLUE_BUTTON_PORT, INPUT_PULLUP);
  pinMode(YELLOW_BUTTON_PORT, INPUT_PULLUP);

  pinMode(STAT_LED_BLUE_PORT, OUTPUT);
  pinMode(STAT_LED_GREEN_PORT, OUTPUT);
  pinMode(STAT_LED_RED_PORT, OUTPUT);

  Serial.begin(9600);
  Wire.begin(7);
  Wire.onRequest(bombState_send);
}


void bombState_send() {
  if(bombState == SUCCESS){ //해제에 성공 했을 때
    Wire.write('S');
  }
  else if(bombState == NORMAL){
    Wire.write('N'); //아직 해제하지 못했을 때. 대기상태
  }
  else if(bombState == FAIL){ //해제 도중 실수를 했을때(실패했을 때)
    Wire.write('F');
    bombState = NORMAL; //실패 정보가 한번 전송된 이후엔 다시 IDLE로 전환
  }
}


void on_start() {
  digitalWrite(RED_LED_PORT, HIGH);
  digitalWrite(GREEN_LED_PORT, HIGH);
  digitalWrite(BLUE_LED_PORT, HIGH);
  digitalWrite(YELLOW_LED_PORT, HIGH);

  switch (wrong_count) {
    case 0:
      digitalWrite(STAT_LED_RED_PORT, LOW);
      digitalWrite(STAT_LED_GREEN_PORT, LOW);
      digitalWrite(STAT_LED_BLUE_PORT, LOW);
      break;
    case 1:
      digitalWrite(STAT_LED_RED_PORT, LOW);
      digitalWrite(STAT_LED_GREEN_PORT, HIGH);
      digitalWrite(STAT_LED_BLUE_PORT, HIGH);
      break;
    case 2:
      digitalWrite(STAT_LED_RED_PORT, LOW);
      digitalWrite(STAT_LED_GREEN_PORT, LOW);
      digitalWrite(STAT_LED_BLUE_PORT, HIGH);
      break;
    case 3:
      digitalWrite(STAT_LED_RED_PORT, HIGH);
      digitalWrite(STAT_LED_GREEN_PORT, LOW);
      digitalWrite(STAT_LED_BLUE_PORT, LOW);
      break;
  }
}

void on_button_clicked() {
  if (!button_stat[RED_BUTTON_PORT]) {
    while (!button_stat[RED_BUTTON_PORT]) {
      digitalWrite(RED_LED_PORT, HIGH);
      update_button_stat();
    }
    digitalWrite(RED_LED_PORT, LOW);
    on_red_clicked();
  }
  if (!button_stat[BLUE_BUTTON_PORT]) {
    // blue button doesn't work
    while (!button_stat[BLUE_BUTTON_PORT]) {
      digitalWrite(BLUE_LED_PORT, HIGH);
      update_button_stat();
    }
    digitalWrite(BLUE_LED_PORT, LOW);
    on_blue_clicked();
  }
  if (!button_stat[GREEN_BUTTON_PORT]) {
    while (!button_stat[GREEN_BUTTON_PORT]) {
      digitalWrite(GREEN_LED_PORT, HIGH);
      update_button_stat();
    }
    digitalWrite(GREEN_LED_PORT, LOW);
    on_green_clicked();
  }
  if (!button_stat[YELLOW_BUTTON_PORT]) {
    while (!button_stat[YELLOW_BUTTON_PORT]) {
      digitalWrite(YELLOW_LED_PORT, HIGH);
      update_button_stat();
    }
    digitalWrite(YELLOW_LED_PORT, LOW);
    on_yellow_clicked();
  }
}

void on_blue_clicked() {
  Serial.println("blue pressed");
  stacks += ans_helper[BLUE_BUTTON_PORT][wrong_count] * pow(10, final_stage-idx);
  Serial.print(BLUE_BUTTON_PORT * pow(10, final_stage-idx)); Serial.println("added");
  Serial.print("stack :"); Serial.println(stacks);
  idx++;
}

void on_red_clicked() {
  Serial.println("Red pressed");
  stacks += ans_helper[RED_BUTTON_PORT][wrong_count] * pow(10, final_stage-idx);
  Serial.print(RED_BUTTON_PORT * pow(10, final_stage-idx)); Serial.println("added");
  Serial.print("stack :"); Serial.println(stacks);
  idx++;
}

void on_green_clicked() {
  Serial.println("Green pressed");
  stacks += ans_helper[GREEN_BUTTON_PORT][wrong_count] * pow(10, final_stage-idx);
  Serial.print(GREEN_BUTTON_PORT * pow(10, final_stage-idx)); Serial.println("added");
  Serial.print("stack :"); Serial.println(stacks);
  idx++;
}

void on_yellow_clicked() {
  Serial.println("Yellow pressed");
  stacks += ans_helper[YELLOW_BUTTON_PORT][wrong_count] * pow(10, final_stage-idx);
  Serial.print(YELLOW_BUTTON_PORT * pow(10, final_stage-idx)); Serial.println("added");
  Serial.print("stack :"); Serial.println(stacks);
  idx++;
}

void update_button_stat() {
  button_stat[BLUE_BUTTON_PORT] = digitalRead(BLUE_BUTTON_PORT);
  button_stat[RED_BUTTON_PORT] = digitalRead(RED_BUTTON_PORT);
  button_stat[GREEN_BUTTON_PORT] = digitalRead(GREEN_BUTTON_PORT);
  button_stat[YELLOW_BUTTON_PORT] = digitalRead(YELLOW_BUTTON_PORT);
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
  digitalWrite(RED_LED_PORT, LOW);
  digitalWrite(YELLOW_LED_PORT, LOW);
  digitalWrite(GREEN_LED_PORT, LOW);
  digitalWrite(BLUE_LED_PORT, LOW);
  delay(200);
  int hint = ans[stage] / pow(10, final_stage - stage);
  Serial.print("hint :"); Serial.println(hint);
  int len = len_helper(hint);
  for (int i = len; i >= 0; i--) {
    int button_color = int(hint / pow(10, i)) % int(10);
    Serial.print("button_color :"); Serial.println(button_color);
    switch (button_color) {
      case RED_BUTTON_PORT:
        blink_led(RED_LED_PORT, 300);
        break;
      case BLUE_BUTTON_PORT:
        blink_led(BLUE_LED_PORT, 300);
        break;
      case GREEN_BUTTON_PORT:
        blink_led(GREEN_LED_PORT, 300);
        break;
      case YELLOW_BUTTON_PORT:
        blink_led(YELLOW_LED_PORT, 300);
        break;
      default:
        break;
    }
  }
}

void blink_led(int led_pin, int milliseconds) {
  digitalWrite(led_pin, HIGH);
  delay(milliseconds);
  digitalWrite(led_pin, LOW);
  delay(milliseconds);
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
        wrong_count++;
        stacks = 1;
        idx = 0;
        break;
      case 1:
        key_input_finished = true;
        Serial.print("right answer! stage: "); Serial.println(stage);
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

  if (stage == 4) {
    bombState = SUCCESS;
    for (int i = 20; i > 5; i--) {
      blink_led(BLUE_LED_PORT, i * 2);
      blink_led(RED_LED_PORT, i * 2);
      blink_led(GREEN_LED_PORT, i * 2);
      blink_led(YELLOW_LED_PORT, i * 2);
    }
    digitalWrite(BLUE_LED_PORT, HIGH);
    digitalWrite(RED_LED_PORT, HIGH);
    digitalWrite(YELLOW_LED_PORT, HIGH);
    digitalWrite(GREEN_LED_PORT, HIGH);

    digitalWrite(STAT_LED_GREEN_PORT, LOW);
    digitalWrite(STAT_LED_BLUE_PORT, LOW);
    digitalWrite(STAT_LED_RED_PORT, LOW);
    blink_led(STAT_LED_GREEN_PORT, 100);
    blink_led(STAT_LED_GREEN_PORT, 100);
    digitalWrite(STAT_LED_GREEN_PORT, HIGH);
    exit(0);
  } else {
    if (wrong_count > 3) {
      bombState = FAIL;
      digitalWrite(STAT_LED_GREEN_PORT, LOW);
      digitalWrite(STAT_LED_BLUE_PORT, LOW);
      digitalWrite(STAT_LED_RED_PORT, LOW);
      digitalWrite(STAT_LED_RED_PORT, HIGH);
      delay(100);
      digitalWrite(STAT_LED_RED_PORT, LOW);
      delay(100);
      digitalWrite(STAT_LED_RED_PORT, HIGH);
      delay(100);
    } else {
      bombState = NORMAL;
    }
  }
}
