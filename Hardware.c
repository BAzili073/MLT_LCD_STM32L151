#include "Hardware.h"

unsigned char TARGET[5] = {0,0,0,0,0};
unsigned char CURRENT_STATE = CURRENT_STATE_DEFAULT;
unsigned char CURRENT_MODE = CURRENT_MODE_AUTO;
unsigned char CURRENT_MAX_SHOT = 5;
unsigned char CURRENT_SHOT = 0;
unsigned char CURRENT_POSITION = 0;

char get_target(unsigned char num){
	if (num > 4) num = 0;
	return TARGET[num];
}

char get_current_state(){
	return CURRENT_STATE;
}

char get_current_mode(){
	return CURRENT_MODE;
}

char get_current_max_shot(){
	return CURRENT_MAX_SHOT;
}

char get_current_shot(){
	return CURRENT_SHOT;
}

char get_current_position(){
	return CURRENT_POSITION;
}

void set_current_position(unsigned char new_position){
	CURRENT_POSITION = new_position;
}

void set_current_state(unsigned char new_state){
	CURRENT_STATE = new_state;
}

void set_current_mode(unsigned char new_mode){
	CURRENT_MODE = new_mode;
}

void set_current_max_shot(unsigned char new_max_shot){
	CURRENT_MAX_SHOT = new_max_shot;
}

void restore_targets(){

}




