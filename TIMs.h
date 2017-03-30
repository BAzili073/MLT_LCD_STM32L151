#ifndef TIMs_h
#define TIMs_h
#include "stm32l1xx_hal.h"
#include "stm32l151xba.h"
void while_timeout();
void TIM6_Init(void);
void set_timeout(int t);
void while_timeout();
void while_time(int usec);
int secons;
int min;
int dsec;





#else
#endif
