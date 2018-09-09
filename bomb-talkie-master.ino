/* bom-talkie-master.ino for Bomb-Talkie a.k.a. 빵터지는 대화
 * 
 * author: fetiu, gomjellie
 * last change: 2018.9.9
 * 메시지 포맷팅은 sprintf로 하는 것을 권장.
 */

#include<Wire.h>
#include"sheets.h"

#define PIEZO_PIN 10
#define SCL_PIN A5
#define SDA_PIN A4
/*for I2C*/
//#define SLAVE_MODULE1 0x04

/*----사용할 모드만 남기고 주석처리 해주세요.----*/
#define TIMER_MODE //0 이면 일반 delay
//#define THREAD_MODE
//#define MUSIC_MODE
/*--------*/

#ifdef TIMER_MODE
#include"timer.h"
extern float time_count;
extern float sound_speed;
#endif

/* 악보배열 호출 */
extern const struct note airplane[];
extern const struct note underworld[];
extern const struct note final_fantasy[];
extern const struct note sweep[];
extern const struct note tiktok[];

void setup() {
  for(int i = 0; i < 4; i++)
    pinMode(digit_select_pin[i], OUTPUT);
  for(int i = 0; i < 8; i++)
    pinMode(segment_pin[i], OUTPUT);
  pinMode(PIEZO_PIN,OUTPUT);
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
void playMusic(note music[], int music_length){
  for(int i =0; i < music_length ; i++){ 
    int dur = 1000 / music[i].tempo;        //한 박자를 tempo만큼 분할.
    tone(PIEZO_PIN, music[i].pitch, dur); //i번째 note의 음 높이로 재생
#ifdef TIMER_MODE
    float _dur = (dur * sound_speed)/MINUTE ; //딜레이를 줄여서 재생. 재생속도 빨라짐
    delay_countdown(_dur);
#elif THREAD_MODE
    sleep(dur);
#else
    delay(dur);
#endif
  }
  sound_speed = analogRead(A1);
  Serial.println(sound_speed);
}

void loop() {
  for (int i = 0; i < MAX_TIME; i++) {
    playMusic(tiktok, sizeof(tiktok) / sizeof(note));
  }
  detach_sound();
  playMusic(final_fantasy, sizeof(final_fantasy) / sizeof(note));
}



