/* main_module.ino for Bomb-Talkie a.k.a. 빵터지는 대화
 * 
 * author: fetiu, gomjellie
 * last change: 2018.9.9
 * 
 * ps.메시지 포맷팅은 sprintf로 하는 것을 권장.
 */
#include<Wire.h>
#include"sheets.h"

/* 악보 리스트 */
extern const struct note airplane[];
extern const struct note underworld[];
extern const struct note final_fantasy[];
extern const struct note sweep[];
extern const struct note tiktok[];

/*----사용할 모드만 남기고 주석처리 해주세요.----*/
#define TIMER_MODE //일반 delay
//#define DEBUG_MODE //to see Serial debug messages
//#define THREAD_MODE //to test multi-threaded function 
//#define MUSIC_MODE

#ifdef TIMER_MODE
#include"timer.h"
extern float time_count;
extern float timer_speed;
#endif
/* 하드웨어 연결 정보 */
/*for I2C*/
#define SCL_PIN A5
#define SDA_PIN A4
//#define SLAVE_MODULE1 0x04
/*for 4 digit 7 segment and timer*/
#define PIEZO_PIN 10
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
  attach_sound();
}

/*효과음*/
void attach_sound(){
  tone(PIEZO_PIN, D_4, 180);
  delay(200); // should be sleep
  tone(PIEZO_PIN, A_4, 150);
  delay(2000);
}//playmusic없이 가는게 시간을 안까먹음.

void detach_sound(){
  tone(PIEZO_PIN, A_4, 150);
  delay(200); // should be sleep
  tone(PIEZO_PIN, D_4, 180);
  delay(2000);
}

 /* 음악재생 함수 선언*/
void play_music(note music[], int music_length){
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
    play_music(tiktok, sizeof(tiktok) / sizeof(note));
    Serial.println(timer_speed);
  }
  detach_sound();
  play_music(final_fantasy, sizeof(final_fantasy) / sizeof(note));
}




