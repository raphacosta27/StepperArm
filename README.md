# Stepper Motor for Atmel SAM E70
This library allows you to use the Stepper Motor model 28BYJ-48 with the constructor for 4-pin version. It was modeladed under an Atmel SAM E70 board and its commands, if your microcontroller uses any other commands that differs from SAME70, I do not guarantee that it will work. 

# Usage
Download Stepper.c and Stepper.h from this repository and include the files in yout Atmel Project. Do not forget to import Stepper.h in yout main file.


## Init 
Create a Stepper struct instance like:</br>
	Stepper n;

Then, use the initStepper function to make it usable:</br>
 initStepper(&n, int number_of_steps, Pio *pio_pin1, uint32_t pio_mask_pin1,</br>
                                              Pio *pio_pin2, uint32_t pio_mask_pin2,</br>
                                              Pio *pio_pin3, uint32_t pio_mask_pin3,</br>
                                              Pio *pio_pin4, uint32_t pio_mask_pin4);</br>

## Setting speed
Set the speed that your motor will work on:</br>
  void setSpeed(&n, long whatSpeed);

## Moving
Call the function step to make it move:</br>
  void step(&n, int steps_to_move);


## Observations:
For some reason that I did not find out yet, giving a steps_to_move in step method positive, it goes on a counter-clockwise direction, and a negative steps_to_move make it goes to a clockwise direction. This definition is the opposite of the one specified in the Arduino Stepper Library.</br>

All this library is based on the Stepper Library for Arduino, write in C++ language. Please consider some bugs. 
