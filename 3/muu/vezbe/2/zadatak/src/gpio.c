
#include <stdint.h>
#include <at89c51rc2.h>
#include "gpio.h"

void  init(){

 	P2 = 0xFF;
	P0 = 0x00;

}

uint8_t get_P0(){ return P0; }

void set_P2(uint8_t p){	   P2 = p; }