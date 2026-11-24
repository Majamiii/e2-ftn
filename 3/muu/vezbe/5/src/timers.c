#include <stdint.h>
#include <at89c51rc2.h>
#include "timers.h"

uint16_t gl_reg_cnt;
uint16_t gl_soft_cnt;
uint16_t cnt;
volatile uint8_t tim0_1s;	// govori da ta promenljiva uvek treba dobije poslednju vrednost iz memorije
// nikad ne znamo kad ce biti prekid, pa treba da naglasimo da ne kesira ovo
volatile uint8_t tim1_2s;

void initTIM0(uint8_t mod, uint16_t reg_cnt, uint16_t soft_cnt){	// bilo bi 8_t da koristimo osmonitni rezim
	toggleTIM0_IT(0);
	TMOD &= ~(0x03);
	TMOD |= (mod & 0x03);
	gl_reg_cnt = reg_cnt;
	gl_soft_cnt = soft_cnt;

	cnt = 0;
	tim0_1s = 0;
 					 
	resetTIM0();
	toggleTIM0(1);
	toggleTIM0_IT(1);
}

void initTIM1(uint8_t mod, uint8_t reg_cnt, uint16_t soft_cnt){
	toggleTIM1_IT(0);
	TMOD &= ~0xF0;
	TMOD |= (mod & 0x03) << 4;   // mod = 2 for 8-bit auto-reload
	gl_reg_cnt = reg_cnt;
	gl_soft_cnt = soft_cnt;
	cnt = 0;
	tim1_2s = 0;
 					 
	resetTIM1();
	toggleTIM1(1);
	toggleTIM1_IT(1);
}

void toggleTIM0_IT(uint8_t on_off){
 	EA = (on_off & 0x01);	// omogucavanje prekida
	ET0 = (on_off & 0x01);  // omogucavanje rada tajmera
}

void toggleTIM1_IT(uint8_t on_off){
 	EA = (on_off & 0x01);	// omogucavanje prekida
	ET1 = (on_off & 0x01);  // omogucavanje rada tajmera
}

void resetTIM0(){
	TH0 = ((gl_reg_cnt>>8) & (0x00FF));		// moze i samo uint8_t(reg_cnt>>8)	
	TL0 = gl_reg_cnt & 0x00FF;
}

void resetTIM1(){	
	TH1 = gl_reg_cnt;
	TL1 = gl_reg_cnt;
}

void toggleTIM0(uint8_t on_off){
 	TR0 = (on_off & 0x01);
}

void toggleTIM1(uint8_t on_off){
 	TR1 = (on_off & 0x01);
}

void TIM0_IT() interrupt 1{		// timer0-1, timer1-3		 
	resetTIM0();
 	
	++cnt;
	if(cnt>=gl_soft_cnt){
	 	cnt = 0;
		tim0_1s = 1;
	}

	
	TF0 = 0;

}

void TIM1_IT() interrupt 3{		// timer0-1, timer1-3		 
	resetTIM1();
 	
	++cnt;
	if(cnt>=gl_soft_cnt){
	 	cnt = 0;
		tim1_2s = 1;
	}

	TF1 = 0;

}