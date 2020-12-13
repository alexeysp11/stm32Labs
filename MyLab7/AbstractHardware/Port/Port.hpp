#pragma once

#include <cstdint> // for uint8_t

class IPort
{
  public: 
    void virtual Toggle(uint8_t num) = 0;
};

template<typename Reg>
class Port : IPort
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