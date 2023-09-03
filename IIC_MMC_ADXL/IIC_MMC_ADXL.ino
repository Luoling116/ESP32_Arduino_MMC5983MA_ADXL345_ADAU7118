#include "config.h"

TaskHandle_t handleIMU;

void setup(){
  hardwareInit();
  
  Serial.println("all hardawre init complete");

  //SD.remove(filename);
  //file = SD.open(filename, O_WRITE|O_CREAT);
  IMUfile = SD.open(filename, FILE_WRITE, true);
  if(!IMUfile){
    Serial.println("crate file error");
    return;
  }
  delay(2000);
  Serial.println("Sersor data recording...");
  IMUfile.println(millis());
  xTaskCreatePinnedToCore(taskIMU, "imu", 2048, NULL, 15, &handleIMU, 1);
  //xTaskCreate(taskIMU, "imu", 4096, NULL, 15, &handleIMU);

}

void loop() {
  if(!server_on){
    if(digitalRead(key_0) == LOW){
    //if(Serial.available() > 0){
      vTaskDelete(handleIMU);
      IMUfile.println(millis());
      Serial.println("task delete success.");
      
      IMUfile.close();
      Serial.println("Recording Complete.");
      delay(1000);

      Serial.println("WebFileServer start!");
      FileServerSetup();
      server_on = true;
    }
  }
  else{
    server.handleClient(); //Listen for client connections
  }
}

void taskIMU(void* param){
  while(1){
    if(xSemaphoreTake(timer0Semaphore, 0) == pdTRUE){

    accRaw = myAcc.getRawValues();
    myMag.getMeasurementXYZ(&magXYZ[0], &magXYZ[1], &magXYZ[2]);

    IMUfile.print(accRaw.x);IMUfile.print(",");
    IMUfile.print(accRaw.y);IMUfile.print(",");
    IMUfile.print(accRaw.z);IMUfile.print(",");
    IMUfile.print(magXYZ[0]);IMUfile.print(",");
    IMUfile.print(magXYZ[1]);IMUfile.print(",");
    IMUfile.println(magXYZ[2]);
    }

  if(xSemaphoreTake(timer1Semaphore, 0) == pdTRUE){
    portENTER_CRITICAL(&timerMux1);
    auto c1 = count1;
    auto t1 = time1;
    portEXIT_CRITICAL(&timerMux1);

    Serial.print(" timer1 is triggered. count: ");Serial.print(c1);
    Serial.print(". time: ");Serial.println(t1);
    }

  vTaskDelay(1);
  }
}