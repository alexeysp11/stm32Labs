#pragma once 
#include <cstdint>
#include "port.hpp"

template<typename Reg, uint8_t numPort>
class LED
{
public:
  void Toggle()
  {
    Port<Reg> port;
    port.Toggle(numPort); 
  }
};