#include "rccregisters.hpp"
#include "gpiocregisters.hpp"
#include <iostream>

int Test(int value, int value1, int value2, int value3, int value4, int value5)
{
  std::cout << value << " "  << std::endl;
  return value ;
}

int main()
{
  RCC::AHB1ENR::GPIOCEN::Enable::Set();
  GPIOC::MODER::MODER5::Output::Set();
  
  while(1)
  {
    GPIOC::BSRR::B55::High::Write();
    for(int i = 0; i < 100'000; i++)
    {
    }
    
    GPIOC::BSRR::B55::Low::Write();
    for(int i = 0; i < 100'000; i++)
    {
    }
  }
  return 1 ;
}
