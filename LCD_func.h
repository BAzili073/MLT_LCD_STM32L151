#ifndef LCD_func_h
#define LCD_func_h
#include "stm32l1xx_hal.h"
#include "stm32l151xba.h"
void MTLCD_CLR();
void MTLCD_set_y(unsigned char pos_y);
void MTLCD_set_x(unsigned char pos_x);
void MTLCD_Init();
void MTLCD_DATA(unsigned char data);
void MTLCD_CMD(unsigned char cmd);
void MTLCD_OnOff(char status);
void MTLCD_SET_HALF(char f,char s);
void MTLCD_PRINT_BLOCK(char * block);





#else
#endif
