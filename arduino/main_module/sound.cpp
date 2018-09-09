/* sound.cpp for sound.h
 * 메모리 졸라 부족해요. 그래서 만들었어요.
 * > "아두이노는 적폐다....." - 아두이노로 임베디드 프로그래밍을 처음 접한 뒤 컬쳐쇼크를 받은 오인규씨의 단말마
 * _하지만 이제는 고생할 필요없어졌어요. 감사합니다 PROGEM HEROS!_
 */
#pragma once
#include"sound.h"

extern const int PIEZO_PIN;

void _play_notes(const note *music, int music_length){
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


const void sound_play(char *sheet_name){
    /**
     * param: sheet_name :
     *      e.g.) "underworld", "final_fantasy", "sweep", "explode", "tiktok", "airplane", "attach", "detach"
     * **/
    int len;
    if (strcmp(sheet_name, "underworld") == 0) {
        len = sizeof(underworld) / sizeof(note);
        _play_notes(underworld, len);
    }
    else if (strcmp(sheet_name, "final_fantasy") == 0) {
        len = sizeof(final_fantasy) / sizeof(note);
        _play_notes(final_fantasy, len);
    }
    else if (strcmp(sheet_name, "sweep") == 0) {
        len = sizeof(sweep) / sizeof(note);
        _play_notes(sweep, len);
    }
    else if (strcmp(sheet_name, "explode") == 0) {
        len = sizeof(explode) / sizeof(note);
        _play_notes(explode, len);
    }
    else if (strcmp(sheet_name, "tiktok") == 0) {
        len = sizeof(tiktok) / sizeof(note);
        _play_notes(tiktok, len);
    }
    else if (strcmp(sheet_name, "airplane") == 0) {
        len = sizeof(airplane) / sizeof(note);
        _play_notes(airplane, len);
    }
    else if (strcmp(sheet_name, "attach") == 0) {
        attach_sound();
    }
    else if (strcmp(sheet_name, "detach") == 0) {
        detach_sound();
    }
}



