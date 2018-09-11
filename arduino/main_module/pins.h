#pragma once
/* 하드웨어 연결 정보 */
/*for I2C*/
#define SCL_PIN A5
#define SDA_PIN A4
//#define SLAVE_MODULE1 0x04
/*for 4 digit 7 segment and timer*/
const int PIEZO_PIN = 10;
const int segment_pins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int digit_pins[]  = {A0, 13, 12, 11};
