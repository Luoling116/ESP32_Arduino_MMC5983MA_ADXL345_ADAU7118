# ESP32_Arduino_MMC5983MA_ADXL345_ADAU7118_SD
Using esp32 to simultaneously collect IMU information and audio information based on Arduino IDE, and after signal acquisition the ESP32 will build a Web server where you can download file.  

> ADXL345: https://github.com/wollewald/ADXL345_WE

> MMC5983: https://github.com/sparkfun/SparkFun_MMC5983MA_Magnetometer_Arduino_Library

> WebFileServer: https://www.youtube.com/watch?v=zoYMU1tA3nI&t=218s

## IIC_MMC_ADXL Folder
ONLY using ADXL345 and MMC5983 to collect signals at 200Hz, and it works FINE.

## IIC_MMC_ADXL_2_test Folder
Using ADXL345 MMC5983 and ADAU7118, but there is always a conflict between them. It will be fixed in future.
