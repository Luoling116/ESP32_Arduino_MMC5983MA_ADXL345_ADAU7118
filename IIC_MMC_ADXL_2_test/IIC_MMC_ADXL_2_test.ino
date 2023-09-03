#include "config.h"

TaskHandle_t handleIMU = NULL;
TaskHandle_t handleADAU = NULL;
xSemaphoreHandle xMutex; //互斥锁

void setup(){
  hardwareInit();
  
  //创建IMU存储文件，/sensor.txt
  sd.remove(fileIMUname);
  fileIMU = sd.open(fileIMUname, O_WRITE|O_CREAT);
  if(!fileIMU){
    Serial.println("crate fileIMU error");
    return;
  }
  Serial.println("Create fileIMU complete");

  //创建麦克风存储文件，/iis.wav
  sd.remove(fileI2Sname);
  fileI2S = sd.open(fileI2Sname, O_WRITE|O_CREAT);
  if(!fileI2S){
    Serial.println("crate fileI2S error");
    return;
  }
  Serial.println("Create fileI2S complete");

  //麦克风wave文件头写入
  auto header = CreateWaveHeader(2, 44100, 32);
  header.riffSize = waveDataSize + 44 - 8;
  header.dataSize = waveDataSize;
  fileI2S.write(&header, 44);

  xMutex = xSemaphoreCreateMutex();
  delay(2000);
  Serial.println("Wait For Command");

  rtc_wdt_protect_off();    // 看门狗写保护关闭，关闭后可以喂狗

}

void loop() {
  //串口命令输入判断
  if(Serial.available() > 0){
    String command = Serial.readString();

    if(command == "start"){
      i2sFlag = 1;
      Serial.println("Record start");
      fileIMU.println(millis());
      xTaskCreatePinnedToCore(taskIMU, "imu", 8192, NULL, 15, &handleIMU, 0);
      xTaskCreatePinnedToCore(taskADAU, "adau", 20480, NULL, 15, &handleADAU, 1);
    }
      
    if(command == "stop"){
      i2sFlag = 0;

      vTaskDelete(handleIMU);
      fileIMU.println(millis());
      fileIMU.close();

      vTaskDelete(handleADAU);
      fileI2S.seekSet(40);
      recordTime *= 4096;
      fileI2S.write(&recordTime,4);
      Serial.print("Record time is: ");
      Serial.println(double(recordTime)/352800);
      fileI2S.close();
      Serial.println("Record finish");

      while(true);
    }
    
  }
}

void taskADAU(void* param){
  while(1){
    if(xSemaphoreTake(xMutex, portMAX_DELAY)){
      //while(recordTime < 31752000/4096){
      //rtc_wdt_feed();
      //int32_t* communicationData =(int32_t*) calloc(1024, sizeof(int32_t));
      auto sz = mi.Read((char*)communicationData, 1024); //原4096
      //mi.Read((char*)communicationData, 4096);
      char*p =(char*)(communicationData);
      for(int i=0;i<sz/4;i++)
      {
        communicationData[i] *= 20;  //提高声音
      }
      recordTime ++;
      fileI2S.write((const byte*)p, 1024);
      //fileI2S.flush();
      xSemaphoreGive(xMutex);
    }
  }
}

void taskIMU(void* param){
  while(1){
    if(xSemaphoreTake(xMutex, portMAX_DELAY)){  
      //定时器0，定时5ms，用于采集加速度计和磁力计数据
      if(xSemaphoreTake(timer0Semaphore, 0) == pdTRUE){
        //accRaw = myAcc.getRawValues();
        myMag.getMeasurementXYZ(&magXYZ[0], &magXYZ[1], &magXYZ[2]);

        //file.print(accRaw.x);file.print(",");
        //file.print(accRaw.y);file.print(",");
        //file.print(accRaw.z);file.print(",");
        fileIMU.print(magXYZ[0]);fileIMU.print(",");
        fileIMU.print(magXYZ[1]);fileIMU.print(",");
        fileIMU.println(magXYZ[2]);

        /*
        //Serial.print(accRaw.x);Serial.print(",");
        //Serial.print(accRaw.y);Serial.print(",");
        //Serial.print(accRaw.z);Serial.print(",");
        Serial.print(magXYZ[0]);Serial.print(",");
        Serial.print(magXYZ[1]);Serial.print(",");
        Serial.println(magXYZ[2]);
        */
      }

      if(xSemaphoreTake(timer1Semaphore, 0) == pdTRUE){
        portENTER_CRITICAL(&timerMux1);
        auto c1 = count1;
        auto t1 = time1;
        portEXIT_CRITICAL(&timerMux1);

        Serial.print(" timer1 is triggered. count: ");Serial.print(c1);
        Serial.print(". time: ");Serial.println(t1);
      }
    xSemaphoreGive(xMutex);
  }
  vTaskDelay(1);
  rtc_wdt_feed();
  }
}