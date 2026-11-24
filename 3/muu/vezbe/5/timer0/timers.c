#include <stdint.h>
#include <at89c51rc2.h>
#include "timers.h"

uint16_t gl_reg_cnt;
uint16_t gl_soft_cnt;
uint16_t cnt;
volatile uint8_t tim0_1s;	// govori da ta promenljiva uvek treba dobije poslednju vrednost iz memorije
// nikad ne znamo kad ce biti prekid, pa treba da naglasimo da ne kesira ovo

void initTIM0(uint8_t mod, uint16_t reg_cnt, uint16_t soft_cnt){	// bilo bi 8_t da koristimo osmonitni rezim
	TMOD &= ~(0x03);
	TMOD |= (mod & 0x03);
	gl_reg_cnt = reg_cnt;
	gl_soft_cnt = soft_cnt;
 					 
	resetTIM0();
	toggleTIM0(1);
}

void toggleTIM0_IT(uint8_t on_off){
 	EA = (on_off & 0x01);	// omogucavanje prekida
	ET0 = (on_off & 0x01);  // omogucavanje rada tajmera
}

void resetTIM0(){
	TH0 = ((gl_reg_cnt>>8) & (0x00FF));		// moze i samo uint8_t(reg_cnt>>8)	
	TL0 = gl_reg_cnt & 0x00FF;
}

void toggleTIM0(uint8_t on_off){
 	TR0 = (on_off & 0x01);
}

void TIM0_IT() interrupt 1{		// timer0-1, timer1-3		 
	resetTIM0();
 	
	++cnt;
	if(cnt==gl_soft_cnt){
	 	cnt = 0;
		tim0_1s = 1;
	}

	TF0 = 0;

}