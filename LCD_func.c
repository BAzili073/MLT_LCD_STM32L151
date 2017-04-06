#include "stm32l1xx_hal.h"
#include "stm32l151xba.h"
#include "LCD_func.h"
#include "defines.h"
#include "TIMs.h"
#include "chars.h"

#define MTLCD_DB0_PORT GPIOA
#define MTLCD_DB0_PIN GPIO_PIN_11
#define MTLCD_DB1_PORT GPIOA
#define MTLCD_DB1_PIN GPIO_PIN_10
#define MTLCD_DB2_PORT GPIOA
#define MTLCD_DB2_PIN GPIO_PIN_9
#define MTLCD_DB3_PORT GPIOA
#define MTLCD_DB3_PIN GPIO_PIN_8
#define MTLCD_DB4_PORT GPIOC
#define MTLCD_DB4_PIN GPIO_PIN_9
#define MTLCD_DB5_PORT GPIOC
#define MTLCD_DB5_PIN GPIO_PIN_8
#define MTLCD_DB6_PORT GPIOC
#define MTLCD_DB6_PIN GPIO_PIN_7
#define MTLCD_DB7_PORT GPIOC
#define MTLCD_DB7_PIN GPIO_PIN_6
#define MTLCD_A0_PORT GPIOC
#define MTLCD_A0_PIN GPIO_PIN_0
#define MTLCD_RW_PORT GPIOC
#define MTLCD_RW_PIN GPIO_PIN_1
#define MTLCD_E_PORT GPIOC
#define MTLCD_E_PIN GPIO_PIN_2
#define MTLCD_E1_PORT GPIOA
#define MTLCD_E1_PIN GPIO_PIN_1
#define MTLCD_E2_PORT GPIOA
#define MTLCD_E2_PIN GPIO_PIN_2
#define MTLCD_RES_PORT GPIOA
#define MTLCD_RES_PIN GPIO_PIN_3



void MTLCD_set_DB_port(unsigned char cmd);
void MTLCD_accept_DB_port();
void MTLCD_set_DB_port(unsigned char cmd);

void MTLCD_accept_DB_port(){
	  GPIO_HIGH(MTLCD_E_PORT,MTLCD_E_PIN); //cmd_port |= (1<<E);//устанавливаем "1" на E
	  while_time(1);
	  GPIO_LOW(MTLCD_E_PORT,MTLCD_E_PIN);// cmd_port &= ~(1<<E);// сбрасываем Е
	  while_time(8);
}


void MTLCD_set_DB_port(unsigned char cmd){
(cmd&(1<<0)) ? (GPIO_HIGH(MTLCD_DB0_PORT,MTLCD_DB0_PIN)) : (GPIO_LOW(MTLCD_DB0_PORT,MTLCD_DB0_PIN));
(cmd&(1<<1)) ? (GPIO_HIGH(MTLCD_DB1_PORT,MTLCD_DB1_PIN)) : (GPIO_LOW(MTLCD_DB1_PORT,MTLCD_DB1_PIN));
(cmd&(1<<2)) ? (GPIO_HIGH(MTLCD_DB2_PORT,MTLCD_DB2_PIN)) : (GPIO_LOW(MTLCD_DB2_PORT,MTLCD_DB2_PIN));
(cmd&(1<<3)) ? (GPIO_HIGH(MTLCD_DB3_PORT,MTLCD_DB3_PIN)) : (GPIO_LOW(MTLCD_DB3_PORT,MTLCD_DB3_PIN));
(cmd&(1<<4)) ? (GPIO_HIGH(MTLCD_DB4_PORT,MTLCD_DB4_PIN)) : (GPIO_LOW(MTLCD_DB4_PORT,MTLCD_DB4_PIN));
(cmd&(1<<5)) ? (GPIO_HIGH(MTLCD_DB5_PORT,MTLCD_DB5_PIN)) : (GPIO_LOW(MTLCD_DB5_PORT,MTLCD_DB5_PIN));
(cmd&(1<<6)) ? (GPIO_HIGH(MTLCD_DB6_PORT,MTLCD_DB6_PIN)) : (GPIO_LOW(MTLCD_DB6_PORT,MTLCD_DB6_PIN));
(cmd&(1<<7)) ? (GPIO_HIGH(MTLCD_DB7_PORT,MTLCD_DB7_PIN)) : (GPIO_LOW(MTLCD_DB7_PORT,MTLCD_DB7_PIN));
}

void MTLCD_CMD(unsigned char cmd){
  while_time(1);
  MTLCD_set_DB_port(cmd);
  //MTLCD_DB_PORT -> ODR |= (cmd << 9);// data_port = cmd;//выводим команду на DB0-DB7
  while_time(1);
  MTLCD_accept_DB_port();
}

void MTLCD_DATA(unsigned char data){
  while_time(1);
  MTLCD_set_DB_port(data); //  data_port = data;//данные на DB0-DB7
  while_time(1);
  GPIO_HIGH(MTLCD_A0_PORT,MTLCD_A0_PIN);// cmd_port |= (1<<DI);//устанавливаем "1" на DI - передаются данные
  while_time(1);
  MTLCD_accept_DB_port();
  GPIO_LOW(MTLCD_A0_PORT,MTLCD_A0_PIN);//cmd_port &= ~(1<<DI);// сбрасываем DI
  while_time(1);
 }


void MTLCD_Init(){
	GPIO_InitTypeDef initSrtuct;

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_A0_PIN;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_A0_PORT, &initSrtuct);

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_E1_PIN ;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_E1_PORT, &initSrtuct);

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_E2_PIN ;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_E2_PORT, &initSrtuct);

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_E_PIN ;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_E_PORT, &initSrtuct);

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_RES_PIN ;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_RES_PORT, &initSrtuct);

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_RW_PIN ;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_RW_PORT, &initSrtuct);

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_DB0_PIN ;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_DB0_PORT, &initSrtuct);

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_DB1_PIN ;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_DB1_PORT, &initSrtuct);

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_DB2_PIN ;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_DB2_PORT, &initSrtuct);

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_DB3_PIN ;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_DB3_PORT, &initSrtuct);

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_DB4_PIN ;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_DB4_PORT, &initSrtuct);

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_DB5_PIN ;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_DB5_PORT, &initSrtuct);

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_DB6_PIN ;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_DB6_PORT, &initSrtuct);

				initSrtuct.Mode = GPIO_MODE_OUTPUT_PP;
				initSrtuct.Pin = MTLCD_DB7_PIN ;
				initSrtuct.Pull = GPIO_NOPULL;
				initSrtuct.Speed = GPIO_SPEED_HIGH;
				HAL_GPIO_Init(MTLCD_DB7_PORT, &initSrtuct);

  GPIO_LOW(MTLCD_RW_PORT,MTLCD_RW_PIN);
  GPIO_LOW(MTLCD_A0_PORT,MTLCD_A0_PIN);
  GPIO_HIGH(MTLCD_RES_PORT,MTLCD_RES_PIN);
  while_time(12);
  GPIO_LOW(MTLCD_RES_PORT,MTLCD_RES_PIN);
  while_time(2);
  GPIO_HIGH(MTLCD_RES_PORT,MTLCD_RES_PIN);
  while_time(12);
//  cmd_port &=~((1<<CS2)|(1<<CS1));
//  cmd_port |= (1<<CS2);
//  lcd_cmd(0x3F);
//  cmd_port &=~((1<<CS2)|(1<<CS1));
//  cmd_port |= (1<<CS1);
//  lcd_cmd(0x3F);
}

void MTLCD_OnOff(char status){
	MTLCD_SET_HALF(1,1);
	 MTLCD_CMD((0x3E | status));
	 MTLCD_SET_HALF(0,0);
}

void MTLCD_set_x(unsigned char pos_x){
  MTLCD_set_DB_port(pos_x|0x40);//Координата X
  while_time(1);
  MTLCD_accept_DB_port();
}

void MTLCD_set_y(unsigned char pos_y){
  MTLCD_set_DB_port(pos_y|0xB8);//Координата Y
  while_time(1);
  MTLCD_accept_DB_port();
}

void MTLCD_set_cord(unsigned char x,unsigned char y){
if (x >= 64) {
	x = x - 64;
	MTLCD_SET_HALF(0,1);
}else{
	MTLCD_SET_HALF(1,0);
}
MTLCD_set_x(x);
MTLCD_set_y(y);
}

void MTLCD_CLR(){
	MTLCD_SET_HALF(1,1);
  for(unsigned char i=0; i<8; i++){
	  MTLCD_CMD(0xB8+i);
   for(unsigned char j=0; j<64; j++){
	   MTLCD_CMD(0x40+j);
	   MTLCD_DATA(0x00);//записываем везде 0
    }
  }
  MTLCD_SET_HALF(0,0);
}

void MTLCD_SET_HALF(char f,char s){
	f ? (GPIO_HIGH(MTLCD_E1_PORT,MTLCD_E1_PIN)) : (GPIO_LOW(MTLCD_E1_PORT,MTLCD_E1_PIN));
	s ? (GPIO_HIGH(MTLCD_E2_PORT,MTLCD_E2_PIN)) : (GPIO_LOW(MTLCD_E2_PORT,MTLCD_E2_PIN));
}


void MTLCD_PRINT_BLOCK(char * block){
	int i;
	for(i = 0;i<8;i++){
		MTLCD_DATA(block[i]);
	}
}

void MTLCD_PRINT_CHAR(unsigned char x, unsigned char y,char * block){

	int i;
	static int cur_half = 0;
	MTLCD_set_cord(x,y);
	for(i = 0;i<5;i++){
		int x_cur = x + i;
		if (x_cur == 64){
			MTLCD_set_cord(x_cur,y);
		}else if (x_cur == 128){
			MTLCD_set_cord(0,(y+1));
		}
		MTLCD_DATA(block[i]);
	}
}

void MTLCD_PRINT_STRING(unsigned char x, unsigned char y, char * text){
	int i = 0;
	char ch;
	while(text[i]){
		ch = text[i];
		if(ch<0x90) ch = ch - 0x20;
		else ch = ch - 0x60;
		if (x > 120){
			x = 0;
			y++;
		}
    	MTLCD_PRINT_CHAR(x, y, sym[ch]);
    	MTLCD_DATA(0x00);
    	x = x + 7;
    	i++;
	}
}

void MTLCD_PRINT_NUMBER(unsigned char x, unsigned char y,unsigned char num){
char num_t[3];
num_t[0] = num/100;
num_t[1] = (num - num_t[0]*100)/10;
num_t[2] = (num - num_t[0]*100 - num_t[1]*10);
int i;
for(i = 0;i<3;i++) num_t[i] = num_t[i] + '0';
MTLCD_PRINT_STRING(x,y,num_t);
}
//void MTLCD_PRINT_TIME(char x, char y, int sec){
//  		MTLCD_SET_HALF(1,1);
//		MTLCD_set_x(1);
//		MTLCD_set_y(7);
//		MTLCD_PRINT_BLOCK(numbers[min/10]);
//		MTLCD_PRINT_BLOCK(numbers[min%10]);
//		MTLCD_DATA(0x00);
//		MTLCD_DATA(0x6C);
//		MTLCD_DATA(0x00);
//		MTLCD_PRINT_BLOCK(numbers[secons/10]);
//		MTLCD_PRINT_BLOCK(numbers[secons%10]);
//		MTLCD_DATA(0xC0);
//		MTLCD_DATA(0xC0);
//		MTLCD_DATA(0x00);
//		MTLCD_PRINT_BLOCK(numbers[dsec]);
//}

//void MTLCD_READ_STATUS(){
//	GPIO_HIGH()
//	MTLCD_CMD()
//}



//for(i = 0;i<8;i = i + 1){
//	MTLCD_set_x(0);
//	MTLCD_set_y(i);
//	int y;
//	for(y = 0;y<64;y++){
//		MTLCD_DATA(HARD[i][y]);
//
//	}
//}
//MTLCD_SET_HALF(0,1);
//for(i = 0;i<8;i++){
//	MTLCD_set_x(0);
//	MTLCD_set_y(i);
//	int y;
//	for(y = 0;y<8;y++){
//		MTLCD_PRINT_BLOCK(FL[y + (i*8)]);
//	}
//}
////			while(1);
////			for (i = 0; i<3000;i++) while_time(1000);
//MTLCD_CLR();
//MTLCD_SET_HALF(1,1);
//MTLCD_set_x(1);
//MTLCD_set_y(1);
//int y;
//for(y = 0;y<64;y++){
//	MTLCD_DATA(0x55);
//	MTLCD_DATA(0xAA);
//}
//MTLCD_set_x(3);
//MTLCD_set_y(3);
//MTLCD_PRINT_BLOCK(FULL_CIRC);
//MTLCD_PRINT_BLOCK(FULL_CIRC);
//MTLCD_PRINT_BLOCK(EMPTY_CIRC);
//MTLCD_PRINT_BLOCK(EMPTY_CIRC);
//MTLCD_set_x(1);
//MTLCD_set_y(5);
//MTLCD_PRINT_BLOCK(STANDUP1);
//MTLCD_PRINT_BLOCK(STANDUP2);
//MTLCD_set_x(1);
//MTLCD_set_y(6);
//MTLCD_PRINT_BLOCK(STANDUP3);
//MTLCD_SET_HALF(1,0);
//MTLCD_set_x(1);
//MTLCD_set_y(4);
////			int i;
//for (i = 0;i<8;i++){
//	MTLCD_PRINT_BLOCK(numbers[i]);
//}
//MTLCD_SET_HALF(0,1);
//MTLCD_set_x(1);
//MTLCD_set_y(4);
//for (i = 8;i<10;i++){
//	MTLCD_PRINT_BLOCK(numbers[i]);
//}
//MTLCD_SET_HALF(0,1);
//MTLCD_set_x(1);
//MTLCD_set_y(4);
//for (i = 8;i<10;i++){
//	MTLCD_PRINT_BLOCK(numbers[i]);
//}
//MTLCD_SET_HALF(1,0);
//MTLCD_set_x(18);
//MTLCD_set_y(5);
//for (i = 0;i<4;i++){
//	MTLCD_PRINT_BLOCK(BIG_CIRC[i]);
//}
//MTLCD_set_x(18);
//MTLCD_set_y(6);
//for (i = 4;i<8;i++){
//	MTLCD_PRINT_BLOCK(BIG_CIRC[i]);
//}
//MTLCD_SET_HALF(0,1);
//MTLCD_set_x(18);
//MTLCD_set_y(5);
//for (i = 0;i<2;i++){
//	MTLCD_PRINT_BLOCK(DOWN_MAN[i]);
//}

