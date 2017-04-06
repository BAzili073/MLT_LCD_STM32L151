#include "stm32l1xx_hal.h"
#include "stm32l151xba.h"
#include "defines.h"
#include "TIMs.h"
#include "Clock.h"
#include "LCD_func.h"
#include "Keyboard.h"

int main(void){

	Clock_init();
	TIM6_Init();
	TIM2_Init();
	GPIO_Init();
	KB_init();
			while_time(100);
			MTLCD_Init();
			while_time(1000);
			MTLCD_OnOff(1);
			MTLCD_CLR();
			MTLCD_SET_HALF(1,0);
			int i;
			char old = 4;
    while(1)
    {
//    	MTLCD_PRINT_STRING(1,1,"ABGT");
//    	MTLCD_CLR();
    	MTLCD_PRINT_STRING(0,0,"Введите номер спорстмена: ");
    	MTLCD_PRINT_NUMBER(50,1,137);
    	MTLCD_PRINT_STRING(0,2,"Вы находитесь на 3 рубеже");
    	//    	MTLCD_CLR();
		char u[1];
		u[0] = KB_check();
		if ((u[0] != 255)){
			if (old == 4){
					MTLCD_PRINT_STRING(1,5,u);
			}
			old = 0;
		}else{
			if (old < 4) old++;
		}
    }
}
