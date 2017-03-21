#ifndef TIms_h
#define TIms_h
#include "stm32l1xx_hal.h"
#include "stm32l151xba.h"
void while_timeout();
void TIM6_Init(void);
void set_timeout(int t);
void while_timeout();
void while_time(int usec);







#else
#endif
