#ifdef DEFINES_H
#else
#define DEFINES_H

#define time_out ((TIM6->SR & TIM_SR_UIF) != 0)

#define LED_RED_PORT GPIOB
#define LED_RED_PIN GPIO_PIN_7


#define GPIO_HIGH(PORT, PIN) (PORT->BSRR) = (PIN)
#define GPIO_LOW(PORT, PIN) (PORT->BSRR) = ((PIN)<<16)
#define GPIO_READ(PORT, PIN) (PORT->IDR)&(PIN)
#define GPIO_TOGGLE(PORT, PIN) ((PORT)->ODR) ^= (PIN)

#define CURRENT_MODE_AUTO 0
#define CURRENT_MODE_HAND 1

#define CURRENT_STATE_START 0
#define CURRENT_STATE_DEFAULT 1
#define CURRENT_STATE_MENU_0 2

#endif
