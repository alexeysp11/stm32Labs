// File Adc.hpp contains definition of IAdc interface and Adc class. 

#ifndef _STM32LABS_ADC_H_
#define _STM32LABS_ADC_H_

#include <cstdint>

class IAdc 
{
public: 
  virtual ~IAdc() = default; 
  virtual uint8_t Convert() = 0;
  virtual float GetVoltageFromDR() = 0;
  virtual std::uint32_t GetTempFromDR() = 0; 
};

class Adc: public IAdc
{
public: 
  Adc() = default; 
  uint8_t Convert();
  float GetVoltageFromDR();
  std::uint32_t GetTempFromDR(); 
};

#endif