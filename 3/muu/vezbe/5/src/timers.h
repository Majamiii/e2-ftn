#ifndef TIMERS_H
#define TIMERS_H

void initTIM0(uint8_t mod, uint16_t reg_cnt, uint16_t soft_cnt);
void toggleTIM0_IT(uint8_t on_off);							   
void resetTIM0();											   
void toggleTIM0(uint8_t on_off);

void initTIM1(uint8_t mod, uint8_t reg_cnt, uint16_t soft_cnt);
void toggleTIM1_IT(uint8_t on_off);							   
void resetTIM1();											   
void toggleTIM1(uint8_t on_off);

extern volatile uint8_t tim0_1s;
extern volatile uint8_t tim1_2s;								   

#endif