#include "rccregisters.hpp"
#include "gpiocregisters.hpp"
#include <iostream>
#include "stkregisters.hpp"

constexpr std::uint32_t CpuClock = 16'000'000U; 

int main()
{  
  STK::LOAD::Write(CpuClock/100'000U - 1U);
  STK::VAL::Write(0U);
  STK::CTRL::CLKSOURCE::CpuClock::Set();
  
  RCC::AHB1ENR::GPIOCEN::Enable::Set();
  
  GPIOC::MODER::MODER5::Output::Set();
  
  while(1)
  {
    STK::VAL::Write(0U);
    STK::CTRL::ENABLE::Enable::Set();
    while()
    {
    }
    
    GPIOC::BSRR::BS5::High::Write();
    GPIOC::BSRR::BR5::Low::Write();
  }
  return 1 ;
}
