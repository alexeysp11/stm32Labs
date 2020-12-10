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

  RCC::AHB1ENR::GPIOCEN::Enable::Set();
  GPIOC::MODER::MODER5::Output::Set();
  
  while(1)
  {
    for(int i = 0; i < 1'000'000; i++);
    GPIOC::ODR::ODR5::High::Set();
    
    for(int i = 0; i < 1'000'000; i++);
    GPIOC::ODR::ODR5::Low::Set();
  }
  return 1 ;
}
