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

    while(1)
    {
    	MTLCD_DISPLAY();
//    	MTLCD_PRINT_STRING(1,1,"ABGT");
//    	MTLCD_CLR();

    	//    	MTLCD_CLR();

    	KB_work();

    }
}
