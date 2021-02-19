#pragma once

#include "Adc.hpp"

#include "adc1registers.hpp"

#include <cstdint>
#include <iostream>

class IVoltage
{
public: 
  virtual ~IVoltage() {}
  virtual std::uint8_t GetNumOfLeds() = 0; 

private: 
  virtual void InvokeAdcConversions() = 0;
};

class Voltage: public IVoltage
{
public: 
  Voltage(); 
  std::uint8_t GetNumOfLeds(); 

private: 
  void InvokeAdcConversions(); 
  
  float V25 = 0.76f;
  float Avg_Slope = 0.0025f;
  float Temperature = 0.0f;
  
  std::int8_t minTemp = - 40; 
  std::int8_t maxTemp = 125; 
};