#include "gpiocregisters.hpp" //for GPIOC
#include "rccregisters.hpp"   //for RCC

int main()
{
  RCC::AHB1ENR::GPIOCEN::Enable::Set() ;
  GPIOC::MODER::MODER5::Output::Set() ;
  GPIOC::ODR::ODR5::High::Set() ;
  GPIOC::ODR::ODR5::Low::Set() ;
  return 0 ;
}