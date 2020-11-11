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
  RCC::CR::HSEON::On::Set();
  while(!RCC::CR::HSERDY::Ready::IsSet())
  {
  }
 
  RCC::CFGR::SW::Hse::Set();
  
  while(!RCC::CFGR::SWS::Hse::IsSet())
  {
  }
  
  RCC::CR::HSION::Off::Set();
  
  //Подать тактирование на порт С
  //*reinterpret_cast<std::uint32_t*>(0x40023830) = 1U << 2U ; 
  volatile int t = 0;   
  RCC::AHB1ENR::GPIOCEN::Enable::Set();
  
  GPIOC::MODER::MODER5::Input::Set();
  
  for(;;)
  {
    for (int i= 0; i < 50000 ; i ++)
    {
    }
    
    GPIOC::ODR::ODR5::High::Set() ;
  
    for (int i= 0; i < 50000 ; i ++)
    {
    }
    GPIOC::ODR::ODR5::Low::Set() ;
  }
  return 1 ;
}
