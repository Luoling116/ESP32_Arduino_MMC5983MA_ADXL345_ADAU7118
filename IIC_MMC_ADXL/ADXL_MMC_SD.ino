#include "config.h"

void hardwareInit(){
  Wire.begin();
  Serial.begin(115200);
  delay(1000);
  ADXL345Init();
  MMC5983MAInit();
  SDInit();
  timerInit();
  pinMode(key_0, INPUT_PULLUP);
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
}

void ADXL345Init(){
  if(!myAcc.init()){
    Serial.println("ADXL345 not connected!");
    while (true)
            ;
  }
  
  Serial.println("ADXL345 connected");
  /* Choose the data rate         Hz
      ADXL345_DATA_RATE_3200    3200
      ADXL345_DATA_RATE_1600    1600
      ADXL345_DATA_RATE_800      800
      ADXL345_DATA_RATE_400      400
      ADXL345_DATA_RATE_200      200
      ADXL345_DATA_RATE_100      100
      ADXL345_DATA_RATE_50        50
      ADXL345_DATA_RATE_25        25
      ADXL345_DATA_RATE_12_5      12.5  
      ADXL345_DATA_RATE_6_25       6.25
      ADXL345_DATA_RATE_3_13       3.13
      ADXL345_DATA_RATE_1_56       1.56
      ADXL345_DATA_RATE_0_78       0.78
      ADXL345_DATA_RATE_0_39       0.39
      ADXL345_DATA_RATE_0_20       0.20
      ADXL345_DATA_RATE_0_10       0.10
  */
  myAcc.setDataRate(ADXL345_DATA_RATE_800);
  Serial.print("ADXL345 Data rate: ");
  Serial.print(myAcc.getDataRateAsString());

  /* In full resolution the size of the raw values depend on the range:
      2g = 10 bit; 4g = 11 bit; 8g = 12 bit; 16g =13 bit;
      uncomment to change to 10 bit for all ranges. 
  */
    // myAcc.setFullRes(false);

  /* Choose the measurement range
      ADXL345_RANGE_16G    16g     
      ADXL345_RANGE_8G      8g     
      ADXL345_RANGE_4G      4g   
      ADXL345_RANGE_2G      2g
  */ 

  myAcc.setRange(ADXL345_RANGE_4G);
  Serial.print("  /  g-Range: ");
  Serial.println(myAcc.getRangeAsString());

  /* Uncomment to enable Low Power Mode. It saves power but slightly
      increases noise. LowPower only affetcs Data Rates 12.5 Hz to 400 Hz.
  */
  // myAcc.setLowPower(true);
}

void MMC5983MAInit(){
  if (myMag.begin() == false)
    {
        Serial.println("MMC5983MA did not respond - check your wiring. Freezing.");
        while (true)
            ;
    }
  
  myMag.softReset();

  Serial.println("MMC5983MA connected");

  myMag.setFilterBandwidth(800);
}

void SDInit(){
  //if(!sd.begin(SdSpiConfig(5, DEDICATED_SPI, 18000000))) //会造成互斥锁832错误，可见https://github.com/greiman/SdFat/issues/349
  //if(!sd.begin(SdSpiConfig(5, SHARED_SPI, 18000000)))

  //using SD.h instead of FatFS.h
  //SPIClass spi = SPIClass(HSPI);
  //spi.begin(18 /* SCK */, 19 /* MISO */, 23 /* MOSI */, 5 /* SS */);
  //if(!SD.begin(5, spi, 18000000))
  //if(!SD.begin())
  if(!SD.begin(5, SPI, 30000000)) //30MHz
  {
    Serial.println("init sd card error");
    Serial.println("Please check the setting of SD card");
    while(true);
  }
}