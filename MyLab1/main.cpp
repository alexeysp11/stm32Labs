#include "gpiocregisters.hpp" //for GPIOC
#include "rccregisters.hpp"   //for RCC

int main()
{
  RCC::AHB1ENR::GPIOCEN::Enable::Set() ;
  GPIOC::MODER::MODER5::Output::Set() ;
  GPIOC::ODR::ODR5::Enable::Set() ;
  GPIOC::ODR::ODR5::Disable::Set() ;
  return 0 ;
}