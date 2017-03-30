#include "Keyboard.h"
#include "defines.h"


#define KB_DONT_PRESS 255

#define KB_MAX_OUT 4
#define KB_MAX_INP 4

#define KB_OUT_1_PORT GPIOA
#define KB_OUT_2_PORT GPIOB
#define KB_OUT_3_PORT GPIOB
#define KB_OUT_4_PORT GPIOB

#define KB_OUT_1_PIN GPIO_PIN_5
#define KB_OUT_2_PIN GPIO_PIN_2
#define KB_OUT_3_PIN GPIO_PIN_10
#define KB_OUT_4_PIN GPIO_PIN_11

#define KB_INP_1_PORT GPIOB
#define KB_INP_2_PORT GPIOB
#define KB_INP_3_PORT GPIOB
#define KB_INP_4_PORT GPIOB

#define KB_INP_1_PIN GPIO_PIN_12
#define KB_INP_2_PIN GPIO_PIN_13
#define KB_INP_3_PIN GPIO_PIN_14
#define KB_INP_4_PIN GPIO_PIN_15

typedef struct KB_OUT_obj{
	GPIO_TypeDef * port;
	uint16_t  pin;
} KB_OUT_obj;

KB_OUT_obj KB_OUT[KB_MAX_OUT] = {
		[0] = { .port = KB_OUT_1_PORT, .pin = KB_OUT_1_PIN},
		[1] = { .port = KB_OUT_2_PORT, .pin = KB_OUT_2_PIN},
		[2] = { .port = KB_OUT_3_PORT, .pin = KB_OUT_3_PIN},
		[3] = { .port = KB_OUT_4_PORT, .pin = KB_OUT_4_PIN},
};

typedef struct KB_INP_obj{
	GPIO_TypeDef * port;
	uint16_t  pin;
} KB_INP_obj;

KB_INP_obj KB_INP[KB_MAX_INP] = {
		[0] = { .port = KB_INP_1_PORT, .pin = KB_INP_1_PIN},
		[1] = { .port = KB_INP_2_PORT, .pin = KB_INP_2_PIN},
		[2] = { .port = KB_INP_3_PORT, .pin = KB_INP_3_PIN},
		[3] = { .port = KB_INP_4_PORT, .pin = KB_INP_4_PIN},
};

char KB_keys[4][4] = {
		[0] = {'1','2','3','A'},
		[1] = {'4','5','6','B'},
		[2] = {'7','8','9','C'},
		[3] = {'*','0','#','D'},
};
void KB_init(){
	GPIO_InitTypeDef initSrtuct;
	int y;
	for (y = 0;y<KB_MAX_OUT;y++){
		initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
		initSrtuct.Pin = (KB_OUT[y].pin);
		initSrtuct.Pull = GPIO_NOPULL;
		initSrtuct.Speed = GPIO_SPEED_HIGH;
		HAL_GPIO_Init((KB_OUT[y].port), &initSrtuct);
		GPIO_LOW((KB_OUT[y].port),(KB_OUT[y].pin));
	}
	for (y = 0;y<KB_MAX_INP;y++){
		initSrtuct.Alternate = 0;
		initSrtuct.Mode = GPIO_MODE_INPUT;
		initSrtuct.Pull = GPIO_PULLDOWN;
		initSrtuct.Pin = (KB_INP[y].pin);
		initSrtuct.Speed = GPIO_SPEED_HIGH;
		HAL_GPIO_Init( (KB_INP[y].port), &initSrtuct);
	}
//	while(1){
//		char u = KB_check();
//		if (u != 255){
//			MTLCD_DATA(0x00);
//		}
//	}
}
char KB_check(){
	int i;
	for (i = 0;i<KB_MAX_OUT;i++){
		GPIO_HIGH((KB_OUT[i].port),(KB_OUT[i].pin));
		int y;
		for (y = 0;y<KB_MAX_OUT;y++){
				if (GPIO_READ((KB_INP[y].port),(KB_INP[y].pin))){
					return KB_keys[i][y];
				}
			}
		GPIO_LOW((KB_OUT[i].port),(KB_OUT[i].pin));
	}
	return KB_DONT_PRESS;
}
