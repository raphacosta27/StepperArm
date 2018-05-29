#include "Stepper.h"

void initStepper(Stepper *n, int number_of_steps, Pio *pio_pin1, uint32_t pio_mask_pin1, Pio *pio_pin2,  uint32_t pio_mask_pin2, Pio *pio_pin3,  uint32_t pio_mask_pin3, Pio *pio_pin4, uint32_t pio_mask_pin4){
    n->step_number = 0;
    n->direction = 0;
    n->last_step_time = 0;
    n->number_of_steps = number_of_steps;

    n->pio_pin1 = pio_pin1;
    n->pio_pin1_mask = pio_mask_pin1;

    n->pio_pin2 = pio_pin2;
    n->pio_pin2_mask = pio_mask_pin2;

    n->pio_pin3 = pio_pin3;
    n->pio_pin3_mask = pio_mask_pin3;

    n->pio_pin4 = pio_pin4;
    n->pio_pin4_mask = pio_mask_pin4;

    pmc_enable_periph_clk(pio_pin1);
	pmc_enable_periph_clk(pio_pin2);
	pmc_enable_periph_clk(pio_pin3);
	pmc_enable_periph_clk(pio_pin4);

	//Configuração dos pinos
	pio_configure(pio_pin1, PIO_OUTPUT_0, pio_mask_pin1, PIO_DEFAULT);
	pio_configure(pio_pin2, PIO_OUTPUT_0, pio_mask_pin2, PIO_DEFAULT);
	pio_configure(pio_pin3, PIO_OUTPUT_0, pio_mask_pin3, PIO_DEFAULT);
	pio_configure(pio_pin4, PIO_OUTPUT_0, pio_mask_pin4, PIO_DEFAULT);
	
	
}

void setSpeed(Stepper *n, long whatSpeed){
    n->step_delay = (60L * 1000L * 1000L) / n->number_of_steps / whatSpeed;
}

void step(Stepper *n, int steps_to_move){
	int steps_left = abs(steps_to_move);
	
	if(steps_to_move > 0){n->direction = 1;}
	if(steps_to_move < 0){n->direction = 0;}
	//printf("Direction = %d\n", n->direction);
	//delay_ms(4000);
	while(steps_left > 0){
		//printf("Steps_left: %d\n", steps_left);
		//unsigned long now = g_utick;
		if(g_utick - n->last_step_time >= n->step_delay){
			n->last_step_time = g_utick;
			if(n->direction == 1){
				n->step_number++;
				if(n->step_number == n->number_of_steps){
					n->step_number = 0;
				}
			}
			else{
				if(n->step_number == 0){
					n->step_number = n->number_of_steps;
				}
				n->step_number--;
			}
			steps_left--;
			
			stepMotor(n, n->step_number % 4);
		}
	}
}

void stepMotor(Stepper *n, int this_step){
	//printf("Which case: %d\n", this_step);
	switch(this_step){
		case 0:
			pio_set(n->pio_pin1, n->pio_pin1_mask);
			pio_clear(n->pio_pin2, n->pio_pin2_mask);
			pio_set(n->pio_pin3, n->pio_pin3_mask);
			pio_clear(n->pio_pin3, n->pio_pin4_mask);
		break;
		case 1:
			pio_clear(n->pio_pin1, n->pio_pin1_mask);
			pio_set(n->pio_pin2, n->pio_pin2_mask);
			pio_set(n->pio_pin3, n->pio_pin1_mask);
			pio_clear(n->pio_pin4, n->pio_pin1_mask);
		break;
		case 2:
			pio_clear(n->pio_pin1, n->pio_pin1_mask);
			pio_set(n->pio_pin2, n->pio_pin2_mask);
			pio_clear(n->pio_pin3, n->pio_pin1_mask);
			pio_set(n->pio_pin4, n->pio_pin1_mask);
		break;
		case 3:
			pio_set(n->pio_pin1, n->pio_pin1_mask);
			pio_clear(n->pio_pin2, n->pio_pin2_mask);
			pio_clear(n->pio_pin3, n->pio_pin1_mask);
			pio_set(n->pio_pin4, n->pio_pin1_mask);
		break;
	}
}