#include "stm32l1xx_hal.h"
#include "stm32l151xba.h"
#include "LCD_func.h"
#include "defines.h"
#include "TIMs.h"

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

//void MTLCD_READ_STATUS(){
//	GPIO_HIGH()
//	MTLCD_CMD()
//}
