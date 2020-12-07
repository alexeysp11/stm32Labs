//#include <cstdint>            //for int types such as uint32_t
#include "gpiocregisters.hpp" //for GPIOC
#include "gpioaregisters.hpp" //for GPIOA
#include "rccregisters.hpp"   //for RCC
#include "tim2registers.hpp"   //for SPI2
#include "nvicregisters.hpp"  //for NVIC
#include "LightEmittingDiodes.hpp"  // for LEDs

using namespace std;

extern "C"
{
  int __low_level_init(void)
  {
    RCC::AHB1ENR::GPIOCEN::Enable::Set();
    RCC::AHB1ENR::GPIOAEN::Enable::Set();
    GPIOC::MODER::MODER13::Input::Set();
    GPIOC::MODER::MODER5::Output::Set();
    GPIOC::MODER::MODER8::Output::Set();
    GPIOC::MODER::MODER9::Output::Set();
    GPIOA::MODER::MODER5::Output::Set();
    
    RCC::APB1ENR::TIM2EN::Enable::Set();
    TIM2::PSC::Write(16'000); 
    
    TIM2::ARR::Write(1000U);
    TIM2::CNT::Write(0U);
    
    NVIC::ISER0::Write(1U << 28U);
    TIM2::DIER::UIE::Enable::Set();
    
    return 1;
  }
}
                     
int main()
{
  TIM2::CR1::CEN::Enable::Set();
  
  while(1)
  {
    LightEmittingDiodes::ReactOnButton();
  }
  
  return 0;
}

