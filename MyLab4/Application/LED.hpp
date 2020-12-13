#pragma once 
#include "gpiocregisters.hpp"
#include "gpioaregisters.hpp"
#include "port.hpp"

template<typename Reg>
class LED
{
  bool Toggle(numPort)
  {
    port.Toggle(numPort);
  }
  
  private: 
    uint8_t numPort; 
    Port& port; 
    
    void ConfigurePins(void)
    {
      RCC::AHB1ENR::GPIOCEN::Enable::Set();
      RCC::AHB1ENR::GPIOAEN::Enable::Set();
      GPIOC::MODER::MODER5::Output::Set();
      GPIOC::MODER::MODER8::Output::Set();
      GPIOC::MODER::MODER9::Output::Set();
      GPIOA::MODER::MODER5::Output::Set();
    }
};