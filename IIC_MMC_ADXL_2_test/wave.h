#pragma once

typedef struct WAV_HEADER_S
{
	char   			    riffType[4]{'R','I','F','F'};	    //4byte,资源交换文件标志:RIFF	
	unsigned int   	riffSize;		                      //4byte,从下个地址到文件结尾的总字节数 = 文件总大小-8	
	char   			    waveType[4]{'W','A','V','E'};	    //4byte,wav文件标志:WAVE	
	char   			    formatType[4]{'f','m','t',' '};	  //4byte,波形文件标志:fmt(最后一位空格符)
	unsigned int	  formatSize{16};		                //4byte,fmt chunk块的(compressionCode,numChannels,sampleRate,bytesPerSecond,blockAlign,bitsPerSample)大小，不包含自己
	unsigned short	compressionCode{1};               //2byte,格式种类(1-线性pcm-WAVE_FORMAT_PCM,WAVEFORMAT_ADPCM)
	unsigned short 	numChannels;	                    //2byte,通道数
	unsigned int   	sampleRate;		                    //4byte,采样率
	unsigned int   	bytesPerSecond;	                  //4byte,每秒传输速率 = SampleRate * NumChannels * BitsPerSample/8
	unsigned short 	blockAlign;		                    //2byte,数据块的对齐，即DATA数据块长度 = NumChannels * BitsPerSample/8
	unsigned short 	bitsPerSample;	                  //2byte,採样精度-PCM位宽
	char   			    dataType[4]{'d','a','t','a'};	    //4byte,数据标志:data
	unsigned int   	dataSize;	       	                //4byte,从下个地址到文件结尾的总字节数。即除了wav header以外的pcm data length = 文件大小 - 44
}WAV_HEADER;

WAV_HEADER CreateWaveHeader(int numChannels = 1,                    //声道数
                            unsigned int sampleRate = 44100,        //采样率
                            unsigned short bitsPerSample = 16);     //采样位宽