#include "gpiocregisters.hpp" //for GPIOC
#include "rccregisters.hpp"   //for RCC

std::uint32_t SystemCoreClock = 16'000'000U;

extern "C" {
int __low_level_init(void)
{
  //Switch on external 16 MHz oscillator
  RCC::CR::HSION::On::Set();
  while (RCC::CR::HSIRDY::NotReady::IsSet())
  {

  }
  //Switch system clock on external oscillator
  RCC::CFGR::SW::Hsi::Set();
  while (!RCC::CFGR::SWS::Hsi::IsSet())
  {

  }
  
  RCC::APB2ENR::SYSCFGEN::Enable::Set(); 

  return 1;
}
}


int main()
{
  RCC::AHB1ENR::GPIOCEN::Enable::Set() ;
  GPIOC::MODER::MODER5::Output::Set() ;
  GPIOC::ODR::ODR5::Enable::Set() ;
  GPIOC::ODR::ODR5::Disable::Set() ;
  return 0 ;
}
