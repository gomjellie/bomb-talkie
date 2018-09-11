/* sheets.h for music player via arduino tone 
 * author: fetiu, gomjellie, ez2max, geonmo...
 * last change: 2018.9.9
 */
#include"pitches.h"
#include"pins.h"

//"underworld", "final_fantasy", "sweep", "explode", "tiktok", "airplane", "attach", "detach"
enum SongLists
{
    FINAL_FANTASY,
    SWEEP,
    EXPLODE,
    TIK_TOK,
    ATTACH,
    DETACH,
};

/*음표 구조체 선언*/
struct note {
  uint16_t pitch; //음높이
  uint16_t tempo; //박자
};

extern void play_notes(const note *music, int music_length);
const void sound_play(int sheet_name);
void _attach_sound();
void _detach_sound();
void _explode();
void _final_fantasy();
void _sweep();
void _tik_tok();

/*효과음*/
void _attach_sound(){
  tone(PIEZO_PIN, D_4, 180);
  delay(200); // should be sleep
  tone(PIEZO_PIN, A_4, 150);
  delay(2000);
}//playmusic없이 가는게 시간을 안까먹음.

void _detach_sound(){
  tone(PIEZO_PIN, A_4, 150);
  delay(200); // should be sleep
  tone(PIEZO_PIN, D_4, 180);
  delay(2000);
}

/*************************************************
 * 악보 배열 선언부
 *************************************************/
//// tempo의 숫자는 몇분음표인지를 나타냄. pitch 0은 쉼표. 
//// 배열 원소 선언시, 한 마디씩 끊어서 작성하기.


void _explode() {
//// it sounds like bomb explodes
//// notes written by fetiu
  const struct note explode[] = {

          {C_4,12},{FS4,12},{F_4,12},{E_4,12},{AS4,12},{A_4,12},
          {GS4,6},{DS4,6},{B_3,6},
          {AS3, 6},{A_3, 6},{GS3,6},
          {C_4,12},{FS4,12},{F_4,12},{E_4,12},{AS4,12},{A_4,12},
          {GS4,6},{DS4,6},{B_3,6},
          {AS3, 6},{A_3, 6},{GS3,6},
          {C_4,12},{FS4,12},{F_4,12},{E_4,12},{AS4,12},{A_4,12},
          {GS4,6},{DS4,6},{B_3,6},
          {AS3, 6},{A_3, 6},{GS3,6},
          {C_4,12},{FS4,12},{F_4,12},{E_4,12},{AS4,12},{A_4,12},
          {GS4,6},{DS4,6},{B_3,6},
          {AS3, 6},{A_3, 6},{GS3,6},
          {C_4,12},{FS4,12},{F_4,12},{E_4,12},{AS4,12},{A_4,12},
          {C_4,12},{FS4,12},{F_4,12},{E_4,12},{AS4,12},{A_4,12},

  };
  int music_length = sizeof(explode) / sizeof(note);
  play_notes(explode, music_length);
}

void _tik_tok() {
//// tik tok
//// notes written by gomjellie & fetiu @fetiu's home
  const struct note tiktok[] = {
          {0,   8},
          {E_6, 16},
          {0,   32},
          {C_4, 32},
          {CS5, 8},
          {0,   8},
          {0,   2},
  };
  int music_length = sizeof(tiktok) / sizeof(note);
  play_notes(tiktok, music_length);
}

void _sweep() {
  //// arpeggio sweeping
  //// note written by gomjellie
  const struct note sweep[] = {
          // when mission successed!
          {D_4, 4},{F_4, 4},{A_4, 4},{C_5, 4},
          {D_5, 4},{F_5, 4},{A_5, 4},{C_6, 4},
          {D_6, 4},{C_6, 4},{A_5, 4},{F_5, 4},
          {D_5, 4},{C_5, 4},{A_4, 4},{F_4, 4},
          /////
          {CS4, 4},{F_4, 4},{GS4, 4},{C_5, 4},
          {CS5, 4},{F_5, 4},{GS5, 4},{C_6, 4},
          {CS6, 4},{C_6, 4},{GS5, 4},{F_5, 4},
          {CS5, 4},{C_5, 4},{GS4, 4},{F_4, 4},
  };
  play_notes(sweep, sizeof(sweep) / sizeof(note));
}


void _final_fantasy() {
  //// final_fantasy arpeggio song
//// notes written by gomjellie
  const struct note final_fantasy[] = {
          //// Code(c, d, e, g)
          /// arpeggio goes up
          {C_3, 8}, {D_3, 8}, {E_3, 8}, {G_3, 8},
          {C_4, 8}, {D_4, 8}, {E_4, 8}, {G_4, 8},
          {C_5, 8}, {D_5, 8}, {E_5, 8}, {G_5, 8},
          {C_6, 8}, {D_6, 8}, {E_6, 8}, {G_6, 8},
          //// arpeggio goes down
          {E_6, 8}, {D_6, 8}, {C_6, 8}, {G_5, 8},
          {E_5, 8}, {D_5, 8}, {C_5, 8}, {G_4, 8},
          {E_4, 8}, {D_4, 8}, {C_4, 8}, {G_3, 8},
          {E_3, 8}, {D_3, 8}, {C_3, 8}, {E_3, 8},

          //// Code(a, b, c, e)
          /// arpeggio goes up
          {A_2, 8}, {B_2, 8}, {C_3, 8}, {E_3, 8},
          {A_3, 8}, {B_3, 8}, {C_4, 8}, {E_4, 8},
          {A_4, 8}, {B_4, 8}, {C_5, 8}, {E_5, 8},
          {A_5, 8}, {B_5, 8}, {C_6, 8}, {E_6, 8},
          //// arpeggio goes down
          {C_6, 8}, {B_5, 8}, {A_5, 8}, {E_5, 8},
          {C_5, 8}, {B_4, 8}, {A_4, 8}, {E_4, 8},
          {C_4, 8}, {B_3, 8}, {A_3, 8}, {E_3, 8},
          {C_3, 8}, {B_2, 8}, {A_2, 8}, {C_3, 8},

          //// Code(F, G, A, C) arpeggio goes up
          {F_2, 8}, {G_2, 8}, {A_2, 8}, {C_3, 8},
          {F_3, 8}, {G_3, 8}, {A_3, 8}, {C_4, 8},
          {F_4, 8}, {G_4, 8}, {A_4, 8}, {C_5, 8},
          {F_5, 8}, {G_5, 8}, {A_5, 8}, {C_6, 8},

          //// Code(G, A, B, D) arpeggio goes up
          {G_2, 8}, {A_2, 8}, {B_2, 8}, {D_3, 8},
          {G_3, 8}, {A_3, 8}, {B_3, 8}, {D_4, 8},
          {G_4, 8}, {A_4, 8}, {B_4, 8}, {D_5, 8},
          {G_5, 8}, {A_5, 8}, {B_5, 8}, {D_6, 8},

          //// Code(C, D, E, G) arpeggio goes up
          {C_3, 8}, {D_3, 8}, {E_3, 8}, {G_3, 8},
          {C_4, 8}, {D_4, 8}, {E_4, 8}, {G_4, 8},
          {C_5, 8}, {D_5, 8}, {E_5, 8}, {G_5, 8},
          {C_6, 8}, {D_6, 8}, {E_6, 8}, {G_6, 8},

          //// Ending note
          {C_7, 2}
  };
  play_notes(final_fantasy, sizeof(final_fantasy) / sizeof(note));
}


/* 음악재생 함수 선언*/
const void sound_play(int sheet_name) {
  /**
   * param: sheet_name :
   *      e.g.) FINAL_FANTASY = 0,
                SWEEP = 1,
                EXPLODE = 2,
                TIK_TOK = 3,
                ATTACH = 4,
                DETACH = 5,
   * **/
  int music_length;
  switch (sheet_name) {
    case FINAL_FANTASY:
      _final_fantasy();
      break;
    case SWEEP:
      _sweep();
      break;
    case EXPLODE:
      _explode();
      break;
    case TIK_TOK:
      _tik_tok();
      break;
    case ATTACH:
      _attach_sound();
      break;
    case DETACH:
      _detach_sound();
      break;
  }
}
