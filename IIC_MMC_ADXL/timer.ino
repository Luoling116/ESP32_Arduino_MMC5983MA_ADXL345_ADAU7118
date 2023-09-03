#include "timer.h"

void timerInit(){

  timer0Semaphore = xSemaphoreCreateBinary();
  timer1Semaphore = xSemaphoreCreateBinary();

  timer0 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer0, ontimer0, true);
  timerAlarmWrite(timer0, 5000, true); //5ms
  timerAlarmEnable(timer0);

  timer1 = timerBegin(3, 80, true);
  timerAttachInterrupt(timer1, ontimer1, true);
  timerAlarmWrite(timer1, 1000000, true); //1000ms
  timerAlarmEnable(timer1);
}

//ISR
void IRAM_ATTR ontimer0(){
  portENTER_CRITICAL_ISR(&timerMux0);
  count0++;
  time0 = micros();
  portEXIT_CRITICAL_ISR(&timerMux0);

  xSemaphoreGiveFromISR(timer0Semaphore, NULL);
}

void IRAM_ATTR ontimer1(){
  portENTER_CRITICAL_ISR(&timerMux1);
  count1++;
  time1 = micros();
  portEXIT_CRITICAL_ISR(&timerMux1);

  xSemaphoreGiveFromISR(timer1Semaphore, NULL);
}