#include "Keyboard.h"
#include "defines.h"
#include "LCD_func.h"
#include "Hardware.h"


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

unsigned char CURRENT_NUMBER = 0;
unsigned char CURRENT_LAST_NUMBER = 0;

char get_current_number(){
	return CURRENT_NUMBER;
}


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

void KB_work(){
	static char  last_key = 255;
	char key = KB_check();
	if (key != last_key){
		last_key = key;
		if ((key != KB_DONT_PRESS)){
			switch (get_current_state()){
				case CURRENT_STATE_START:
				break;
				case CURRENT_STATE_DEFAULT:
					if (key == '*') {
						MTLCD_CLR();
						set_current_state(CURRENT_STATE_MENU_0);
					}
					if (key == 'A') {
						if (get_current_mode() == CURRENT_MODE_AUTO) set_current_mode(CURRENT_MODE_HAND);
						else if (get_current_mode() == CURRENT_MODE_HAND) set_current_mode(CURRENT_MODE_AUTO);
					}
					if (key == 'B') {
						if (get_current_max_shot() == 5) set_current_max_shot(8);
						else set_current_max_shot(5);
					}
					if (key == 'C') {
						if (get_current_position() == CURRENT_POSITION_LIE) set_current_position(CURRENT_POSITION_STAND);
						else set_current_position(CURRENT_POSITION_LIE);
					}
					if (key == 'D') {
						MTLCD_CLR();
						CURRENT_LAST_NUMBER = CURRENT_NUMBER;
						CURRENT_NUMBER = 0;
						set_current_state(CURRENT_STATE_MENU_0);
					}
				break;
				case CURRENT_STATE_MENU_0:
						if (key == 'A') {
							if (get_current_mode() == CURRENT_MODE_AUTO) set_current_mode(CURRENT_MODE_HAND);
							else if (get_current_mode() == CURRENT_MODE_HAND) set_current_mode(CURRENT_MODE_AUTO);
						}
						if (key == 'B') {
							if (get_current_max_shot() == 5) set_current_max_shot(8);
							else set_current_max_shot(5);
						}
						if (key == 'C') {
							if (get_current_position() == CURRENT_POSITION_LIE) set_current_position(CURRENT_POSITION_STAND);
							else set_current_position(CURRENT_POSITION_LIE);
						}
						if (key == '#') {
							MTLCD_CLR();
							set_current_state(CURRENT_STATE_DEFAULT);
						}
				break;
				case CURRENT_STATE_INPUT_NUMBER:
					if ((key >= '0') && (key <= '9')){
						CURRENT_NUMBER = CURRENT_NUMBER * 10 + (key - 48);
					}else{
						if (key == '*') {
							CURRENT_NUMBER = CURRENT_LAST_NUMBER;
							set_current_state(CURRENT_STATE_DEFAULT);
						}else if (key == '#') {
							set_current_state(CURRENT_STATE_DEFAULT);
						}
					}
				break;
			}
		}
	}
}

char KB_check(){
	int i;
	for (i = 0;i<KB_MAX_OUT;i++){
		GPIO_HIGH((KB_OUT[i].port),(KB_OUT[i].pin));
		int y;
		for (y = 0;y<KB_MAX_OUT;y++){
				if (GPIO_READ((KB_INP[y].port),(KB_INP[y].pin))){
					GPIO_LOW((KB_OUT[i].port),(KB_OUT[i].pin));
					return KB_keys[i][y];
				}
			}
		GPIO_LOW((KB_OUT[i].port),(KB_OUT[i].pin));
	}
	return KB_DONT_PRESS;
}
