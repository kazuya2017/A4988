#include <stdlib.h>

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

void step(boolean dir, byte dirPin, byte stepperPin, int32_t steps)
{
  digitalWrite(dirPin, dir);
  delay(50);
  for (int32_t i = 0; i < steps; i++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(800);  
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(800);  
  }
}
void SetDir(uint8_t dir){
  if(dir){
    digitalWrite(A4988_X_DIR, HIGH);
    }
  else{
    digitalWrite(A4988_X_DIR, LOW);    
  }
}

void SetPWM(uint16_t frequency){
  if(frequency < 32){
    noTone(A4988_X_STP);
  }
  else{
    tone(A4988_X_STP,frequency);
  }    
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A4988_X_DIR, OUTPUT); pinMode(A4988_X_STP, OUTPUT);
  pinMode(A4988_EN, OUTPUT);
  digitalWrite(A4988_EN, LOW);
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
      SetPWM(fmotor);
    }
    else if(serialbuffer[0]=='p'){
      SetDir(1);
    }
    else if(serialbuffer[0]=='m'){
      SetDir(0);      
    }    
  }
  delay(10);

  
  
//  Serial.write((char *)serialbuffer);  
  if(serialbuffer[0]=='x'){
    int16_t motordig = strtol(&serialbuffer[1], &endptr, 10);
    Serial.println(motordig);
    int32_t mstep = (int32_t) motordig*100/35;
    if(motordig>0){
      step(true, A4988_X_DIR, A4988_X_STP, mstep); // X axis motor rotates CW for 1 circle, as in 200 steps
    }
    else{
      mstep *=-1;
      step(false, A4988_X_DIR, A4988_X_STP, mstep); // x axis motor rotates CCW for 1 circle, as in 200 steps      
    }
  delay(1000);
  }
   
/*  
  step(false, X_DIR, X_STP, 200); // x axis motor rotates CCW for 1 circle, as in 200 steps
  step(false, Y_DIR, Y_STP, 200); // y axis motor rotates CCW for 1 circle, as in 200 steps
  step(false, Z_DIR, Z_STP, 200); // z axis motor rotates CCW for 1 circle, as in 200 steps
  delay(1000);
  step(true, X_DIR, X_STP, 200); // X axis motor rotates CW for 1 circle, as in 200 steps
  step(true, Y_DIR, Y_STP, 200); // y axis motor rotates CW for 1 circle, as in 200 steps
  step(true, Z_DIR, Z_STP, 200); // z axis motor rotates CW for 1 circle, as in 200 steps
  delay(1000);
*/
}
