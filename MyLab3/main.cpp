#include "rccregisters.hpp"
#include "gpiocregisters.hpp"
#include <iostream>
#include <ctime>

void sleep(float seconds)
{
    clock_t startClock = clock();
    float secondsAhead = seconds * CLOCKS_PER_SEC;
    
    // do nothing until the elapsed time has passed.
    while(clock() < startClock+secondsAhead);
    return;
}

int main()
{  
  RCC::CR::HSEON::On::Set();
  while(!RCC::CR::HSERDY::Ready::IsSet());
 
  RCC::CFGR::SW::Hse::Set();
  while(!RCC::CFGR::SWS::Hse::IsSet());
  
  RCC::CR::HSION::Off::Set();
  RCC::PLLCFGR::PLLSRC::HseSource::Set();
  
  // Set VCO equal to 2 MHz => HSE / 4 = 8'000'000 / 4 
  RCC::PLLCFGR::PLLM0::Set(4U);
  
  // Set VCC Output equal to 128 MHz => VCO * 64 = 2'000'000 * 64
  RCC::PLLCFGR::PLLN0::Set(64U);
  
  // Set PLL Output equal to 32 Mhz => VCC / 4 = 128'000'000 / 4
  RCC::PLLCFGR::PLLP0::Pllp4::Set();
  
  RCC::CR::PLLON::On::Set();
  while(RCC::CR::PLLRDY::Unclocked::IsSet());
  
  RCC::CFGR::SW::Pll::Set();
  while(!RCC::CFGR::SWS::Pll::IsSet());
  
  RCC::AHB1ENR::GPIOCEN::Enable::Set();
  GPIOC::MODER::MODER5::Output::Set();
  
  while(1)
  {
    sleep(1.0);
    GPIOC::ODR::ODR5::High::Set();
    
    sleep(1.0);
    GPIOC::ODR::ODR5::Low::Set();
  }
  return 1 ;
}
