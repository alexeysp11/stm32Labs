// File port.h contains definition of IPortSet interface and class Port. 

#ifndef _STM32LABS_PORT_H_
#define _STM32LABS_PORT_H_

#include "gpiocregisters.hpp" 
#include "gpioaregisters.hpp" 
#include "rccregisters.hpp" 

#include <cstdint>
#include <cassert>

class IPortSet
{
public:
  virtual void SetHigh(std::uint8_t num) = 0;
  virtual void SetLow(std::uint8_t num) = 0;
  virtual void Toggle(std::uint8_t num) = 0;
};

template <typename Reg>
class Port: public IPortSet
{
public:
  void SetHigh(std::uint8_t num) override
  {
    Reg::ODR::Write(1 << num); 
  }
  
  void SetLow(std::uint8_t num) override
  {
    Reg::ODR::Write(1 << num); 
  }
  
  void Toggle(std::uint8_t num) override
  {
     assert (num < 16);
     Reg::ODR::Toggle(1 << num);
   }
};

#endif