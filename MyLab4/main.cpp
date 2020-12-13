// #include <iostream>
#include "rccregisters.hpp"
#include "button.hpp"

extern "C"
{
  int __low_level_init(void)
  {
    RCC::CR::HSEON::On::Set();
    while(!RCC::CR::HSERDY::Ready::IsSet());

    RCC::CFGR::SW::Hse::Set();
    while(!RCC::CFGR::SWS::Hse::IsSet());
    
    RCC::CR::HSION::Off::Set();

    RCC::PLLCFGR::PLLSRC::HseSource::Set();

    RCC::PLLCFGR::PLLM0::Set(4U);
    RCC::PLLCFGR::PLLN0::Set(50U);
    RCC::PLLCFGR::PLLP0::Pllp6::Set();

    RCC::CR::PLLON::On::Set();

    while(RCC::CR::PLLRDY::Unclocked::IsSet());

    RCC::CFGR::SW::Pll::Set();
    while(!RCC::CFGR::SWS::Pll::IsSet());
    
    return 1; 
  }
}

int main()
{
  Button<GPIOC> button; 
  
  while(1)
  {
    button.ReactOnPushing();
  }

  return 0 ;
}