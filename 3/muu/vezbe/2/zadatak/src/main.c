#include <stdint.h>
#include <stdbool.h>
#include <at89c51rc2.h>	
#include <stdlib.h>

#include "gpio.h"
#include "utils.h"

int main(void){

  	uint8_t P0_state = P0;
    uint8_t P2_state = 0x00;
    uint8_t state_changed = 0x00;	 
    uint8_t out_state = 0x00;
    uint8_t start = 0x00;
    uint8_t stop = 0x00;
	uint8_t working = 0x00;
	uint8_t which_program = 0x00;
	uint8_t which_speed = 0x00;
	uint8_t lower_4_bites = 0x00;
	uint8_t to_left = 0x00;

	init();

	while(true){

		P0_state = get_P0();
		
		// start
		if (((P0_state & 0x01) != 0)||(working==0x01)) {
			working = 0x01;
		}

		// stop
		if ((P0_state & 0x02) != 0){
			working = 0x00;
			set_P2(0x00);
			continue;
		}
		
		if ((P0_state & 0x3c)!=0) {
			which_program = P0_state & 0x3c; // 00111100
			which_program = which_program >> 2;
		}

		// program 1
		if ((((P0_state & 0x04) != 0)||(which_program == 0x01))&&(working))  {
			 if ((P0_state & 0x04) != 0) {
			 	out_state = 0xFF;
			 }
			 which_program = 0x01;
			 out_state = ~out_state;
		}

		// program 2
		else if ((((P0_state & 0x08) != 0)||(which_program == 0x02))&&(working)){
			which_program = 0x02;
			out_state = program_2(out_state);
			if ((P0_state & 0x08) != 0) {
			   out_state = 0x01;
			}
		}

		// program 3
		else if ((((P0_state & 0x10) != 0)||(which_program == 0x04))&&(working)){
			which_program = 0x04;
			lower_4_bites = out_state & 0x0F;
			if (lower_4_bites == 0x01){to_left = 1;} else if (lower_4_bites == 0x08) {to_left = 0;}
			out_state = program_3(out_state, lower_4_bites, to_left);
			if ((P0_state & 0x10) != 0) {
			   out_state = 0x81;
			}
		}

		// program 4
		else if ((((P0_state & 0x20) != 0)||(which_program == 0x08))&&(working)){
			which_program = 0x08;
			out_state = rand() % 0xFF;
		}
		
		set_P2(out_state);

		// speed 1
		if ((((P0_state & 0x40)!= 0)||(which_speed == 0x01))&&(working)) {
			which_speed == 0x01;
			delay_speed_1();
		}

		// speed 2
		else if ((((P0_state & 0x80)!= 0)||(which_speed == 0x02))&&(working)) {
			which_speed == 0x02;
			delay_speed_2();
		}

	}

	return 0;
}