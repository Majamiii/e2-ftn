#include <stdint.h>
#include <stdbool.h>	
#include <stdlib.h>

#include "gpio.h"
#include "timers.h"

int main(void){

	uint8_t start;
  	uint8_t P0_stanje;
    uint8_t P2_stanje;

	init();
	initTIM0(1, 56320, 100); // 0xDC00, 10ms
	toggleTIM0_IT(1);

	while(true){
		P0_stanje = get_P0();
	
		if(!(P0_stanje & 0x01)){
		  	start=1;
		}
		if(!(P0_stanje & 0x02)){
		  	start=0;
		}
		if(tim0_1s){
			tim0_1s = 0;
			if(start){
			 	P2_stanje = ~P2_stanje;
			}
		}
		set_P2(P2_stanje);

	}

	return 0;
}