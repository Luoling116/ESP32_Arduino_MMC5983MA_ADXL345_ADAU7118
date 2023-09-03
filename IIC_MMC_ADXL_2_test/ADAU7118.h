#ifndef ADAU7118_H_
#define ADAU7118_H_

#include <Wire.h>
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#define SAMPLE_RATE (44100)

/* 设备地址 */
//#define ADAU7118Address		0x2E
#define ADAU7118Address		0x17

/* 寄存器地址 */
#define ADAU7118_REG_VENDOR_ID		0x00
#define ADAU7118_REG_DEVICE_ID1		0x01
#define ADAU7118_REG_DEVICE_ID2		0x02
#define ADAU7118_REG_REVISION_ID	0x03
#define ADAU7118_REG_ENABLES		0x04
#define ADAU7118_REG_DEC_RATIO_CLK_MAP	0x05
#define ADAU7118_REG_HPF_CONTROL	0x06
#define ADAU7118_REG_SPT_CTRL1		0x07
#define ADAU7118_REG_SPT_CTRL2		0x08
#define ADAU7118_REG_SPT_CX(num)	(0x09 + (num))
#define ADAU7118_REG_DRIVE_STRENGTH	0x11
#define ADAU7118_REG_RESET		0x12

/* 设备ID默认值 */
#define Defult_VENDOR_ID		0x41
#define Defult_DEVICE_ID1		0x71	
#define Defult_DEVICE_ID2		0x18
#define Defult_REVISION_ID	0x00

/* ENABLES rigister config */
#define PDM_CLK1_ENABLE		0x20
#define PDM_CLK0_ENABLE 	0x10
#define CHAN_67_ENABLE 		0x08
#define CHAN_67_DISABLE 	0x00
#define CHAN_45_ENABLE 		0x04
#define CHAN_45_DISABLE 	0x00
#define CHAN_23_ENABLE 		0x02
#define CHAN_23_DISABLE 	0x00
#define CHAN_01_ENABLE 		0x01
#define CHAN_01_DISABLE 	0x00

/* DEC_RATIO_CLK_MAP rigister config */
#define PDM_DAT3_CLK0			0x00
#define PDM_DAT3_CLK1			0x80
#define PDM_DAT2_CLK0			0x00
#define PDM_DAT2_CLK1			0x40
#define PDM_DAT1_CLK0 		0x00
#define PDM_DAT1_CLK1 		0x20
#define PDM_DAT0_CLK0 		0x00
#define PDM_DAT0_CLK1 		0x10
#define DEC_RATIO_64 			0x00
#define DEC_RATIO_32 			0x01
#define DEC_RATIO_16 			0x02

/* HPF_CONTROL rigister config */
#define  HPF_Enable 		0x01
#define  HPF_Disable 		0x00
#define	 Defult_Cutoff_freq 0xD0

/* SPT_CTRL1 rigister config */
#define TRI_STATE_Enable		 0x40 
#define TRI_STATE_Disable		 0x00 
#define SPT_SLOT_WIDTH_32		 0x00    
#define SPT_SLOT_WIDTH_16		 0x10  
#define SPT_SLOT_WIDTH_24		 0x20
#define SPT_DATA_Left				 0x02
#define SPT_DATA_I2S_delay1  0x00
#define SPT_DATA_I2S_delay8  0x04
#define SPT_DATA_I2S_delay12 0x06
#define SPT_DATA_I2S_delay16 0x08
#define SPT_SAI_Stereo 			 0x00
#define SPT_SAI_TDM 			 	 0x01

/* SPT_CTRL2 rigister config */
#define LRCLK_POL_Normal		 0x00 
#define LRCLK_POL_Invert		 0x02 
#define BCLK_POL_Rising		 	 0x00    
#define BCLK_POL_Falling		 0x01  

#define RXBUFFER_SIZE  512							//缓存数组存储的数据帧数
#define SAVEBUFFER_SIZE  RXBUFFER_SIZE*6

class MyI2S
{
public:
  //以接收I2S的数据进行初始化
  bool InitInput(i2s_bits_per_sample_t BPS,
                 int bckPin,
                 int wsPin,
                 int dataInPin);

  //以接收ADC通道的数据进行初始化
  bool InitAdcInput(i2s_bits_per_sample_t BPS, adc1_channel_t adcChannel);

  size_t Read(char* data, int numData);

  size_t Write(char* data, int numData);

  void End();
};

/*
extern u16 I2s_buffer0[RXBUFFER_SIZE*4];
extern u16 I2s_buffer1[RXBUFFER_SIZE*4];
extern I2S_HandleTypeDef hi2s2;
extern u8  buf0_flag,buf1_flag;

void ADAU7118Init(void);
void My_I2S2_Init(void);
void I2S_DMA0ConvCplt(DMA_HandleTypeDef *hdma);
void I2S_DMA1ConvCplt(DMA_HandleTypeDef *hdma);
void I2S_DMAError2(DMA_HandleTypeDef *hdma);
void I2S_start(void);
void I2S_stop(void);
void Init_Sample(void);
void DMA_I2S2_Init(void);
int32_t Read_Buf_data(u16* buf, u16 i);
*/

void ADAU7118Init(void);

#endif