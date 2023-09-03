#ifndef TIMER_H_
#define TIMER_H_

#include <Arduino.h>
#include <esp32-hal-timer.h>

hw_timer_t* timer0 = NULL;
hw_timer_t* timer1 = NULL;

volatile int count0 = 0;
volatile int count1 = 0;
volatile uint32_t time0 = 0;
volatile uint32_t time1 = 0;

volatile SemaphoreHandle_t timer0Semaphore;
volatile SemaphoreHandle_t timer1Semaphore;

portMUX_TYPE timerMux0 = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE timerMux1 = portMUX_INITIALIZER_UNLOCKED;

void timerInit();
void IRAM_ATTR ontimer0();
void IRAM_ATTR ontimer1();

#endif
