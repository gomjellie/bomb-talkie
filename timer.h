/* timer.h for countdown timer via sevensegment
 * 카운트다운 타이머를 위한 라이브러리
 * author: fetiu
 * last change: 2018.9.9
 */ 
#define str String
#define append concat //**주의**
#define BUFF_SIZE 80 //for sprintf message
#define MINUTE 1000 // 1 minute for countdown 
#define MAX_TIME 300 // 5 minute

//#define DEBUG //디버그 모드로 전환하여 세그먼트 출력 값을 보려면 주석 해제.
/*정상적으로 세그먼트를 보려면 반드시 주석처리해야함.*/

float time_count = MAX_TIME;
float sound_speed= 800; //이걸 줄이면 카운트 속도가 빨라짐. 최대 1000
//BGM을 재생할때는 원래 속도로 돌려놓는것 잊지말기.

//전선 잘 짜르면 1000으로 올라가서 느리게 만드는것도 해보자.

const int digit_select_pin[] = {A0, 13, 12, 11};
const int segment_pin[] = {2, 3, 4, 5, 6, 7, 8, 9};
/* segment표시 위한 배열 정의 */
bool number_data[10][8]={
  {1, 1, 1, 1, 1, 1, 0, 0}, //0
  {0, 1, 1, 0, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1, 0}, //2
  {1, 1, 1, 1, 0, 0, 1, 0}, //3
  {0, 1, 1, 0, 0, 1, 1, 0}, //4
  {1, 0, 1, 1, 0, 1, 1, 0}, //5
  {1, 0, 1, 1, 1, 1, 1, 0}, //6
  {1, 1, 1, 0, 0, 1, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 1, 0}, //8
  {1, 1, 1, 0, 0, 1, 1, 0}  //9
};// anode일 경우 원소 호출시 앞에 !붙이기


void show_digit(int pos, int number){
  bool value, segment_value;
#ifdef DEBUG
  String msg= "digit " + str(pos) + ": "; //세그먼트 작동 테스트용 메시지.
  int = sleeptime;
  Serial.print("sleep할 시간을 지정하세요");
  sleeptime = Serial.parseInt()
#endif
  /*select a digit.*/
  for(int i = 0; i < 4; i++){
    value = (i == pos-1)? LOW : HIGH;
    digitalWrite(digit_select_pin[i], value);
  }
  /*show a number on the segment*/
  for(int i = 0; i < 8; i++){
    segment_value = number_data[number][i];
    digitalWrite(segment_pin[i], segment_value); //anode의 경우 켜질때 1, 끌때 0
#ifndef DEBUG //Debug모드가 아니라면
  }
  delay(5);
  return;
#else
    msg.append(segment_value);
  }
  Serial.println(msg);
  delay(500);
#endif
}

/* 함수 선언부 */
void delay_countdown(int duration){
  static char message[BUFF_SIZE];
  int minute = time_count/60;
  int second = (int)time_count%60;
  
  sprintf(message,"(%d:%d)", minute, second);
  Serial.println(message);
  
  if (time_count >= 0){
    for(int cycle=0; cycle < duration/20 ; cycle++){
      show_digit(1, 0);
      show_digit(2, minute); // minute
      show_digit(3, second/10); // second 1st digit
      show_digit(4, (int)second%10); // second 2nd digit
    }// 5ms * 4 routines = 20ms for one cycle. duration should be devides by that.
    
    time_count -= duration/sound_speed;  // 재생한 노트 길이 만큼이 전체 시간에서 빼줌.
  }
}


