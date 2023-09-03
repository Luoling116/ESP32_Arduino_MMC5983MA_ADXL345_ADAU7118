#ifndef CONFIG_H_
#define CONFIG_H_

#include <Wire.h>
#include <ADXL345_WE.h>
#include <SparkFun_MMC5983MA_Arduino_Library.h>
#include <SPI.h>
//#include <SdFat.h>
#include <SD.h>
#include "timer.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "WebFileServer.h"

#define ADXL345_I2CADDR 0x53 // 0x1D if SDO = HIGH
//#define ADXL345_I2CADDR 0x1D // 0x1D if SDO = HIGH

ADXL345_WE myAcc = ADXL345_WE(ADXL345_I2CADDR);
SFE_MMC5983MA myMag;

//SdFs sd;      // sd卡
//FsFile file;
File IMUfile;

int key_0 = 13;
const char filename[] = "/sensor.txt";
xyzFloat accRaw;
uint32_t magXYZ[3];

void ADXL345Init();
void MMC5983MAInit();
void SDInit();
void hardwareInit();

#endif