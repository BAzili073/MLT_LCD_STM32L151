#include "stm32l1xx_hal.h"
#include "stm32l151xba.h"
#include "defines.h"
#include "TIMs.h"
#include "Clock.h"
#include "LCD_func.h"
#include "Keyboard.h"
#include "chars.h"

int main(void){

	Clock_init();
	TIM6_Init();
	TIM2_Init();

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	KB_init();
	GPIO_InitTypeDef initSrtuct;

			initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
			initSrtuct.Pin = LED_RED_PIN;
			initSrtuct.Pull = GPIO_NOPULL;
			initSrtuct.Speed = GPIO_SPEED_HIGH;
			HAL_GPIO_Init(LED_RED_PORT, &initSrtuct);


			while_time(100);
			MTLCD_Init();
			while_time(1000);
			MTLCD_OnOff(1);
			MTLCD_CLR();

			MTLCD_SET_HALF(1,0);
			int i;
			for(i = 0;i<8;i = i + 1){
				MTLCD_set_x(0);
				MTLCD_set_y(i);
				int y;
				for(y = 0;y<64;y++){
					MTLCD_DATA(HARD[i][y]);

				}
			}
			MTLCD_SET_HALF(0,1);
			for(i = 0;i<8;i++){
				MTLCD_set_x(0);
				MTLCD_set_y(i);
				int y;
				for(y = 0;y<8;y++){
					MTLCD_PRINT_BLOCK(FL[y + (i*8)]);
				}
			}
//			while(1);
//			for (i = 0; i<3000;i++) while_time(1000);
			MTLCD_CLR();
			MTLCD_SET_HALF(1,1);
			MTLCD_set_x(1);
			MTLCD_set_y(1);
			int y;
			for(y = 0;y<64;y++){
				MTLCD_DATA(0x55);
				MTLCD_DATA(0xAA);
			}
			MTLCD_set_x(3);
			MTLCD_set_y(3);
			MTLCD_PRINT_BLOCK(FULL_CIRC);
			MTLCD_PRINT_BLOCK(FULL_CIRC);
			MTLCD_PRINT_BLOCK(EMPTY_CIRC);
			MTLCD_PRINT_BLOCK(EMPTY_CIRC);
			MTLCD_set_x(1);
			MTLCD_set_y(5);
			MTLCD_PRINT_BLOCK(STANDUP1);
			MTLCD_PRINT_BLOCK(STANDUP2);
			MTLCD_set_x(1);
			MTLCD_set_y(6);
			MTLCD_PRINT_BLOCK(STANDUP3);
			MTLCD_SET_HALF(1,0);
			MTLCD_set_x(1);
			MTLCD_set_y(4);
//			int i;
			for (i = 0;i<8;i++){
				MTLCD_PRINT_BLOCK(numbers[i]);
			}
			MTLCD_SET_HALF(0,1);
			MTLCD_set_x(1);
			MTLCD_set_y(4);
			for (i = 8;i<10;i++){
				MTLCD_PRINT_BLOCK(numbers[i]);
			}
			MTLCD_SET_HALF(0,1);
			MTLCD_set_x(1);
			MTLCD_set_y(4);
			for (i = 8;i<10;i++){
				MTLCD_PRINT_BLOCK(numbers[i]);
			}
			MTLCD_SET_HALF(1,0);
			MTLCD_set_x(18);
			MTLCD_set_y(5);
			for (i = 0;i<4;i++){
				MTLCD_PRINT_BLOCK(BIG_CIRC[i]);
			}
			MTLCD_set_x(18);
			MTLCD_set_y(6);
			for (i = 4;i<8;i++){
				MTLCD_PRINT_BLOCK(BIG_CIRC[i]);
			}
			MTLCD_SET_HALF(0,1);
			MTLCD_set_x(18);
			MTLCD_set_y(5);
			for (i = 0;i<2;i++){
				MTLCD_PRINT_BLOCK(DOWN_MAN[i]);
			}
			char old = 4;
    while(1)
    {
    	MTLCD_SET_HALF(1,1);
		MTLCD_set_x(1);
		MTLCD_set_y(7);
		MTLCD_PRINT_BLOCK(numbers[min/10]);
		MTLCD_PRINT_BLOCK(numbers[min%10]);
		MTLCD_DATA(0x00);
		MTLCD_DATA(0x6C);
		MTLCD_DATA(0x00);
		MTLCD_PRINT_BLOCK(numbers[secons/10]);
		MTLCD_PRINT_BLOCK(numbers[secons%10]);
		MTLCD_DATA(0xC0);
		MTLCD_DATA(0xC0);
		MTLCD_DATA(0x00);
		MTLCD_PRINT_BLOCK(numbers[dsec]);
//    	MTLCD_CLR();
		char u = KB_check();
		if ((u != 255)){
			if (old == 4){
				MTLCD_SET_HALF(0,1);
				MTLCD_set_x(50);
				MTLCD_set_y(4);
				int i;
				for(i = 0;i<5;i++){
					MTLCD_DATA(symb[u][i]);
				}
			}
			old = 0;
		}else{
			if (old < 4) old++;
		}
    }
}
