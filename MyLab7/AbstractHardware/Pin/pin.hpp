#pragma once

#include <cstdint> // for uint8_t

class IPin
{
  public: 
    uint8_t number; 
    IPort& port;
    void virtual Toggle(uint8_t num) = 0;
};

template<typename Reg>
class Pin
{
  public: 
    void Toggle(uint8_t num)
    {
      Reg::ODR::Toggle(1U << num);
    }
    
    bool Read(uint8_t num)
    {
      return Reg::IDR::num::Low::IsSet(); 
    }
};