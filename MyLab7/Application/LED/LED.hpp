#pragma once
#include "Port.hpp"

class Led
{
public:
  Led(uint8_t num, IPortSet& aPin);
  void Toggle();

private:
  uint8_t number; 
  IPortSet& port;
};