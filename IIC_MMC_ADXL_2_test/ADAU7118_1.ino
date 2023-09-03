#include "ADAU7118.h"

uint8_t deviceID = 0;

bool MyI2S::InitInput(i2s_bits_per_sample_t BPS,
                      int bckPin, //17
                      int wsPin,  //16
                      int dataInPin) //4
{
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = BPS,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0,
    .dma_buf_count = 20,
    .dma_buf_len = 500,
    .use_apll = false
  };

  i2s_pin_config_t pin_config;
  memset(&pin_config,0,sizeof(i2s_pin_config_t));
  pin_config.bck_io_num = bckPin;
  pin_config.ws_io_num = wsPin;
  pin_config.data_out_num = I2S_PIN_NO_CHANGE;
  pin_config.data_in_num = dataInPin;

  if(ESP_OK!=i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL))
  {
    Serial.println("install i2s driver failed");
    return false;
  }
  if(ESP_OK!=i2s_set_pin(I2S_NUM_0, &pin_config))
  {
    Serial.println("i2s set pin failed");
    return false;
  }
  return true;
}

bool MyI2S::InitAdcInput(i2s_bits_per_sample_t BPS, adc1_channel_t dataInPin){
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_ADC_BUILT_IN),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = BPS,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = 1000,
    .use_apll = false
  };

  if(ESP_OK!=i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL))
  {
    Serial.println("install i2s driver failed");
    return false;
  }
  i2s_set_pin(I2S_NUM_0, NULL);
  //i2s_set_adc_mode(ADC_UNIT_1, adcChannel);
  //adc1_config_channel_atten(adcChannel, ADC_ATTEN_DB_11);
  i2s_adc_enable(I2S_NUM_0);
  return true;
}

size_t MyI2S::Read(char* data, int numData){
  size_t recvSize;
  i2s_read(I2S_NUM_0, (void*)data, numData, &recvSize, portMAX_DELAY);
  return recvSize;
}

size_t MyI2S::Write(char* data, int numData){
  size_t sendSize;
  i2s_write(I2S_NUM_0, (void*)data, numData, &sendSize, portMAX_DELAY);
  return sendSize;
}

void MyI2S::End(){
  i2s_driver_uninstall(I2S_NUM_0);
}

void ADAU7118Init(void){
  while(deviceID != Defult_VENDOR_ID){
    deviceID = SingleRead(ADAU7118_REG_VENDOR_ID);
    Serial.print("ADAU Init success! ");
    Serial.print("deviceID is: ");
    Serial.println(deviceID);
    delay(500);
  }
  SingleWrite(ADAU7118_REG_ENABLES, CHAN_01_ENABLE | PDM_CLK0_ENABLE);
  SingleWrite(ADAU7118_REG_SPT_CTRL1,TRI_STATE_Enable|SPT_SLOT_WIDTH_32|SPT_DATA_I2S_delay1|SPT_SAI_Stereo);
}

void SingleWrite(uint8_t REGAddress, uint8_t REGDdata){
  Wire.beginTransmission(ADAU7118Address);
  Wire.write(REGAddress);
  Wire.write(REGDdata);
  Wire.endTransmission();
}

uint8_t SingleRead(uint8_t REGAddress){
  uint8_t REGValue = 0;
  Wire.beginTransmission(ADAU7118Address);
  Wire.write(REGAddress);
  Wire.endTransmission();
  Wire.requestFrom(ADAU7118Address, static_cast<uint8_t>(1));
  if(Wire.available()){
    REGValue = Wire.read();
  }
  return REGValue;
}