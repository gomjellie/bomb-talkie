#include "Wire.h"
#include <mthread.h>
#define Rled 12
#define Bled 11
#define Gled 10
#define Yled 9

#define Rbut 6
#define Bbut 5
#define Gbut 4
#define Ybut 3

#define PBuzzer 2

int SRbut;
int SBbut;
int SGbut;
int SYbut;
int global_button_status[10] = {0,};
int should_led_be_on[15] = {0,};

const long interval = 1000;
unsigned long previousMillis = 0;
int State = 0;
int buttonpushed = 0;

// Our custom Thread:
class LedThread : public Thread
{
public:
    LedThread(int led_pin);
protected:
    bool loop();
private:
    int led_pin;
};

LedThread::LedThread(int led_pin)
{
    pinMode(led_pin, OUTPUT);
    this->led_pin = led_pin;
}

bool LedThread::loop()
{

    // Die if requested:
    if(kill_flag)
        return false;

    if (should_led_be_on[this->led_pin] == 1) {
      digitalWrite(this->led_pin, HIGH);
    } else {
      digitalWrite(this->led_pin, LOW);
    }
    // Print the status message:

    // Sleep for one second:
    sleep_milli(100);
    return true;
}

//////

class ButtonThread : public Thread
{
public:
    ButtonThread(int led_pin);
protected:
    bool loop();
private:
    int button_pin;
};

ButtonThread::ButtonThread(int button_pin)
{
    pinMode(button_pin, INPUT);
    this->button_pin = button_pin;
}

bool ButtonThread::loop()
{
    // Die if requested:
    if(kill_flag)
        return false;
    bool button_status = digitalRead(this->button_pin);
    global_button_status[this->button_pin] = button_status;
    
    // Print the status message:
    

    // Sleep for one second:
    sleep_milli(100);
    return true;
}

///////


class ControllerThread : public Thread
{
public:
    ControllerThread();
protected:
    bool loop();
private:
    int button_pin;
};

ControllerThread::ControllerThread()
{
  //empty
}

bool ControllerThread::loop()
{
  unsigned long sleep_for_second = millis();
    // Die if requested:
    if(kill_flag)
        return false;
    
    // Print the status message:

    // logic HERE 
    //
    //
    Serial.println("hi");
  should_led_be_on[Rled] = 1;
    while(sleep_for_second < 1000){Serial.println(sleep_for_second);}
    should_led_be_on[Rled] = 0;
    while(sleep_for_second < 2000){}
    should_led_be_on[Rled] = 1;
    // Sleep for one second:
     sleep_milli(10000);
    return true;
}


void setup()
{
    
    // LedThread는 should_led_be_on 의 값을 읽어서 1이면 키고 0이면 끄는 역할만을 한다.
    main_thread_list->add_thread(new LedThread(Rled));
    main_thread_list->add_thread(new LedThread(Gled));
    main_thread_list->add_thread(new LedThread(Bled));
    main_thread_list->add_thread(new LedThread(Yled));

    // ButtonThread는 버튼이 눌렸는지 확인하고 global_button_status에 기록하는 작업만을 한다.
    main_thread_list->add_thread(new ButtonThread(Rbut));
    main_thread_list->add_thread(new ButtonThread(Gbut));
    main_thread_list->add_thread(new ButtonThread(Bbut));
    main_thread_list->add_thread(new ButtonThread(Ybut));

    // Controller는 프로그램의 프름을 관리한다. 
    // global_button_status의 값을 읽고
    // should_led_be_on 의 값을 쓸 수 있다.
    main_thread_list->add_thread(new ControllerThread());
    

    // Initialize the serial connection:
    Serial.begin(9600);
    delay(1000);

}
// void setup() {
//   for (int i = 9; i < 13; i++){
//     pinMode(i, OUTPUT);
//   }
//   for (int i = 3; i < 7; i++){
//     pinMode(i, INPUT_PULLUP);
//   }
//   pinMode(PBuzzer, OUTPUT);
//   noTone(PBuzzer);
//   Wire.begin(7);
//   Serial.begin(9600);
// }

// void Flash(int blinkLed) {
//   unsigned long currentMillis = millis();
//   if (currentMillis - previousMillis > interval) {
//     previousMillis = currentMillis;
//     if (State == LOW) {
//       State = HIGH;
//       tone(PBuzzer, 250);
//     } else {
//       State = LOW;
//       noTone(PBuzzer);
//     }
//     digitalWrite(blinkLed, State);
//     Serial.print(State);
//     Serial.println(": State");
//   }
// }

// void Off(int led) {
//   digitalWrite(led, LOW);
//   noTone(PBuzzer);
// }

// void Correct(){
//   Wire.write('S');
// }

// void Wrong() {
//   //신호 보낼 것@!@!@!@
//   Wire.write('F');
//   Serial.println('F');
//   tone(PBuzzer, 500);
//   delay(200);
//   noTone(PBuzzer);
//   delay(200);
//   tone(PBuzzer, 500);
//   delay(200);
//   noTone(PBuzzer);
//   delay(200);
//   tone(PBuzzer, 500);
//   delay(200);
//   noTone(PBuzzer);
// }

// void Rled_1() { //빨강 하나 반짝반짝 =>> 파란버튼 클릭
//   while(buttonpushed == 0){
//     updateSBut();
//     Flash(Rled);
//     if(SBbut == 0){Off(Rled); delay(10); Serial.println('Correct'); buttonpushed = 1;}
//     if(SRbut == 0 || SGbut ==0 || SYbut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
//     Wire.write(4);
//     //else if(Gbut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
//     //else if(Ybut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
//   }
//   buttonpushed = 0;
// }
// void YGled_2() { //노랑, 초록 반짝반짝 =>> 빨강 초록 클릭
//   int stack = 0;
//   while(buttonpushed == 0){
//     updateSBut()0.;
//     Flash(Yled);
//     Flash(Gled);
//      if (SRbut == 0){stack = 1;}
//      if (SBbut == 0 || SGbut ==0 || SYbut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
//      if (stack == 1){
//        if (SGbut == 0){Off(Yled); Off(Gled); delay(10); Correct(); buttonpushed = 1;}
//        if (SBbut == 0 || SRbut ==0 || SYbut == 0){Wrong(); delay(10); buttonpushed = 0; stack = 0; continue;}
//      }
//   }

// }
 
// void updateSBut(){
//   SRbut = digitalRead(Rbut);
//   SBbut = digitalRead(Bbut);
//   SGbut = digitalRead(Gbut);
//   SYbut = digitalRead(Ybut);
// }
  
// void loop() {
//  Rled_1();
//  delay(500);
//  YGled_2();
// }void Flash(int blinkLed) {
//   unsigned long currentMillis = millis();
//   if (currentMillis - previousMillis > interval) {
//     previousMillis = currentMillis;
//     if (State == LOW) {
//       State = HIGH;
//       tone(PBuzzer, 250);
//     } else {
//       State = LOW;
//       noTone(PBuzzer);
//     }
//     digitalWrite(blinkLed, State);
//     Serial.print(State);
//     Serial.println(": State");
//   }
// }

// void Off(int led) {
//   digitalWrite(led, LOW);
//   noTone(PBuzzer);
// }

// void Correct(){
//   Wire.write('S');
// }

// void Wrong() {
//   //신호 보낼 것@!@!@!@
//   Wire.write('F');
//   Serial.println('F');
//   tone(PBuzzer, 500);
//   delay(200);
//   noTone(PBuzzer);
//   delay(200);
//   tone(PBuzzer, 500);
//   delay(200);
//   noTone(PBuzzer);
//   delay(200);
//   tone(PBuzzer, 500);
//   delay(200);
//   noTone(PBuzzer);
// }

// void Rled_1() { //빨강 하나 반짝반짝 =>> 파란버튼 클릭
//   while(buttonpushed == 0){
//     updateSBut();
//     Flash(Rled);
//     if(SBbut == 0){Off(Rled); delay(10); Serial.println('Correct'); buttonpushed = 1;}
//     if(SRbut == 0 || SGbut ==0 || SYbut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
//     Wire.write(4);
//     //else if(Gbut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
//     //else if(Ybut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
//   }
//   buttonpushed = 0;
// }
// void YGled_2() { //노랑, 초록 반짝반짝 =>> 빨강 초록 클릭
//   int stack = 0;
//   while(buttonpushed == 0){
//     updateSBut()0.;
//     Flash(Yled);
//     Flash(Gled);
//      if (SRbut == 0){stack = 1;}
//      if (SBbut == 0 || SGbut ==0 || SYbut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
//      if (stack == 1){
//        if (SGbut == 0){Off(Yled); Off(Gled); delay(10); Correct(); buttonpushed = 1;}
//        if (SBbut == 0 || SRbut ==0 || SYbut == 0){Wrong(); delay(10); buttonpushed = 0; stack = 0; continue;}
//      }
//   }

// }
 
// void updateSBut(){
//   SRbut = digitalRead(Rbut);
//   SBbut = digitalRead(Bbut);
//   SGbut = digitalRead(Gbut);
//   SYbut = digitalRead(Ybut);
// }
  
// void loop() {
//  Rled_1();
//  delay(500);
//  YGled_2();
// }