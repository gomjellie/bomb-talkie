#include "Wire.h"

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
int buttonpushed = 0;


class Flash //지속적인 깜빡임
{
  private:
    int ledPin;
    int Buzzer;
    unsigned long targetMillis;
    int ledState;
    long OnTime;
    long OffTime;
    unsigned long previousMillis;    
    int State;
    int shift;

  public:
  Flash(int led_pin, int buzzerTone);
  void update(int time_delay, long on, long off);
  void Off();
};


Flash::Flash(int led_pin, int buzzerTone){
  ledPin = led_pin;
  pinMode(ledPin, OUTPUT);
  targetMillis =0;
  State = LOW;
  Buzzer = buzzerTone;
}

void Flash::update(int time_delay, long on, long off) {
  OnTime = on;
  OffTime = off;
  shift = time_delay;
long currentMillis = millis();
currentMillis = currentMillis - shift;
if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;
      previousMillis = currentMillis; 
      digitalWrite(ledPin, ledState);
      noTone(PBuzzer);
    }
else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;
      previousMillis = currentMillis; 
      digitalWrite(ledPin, ledState); 
      tone(PBuzzer, Buzzer);
    }
  }

void Flash::Off() {
  digitalWrite(ledPin, LOW);
  noTone(PBuzzer);
}

Flash R_led(Rled, 131); //빨강, C3
Flash B_led(Bled, 165); //파랑, E3
Flash Y_led(Yled, 196); //노랑. G3
Flash G_led(Gled, 262); //초록, C4

void setup() {
 /* for (int i = 9; i < 13; i++){
    pinMode(i, OUTPUT);
  }*/
  for (int i = 3; i < 7; i++){
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(PBuzzer, OUTPUT);
  noTone(PBuzzer);
  Wire.begin(7);
  Serial.begin(9600);
}

void Wrong() {
  //신호 보낼 것@!@!@!@
  Wire.write('F');
  tone(PBuzzer, 500);
  delay(200);
  noTone(PBuzzer);
  delay(200);
  tone(PBuzzer, 500);
  delay(200);
  noTone(PBuzzer);
  delay(200);
  tone(PBuzzer, 500);
  delay(200);
  noTone(PBuzzer);
}

void Rled_1() { //빨강 하나 반짝반짝 =>> 파란버튼 클릭
  while(buttonpushed == 0){
    updateSBut();
    R_led.update(0, 500, 2500); //shift 0 millis
    if(SBbut == 0){R_led.Off(); delay(10); buttonpushed = 1;}
    if(SRbut == 0 || SGbut ==0 || SYbut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
    Wire.write(4);
    //else if(Gbut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
    //else if(Ybut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
  }
  buttonpushed = 0;
}
void YGled_2() { //노랑, 초록 반짝반짝 =>> 빨강 초록 클릭
  while(buttonpushed == 0){
     int stack = 0;
    updateSBut();
    Y_led.update(0, 500, 2500);
    G_led.update(500, 500, 2500);
     if (stack == 0){
       Serial.println(stack);
       if(SRbut == 0){stack = 1; delay(10);}
       else if (SBbut == 0 || SGbut ==0 || SYbut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
       }
     else if (stack == 1){
       if (SGbut == 0) {
         Y_led.Off(); G_led.Off(); delay(10); buttonpushed = 1;
       }
       if (SBbut == 0 || SGbut ==0 || SYbut == 0){Wrong(); delay(10); buttonpushed = 0; continue;}
       if (SBbut == 0 || SRbut ==0 || SYbut == 0){Wrong(); delay(10); buttonpushed = 0; stack = 0; continue;}
     }
  }
}

void updateSBut(){
  SRbut = digitalRead(Rbut);
  SBbut = digitalRead(Bbut);
  SGbut = digitalRead(Gbut);
  SYbut = digitalRead(Ybut);
}
  
void loop() {
 Rled_1();
 delay(500);
 YGled_2();
}