

A4988 motor driver can be controlled by serial protocol (UART)

Three types of following commands are prepared.
1: frequency set 
2: direction set
3: step number set

Description of A4988 class
	Constructor : A4988(uint8_t dir_pin,uint8_t stp_pin, uint8_t enable_pin);
		dir_pin: set the direction pin (connecting the A4988 direction control pin)
		stp_pin: set the step out pin (connecting the A4988 step input pin)
		enabke_pin: set the enable pin (connecting the A4988 enable pin)

	enable(), disable() :
		control the enable pin.

	SetPWM(uint8_t frequency):
		Set the pulse frequency outputted by stp_pin.
		Note: use tone library

	SetPulseNum(uint8_t steps,uint8_t p_width)
		steps : number of steps
		p_width: number of pulse width 

In main program, 1 and 2 are used as samples.

	1: frequency set 
		Command format: fxxx (xxx = frequency)
		xxx is number of frequency in range of unsigned int16 (uint16_t)

	2: direction set 
		Command format: p or m (one character)


