#pragma once 
#include <cstdint>
#include "gpiocregisters.hpp"
#include "gpioaregisters.hpp"

template<typename Reg>
class Port
{
public: 
  void Toggle(uint8_t num)
  {
    ConfigurePorts();
    Reg::ODR::Toggle(1U << num);
  }
  
  bool IsPressed()
  {
    ConfigurePorts();
    return Reg::IDR::IDR13::Low::IsSet();
  }
  
private: 
  uint8_t num; 
  
  void ConfigurePorts()
  {
    RCC::AHB1ENR::GPIOCEN::Enable::Set();
    RCC::AHB1ENR::GPIOAEN::Enable::Set();
    GPIOC::MODER::MODER13::Input::Set();
    GPIOC::MODER::MODER5::Output::Set();
    GPIOC::MODER::MODER8::Output::Set();
    GPIOC::MODER::MODER9::Output::Set();
    GPIOA::MODER::MODER5::Output::Set();
  }
};