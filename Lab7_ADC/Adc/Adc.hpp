#pragma once

#include <cstdint>

class IAdc 
{
public: 
  virtual ~IAdc() {}
  virtual uint8_t Convert() = 0;

private: 
  virtual void Write() = 0;
};

class Adc: public IAdc
{
public: 
  Adc(); 
  uint8_t Convert();

private: 
  void Write();
};