#pragma once

#include "gpiocregisters.hpp" 
#include "gpioaregisters.hpp" 
#include "rccregisters.hpp" 

#include <cstdint>
#include <cassert>

class IPortSet
{
public:
  virtual bool IsSet(std::uint8_t num) = 0;
  virtual void SetHigh(std::uint8_t num) = 0;
  virtual void SetLow(std::uint8_t num) = 0;
  virtual void Toggle(std::uint8_t num) = 0;
};

class IPortMeasure
{
public:
  virtual std::uint8_t Measure() = 0;
};

template <typename Reg>
class Port: public IPortSet, public IPortMeasure
{
public:
  bool IsSet(std::uint8_t num) override
  {
    return (Reg::IDR::Get()&(1<<num)) != 0;
  }
  
  void SetHigh(std::uint8_t num)
  {
    Reg::ODR::Write(1 << num); 
  }
  
  void SetLow(std::uint8_t num)
  {
    Reg::ODR::Write(1 << num); 
  }
  
  void Toggle(std::uint8_t num) override
  {
     assert (num < 16);
     Reg::ODR::Toggle(1 << num);
   }

  std::uint8_t Measure() override
  {
     return Reg::IDR::Get();
  }
};