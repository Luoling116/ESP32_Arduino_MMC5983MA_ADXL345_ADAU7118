#include "wave.h"

WAV_HEADER CreateWaveHeader(int numChannels,                    //声道数
                            unsigned int sampleRate,            //采样率
                            unsigned short bitsPerSample)       //采样位宽
{
  WAV_HEADER header;
  header.riffSize = 0;
  header.numChannels = numChannels;
  header.sampleRate = sampleRate;
  header.bitsPerSample = bitsPerSample;
  header.bytesPerSecond = sampleRate * numChannels /8 * bitsPerSample;
  header.blockAlign = numChannels * bitsPerSample/8;
  header.dataSize = 0;
  return header;
}