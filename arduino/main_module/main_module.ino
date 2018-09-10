/* main_module.ino for Bomb-Talkie a.k.a. 빵터지는 대화
 * 
 * author: fetiu, gomjellie
 * last change: 2018.9.9
 * 
 * ps.메시지 포맷팅은 sprintf로 하는 것을 권장.
 */
#include<Wire.h>

/*----사용할 모드만 남기고 주석처리 해주세요.----*/
#define TIMER_MODE //일반 delay
//#define THREAD_MODE //to test multi-threaded function.
//#define MUSIC_MODE
//#define DEBUG_MODE //디버그 모드로 전환하여 세그먼트 출력 값을 보려면 주석 해제.
/*정상적으로 세그먼트를 보려면 DEBUG_MODE는 반드시 주석처리해야함.*/

#include"sound.h"
#ifdef TIMER_MODE
#include"timer.h"
extern float time_count; //5 * 60 s
extern float timer_speed;
extern bool success;
#endif
/* 하드웨어 연결 정보 */
/*for I2C*/
#define SCL_PIN A5
#define SDA_PIN A4
//#define SLAVE_MODULE1 0x04
/*for 4 digit 7 segment and timer*/
const int PIEZO_PIN = 10;
const int segment_pins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int digit_pins[]  = {A0, 13, 12, 11};

void setup() {
  pinMode(PIEZO_PIN,OUTPUT);
  for(int i = 0; i < 4; i++)
    pinMode(digit_pins[i], OUTPUT);
  for(int i = 0; i < 8; i++)
    pinMode(segment_pins[i], OUTPUT);
  Serial.begin(9600);
  Wire.begin(); //MASTER. 
  sound_play(ATTACH);
}

void play_notes(const note *music, int music_length){
 /**
  * param: music: array of notes
  * param: music_length: how long it sustain
  */
  for(int i =0; i < music_length ; i++){
    int dur = 1000 / music[i].tempo;        //한 박자를 tempo만큼 분할.
    tone(PIEZO_PIN, music[i].pitch, dur); //i번째 note의 음 높이로 재생
#ifdef TIMER_MODE
    float _dur = (dur * timer_speed)/MINUTE ; //딜레이를 줄여서 재생. 재생속도 빨라짐
    delay_countdown(_dur);
#elif THREAD_MODE
    sleep(dur);
#else
    delay(dur);
#endif
  }
}

void loop() {
  while(time_count > 0) {
    timer_speed = analogRead(A1);
    Serial.println(timer_speed);
    sound_play(TIK_TOK);
    if(timer_speed == 1023){
        success = true;
        sound_play(FINAL_FANTASY);
        sound_play(DETACH);
        exit(0);
    }
  }
  timer_speed = 50;
  for(int i=0; i<5; i++) sound_play(EXPLODE); //it sounds like boom.
  exit(0);
}

