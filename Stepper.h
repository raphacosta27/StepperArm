#include "asf.h"


extern volatile long g_utick;

typedef struct Stepper{
	int direction;
    unsigned long step_delay;
    int number_of_steps;
	int step_number;
    
    Pio *pio_pin1;
    uint32_t pio_pin1_mask;
    Pio *pio_pin2;
    uint32_t pio_pin2_mask;
    Pio *pio_pin3;
    uint32_t pio_pin3_mask;
    Pio *pio_pin4;
    uint32_t pio_pin4_mask;

    unsigned long last_step_time;
    
} Stepper;

void initStepper(Stepper *n, int number_of_steps, Pio *pio_pin1, const uint32_t pio_mask_pin1,
                                                  Pio *pio_pin2, const uint32_t pio_mask_pin2,
                                                  Pio *pio_pin3, const uint32_t pio_mask_pin3,
                                                  Pio *pio_pin4, const uint32_t pio_mask_pin4);
// Speed setter method
void setSpeed(Stepper *n, long whatSpeed);

// mover method:
void step(Stepper *n, int steps_to_move);

void stepMotor(Stepper *n, int this_step);