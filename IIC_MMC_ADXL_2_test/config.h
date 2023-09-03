#ifndef CONFIG_H_
#define CONFIG_H_

#include <Wire.h>
#include <ADXL345_WE.h>
#include <SparkFun_MMC5983MA_Arduino_Library.h>
#include <SPI.h>
#include <SdFat.h>
#include "timer.h"
#include "wave.h"
#include "ADAU7118.h"
#include "soc/rtc_wdt.h"
#include <FreeRTOSConfig.h>

#define ADXL345_I2CADDR 0x53 // 0x1D if SDO = HIGH

ADXL345_WE myAcc = ADXL345_WE(ADXL345_I2CADDR);
SFE_MMC5983MA myMag;

MyI2S mi;
SdFs sd;      // sd卡
FsFile fileIMU;
FsFile fileI2S;

const char fileIMUname[] = "/sensor.txt";
const int record_time = 90;  // second
const char fileI2Sname[] = "/iis.wav";

xyzFloat accRaw;
uint32_t magXYZ[3];

const uint32_t waveDataSize = record_time * 352800; //32bit, Stereo, 2 channels
//onst uint32_t waveDataSize = record_time * 264600; //24bit, Stereo, 2 channels
//const uint32_t waveDataSize = record_time * 176400; //16bit, Stereo, 2 channels
//const uint32_t waveDataSize = record_time * 88200; //16bit, Mono, 1 channels
int32_t communicationData[1024];     //单次接收缓冲区, 32bit ,size = 4K
char partWavData[4096];
volatile bool i2sFlag = 0;
uint32_t recordTime = 0;

void ADXL345Init();
void MMC5983MAInit();
void SDInit();
void iisInit();
void hardwareInit();

#endif