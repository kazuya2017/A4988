#ifndef __A4988_H__
#define __A4988_H__

#include <stdint.h>
#include <Arduino.h>

class A4988{
	private:
	uint8_t dir_pin, stp_pin, enable_pin;
	
	public:
	
	A4988(uint8_t dir_pin,uint8_t stp_pin, uint8_t enable_pin);

	void SetDir(uint8_t dir){
		digitalWrite(dir_pin, (dir & 0x01));
		delay(50);
	}
	void enable(){digitalWrite(enable_pin, LOW);}
	void disable(){digitalWrite(enable_pin, HIGH);}

	void SetPWM(uint8_t frequency);
	void SetPulseNum(uint8_t steps,uint8_t p_width);
};

#endif
