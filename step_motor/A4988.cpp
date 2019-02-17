#include "A4988.h"

A4988::A4988(uint8_t dir_pin,uint8_t stp_pin,uint8_t enable_pin){
    this->dir_pin = dir_pin;
    this->stp_pin =stp_pin;
    this->enable_pin =enable_pin;
    pinMode(dir_pin, OUTPUT);
    pinMode(stp_pin, OUTPUT);
    pinMode(enable_pin, OUTPUT);
    enable();
}

void A4988::SetPWM(uint8_t frequency){
    if(dir_pin < 32){
        noTone(stp_pin);
    }
    else{
        tone(stp_pin,frequency);
    }
}
void A4988::SetAngle(uint8_t steps,uint8_t p_width){
  for (int32_t i = 0; i < steps; i++) {
    digitalWrite(stp_pin, HIGH);
    delayMicroseconds(p_width>>2);  
    digitalWrite(stp_pin, LOW);
    delayMicroseconds(p_width>>2);  
  }
}



