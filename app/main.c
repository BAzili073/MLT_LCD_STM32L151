#include "stm32l1xx_hal.h"
#include "stm32l151xba.h"
#include "defines.h"
#include "TIMs.h"
#include "Clock.h"
#include "LCD_func.h"
char FULL_CIRC[8]  = {0x3C,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x3C};
char EMPTY_CIRC[8]  = {0x3C,0x42,0x81,0x81,0x81,0x81,0x42,0x3C};

char STANDUP1[8]  = {0xC0,0xCE,0xF1,0xF1,0x51,0x4E,0xE0,0xE0};
char STANDUP2[8]  = {0xE0,0xC0,0x40,0x40,0x40,0x40,0x00,0x00};
char STANDUP3[8]  = {0xF8,0xFF,0x0F,0xF9,0xF9,0x01,0x01,0x00};
int main(void){

	Clock_init();
	TIM6_Init();

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

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

    while(1)
    {
    	int i;
    	for (i = 0;i<10;i++){
    		set_timeout(100);
    		while_timeout();
    	}
    	LED_RED_PORT->ODR ^= LED_RED_PIN;
//    	MTLCD_CLR();
    }
}
