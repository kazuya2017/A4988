#include <stdlib.h>
#include "A4988.h"
/*
#define EN        8       // stepper motor enable, low level effective
#define X_DIR     5       //X axis, stepper motor direction control 
#define Y_DIR     6       //y axis, stepper motor direction control
#define Z_DIR     7       //zaxis, stepper motor direction control
#define X_STP     2       //x axis, stepper motor control
#define Y_STP     3       //y axis, stepper motor control
#define Z_STP     4       //z axis, stepper motor control
*/
const uint8_t A4988_EN = 8;
const uint8_t A4988_X_DIR = 5;
const uint8_t A4988_X_STP = 2;

A4988 step_motor(A4988_X_DIR,A4988_X_STP,A4988_EN);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

uint8_t serialRead(uint8_t *buffer,uint8_t max){
  uint8_t i=0;
  while(1){
      buffer[i] = Serial.read();      
      if(buffer[i]=='\n'){
        buffer[i]= '\0';
        break;
        }
      ++i;
      if(i>max){break;}      
    }
  return 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t serialbuffer[30];
  uint8_t* endptr;
  uint8_t rcvflag = 0;

  if (Serial.available()) {
    serialRead(serialbuffer,30);
    rcvflag=1;
  }
  if(rcvflag==1){
    rcvflag=0;
 
    if(serialbuffer[0]=='f'){//frequency
      uint16_t fmotor = strtol(&serialbuffer[1], &endptr, 10);
      step_motor.SetPWM(fmotor);
    }
    else if(serialbuffer[0]=='p'){
      step_motor.SetDir(1);
    }
    else if(serialbuffer[0]=='m'){
      step_motor.SetDir(0);      
    }    
  }
  delay(10);
}
