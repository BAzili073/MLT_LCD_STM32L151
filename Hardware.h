#ifndef Hardware_h
#include "stm32l1xx_hal.h"
#include "stm32l151xba.h"
#define Hardware_h
#include "defines.h"

char get_target(unsigned char num);
char get_current_state();
char get_current_mode();
char get_current_max_shot();
void set_current_state(unsigned char new_state);
void set_current_mode(unsigned char new_mode);
void set_current_max_shot(unsigned char new_max_shot);











#else
#endif
