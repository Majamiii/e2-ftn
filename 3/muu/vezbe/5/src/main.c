#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "gpio.h"
#include "timers.h"
#include "utils.h"

int main(void){

	uint8_t P0_stanje;
	uint8_t P2_stanje = 0x00;     // trenutno stanje dioda

	uint8_t running = 0;          // 1 = program se izvrsava (start), 0 = stop
	uint8_t which_program = 1;    // 1..4
	uint8_t which_speed = 1;      // 1 ili 2
	uint8_t load_program = 1;     // 1 = treba ucitati pocetno stanje programa

	uint8_t lower_4_bites = 0x01; // donja 4 bita za program 3
	uint8_t to_left = 1;          // smer za program 3

	uint8_t reload = 256 - 250;          // 250 us pri 12 MHz
	uint16_t soft_cnt_speed1 = 4000;     // 2000 * 250us = 500 ms
	uint16_t soft_cnt_speed2 = 2000;     // 1000 * 250us = 250 ms

	init();
	initTIM1(2, reload, soft_cnt_speed1);   // tajmer 1, 8-bitni auto reload
	toggleTIM1_IT(1);

	while(true){
		P0_stanje = get_P0();

		// tasteri su aktivni na nuli
		if(!(P0_stanje & 0x01)){ running = 1; }                           // start
		if(!(P0_stanje & 0x02)){ running = 0; }                           // stop

		if(!(P0_stanje & 0x04)){ which_program = 1; load_program = 1; }   // program 1
		if(!(P0_stanje & 0x08)){ which_program = 2; load_program = 1; }   // program 2
		if(!(P0_stanje & 0x10)){ which_program = 3; load_program = 1; }   // program 3
		if(!(P0_stanje & 0x20)){ which_program = 4; load_program = 1; }   // program 4

		if(!(P0_stanje & 0x40) && which_speed != 1){                      // brzina 1
			which_speed = 1;
			initTIM1(2, reload, soft_cnt_speed1);
		}
		if(!(P0_stanje & 0x80) && which_speed != 2){                      // brzina 2
			which_speed = 2;
			initTIM1(2, reload, soft_cnt_speed2);
		}

		// ucitavanje pocetnog stanja izabranog programa
		if(load_program){
			load_program = 0;
			if(which_program == 1){
				P2_stanje = 0x00;
			}else if(which_program == 2){
				P2_stanje = 0x01;
			}else if(which_program == 3){
				lower_4_bites = 0x01;
				to_left = 1;
				P2_stanje = 0x81;
			}else{
				P2_stanje = 0x00;
			}
		}

		// jedan korak programa na svaki istek tajmera
		if(tim1_2s){
			tim1_2s = 0;
			if(running){
				if(which_program == 1){
					P2_stanje = ~P2_stanje;
				}else if(which_program == 2){
					P2_stanje = program_2(P2_stanje);
				}else if(which_program == 3){
					P2_stanje = program_3(P2_stanje, lower_4_bites, to_left);
					lower_4_bites = P2_stanje & 0x0F;
					if(lower_4_bites == 0x08){ to_left = 0; }
					if(lower_4_bites == 0x01){ to_left = 1; }
				}else{
					if(P2_stanje == 0xFF){
						P2_stanje = 0x00;
					}else{
						P2_stanje = (P2_stanje << 1) | 0x01;
					}
				}
			}
		}

		set_P2(P2_stanje);
	}

	return 0;
}