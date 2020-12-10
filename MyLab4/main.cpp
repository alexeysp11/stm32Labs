#include "rccregisters.hpp"
#include "gpiocregisters.hpp"
#include <iostream>
#include "gpioaregisters.hpp"

bool LEDsToggle(bool currentlyOn)
{
  if(!currentlyOn)
  {
    GPIOC::BSRR::BS5::High::Write();
    GPIOC::BSRR::BS9::High::Write();
    GPIOC::BSRR::BS8::High::Write();
    GPIOA::BSRR::BS5::High::Write();
    currentlyOn = 1; 
  }
  else
  {
    GPIOC::BSRR::BR5::Low::Write();
    GPIOC::BSRR::BR9::Low::Write();
    GPIOC::BSRR::BR8::Low::Write();
    GPIOA::BSRR::BR5::Low::Write();
    currentlyOn = 0; 
  }
  
  return currentlyOn; 
}

int main()
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

  RCC::AHB1ENR::GPIOCEN::Enable::Set();
  RCC::AHB1ENR::GPIOAEN::Enable::Set();
  GPIOC::MODER::MODER13::Input::Set();
  GPIOC::MODER::MODER5::Output::Set();
  GPIOC::MODER::MODER8::Output::Set();
  GPIOC::MODER::MODER9::Output::Set();
  GPIOA::MODER::MODER5::Output::Set();
  
  bool isPressed = 0;
  static bool currentlyOn = 0;
  while(1)
  {
    if(GPIOC::IDR::IDR13::Low::IsSet() && !isPressed)
    {
      isPressed = 1;
      currentlyOn = LEDsToggle(currentlyOn);
    }
    if(GPIOC::IDR::IDR13::High::IsSet())
      isPressed = 0;
	
  }

  return 1 ;
}