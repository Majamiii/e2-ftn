#include <stdint.h>
#include "utils.h"

uint8_t program_2(uint8_t prev){
	 if (prev == 0x80){ return 0x01; }
	 else {
		prev = prev << 1;
	 	return prev;
	}
}

uint8_t program_3(uint8_t prev, uint8_t lower, uint8_t to_left){
	  if (to_left){
	  		lower = lower << 1;
	  }else{
		lower = lower >> 1;
	  }
	  prev = ((lower & 0x01) << 3) | ((lower & 0x02) << 1) | ((lower & 0x04) >> 1) | ((lower & 0x08) >> 3);
	  prev = prev << 4;
	  prev += lower;
	  return prev;
}