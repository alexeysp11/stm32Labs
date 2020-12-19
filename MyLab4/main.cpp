#include "rccregisters.hpp"
#include "gpiocregisters.hpp"
#include "gpioaregisters.hpp"
#include "tim2registers.hpp"

auto delay_100ms()
{
  TIM2::CR1::URS::OverflowEvent::Set();
  
  TIM2::PSC::Set(8000U);
  TIM2::ARR::Write(100U);
  TIM2::CNT::Write(0U);
  
  TIM2::SR::UIF::NoInterruptPending::Set();

  TIM2::CR1::CEN::Enable::Set();
  while(TIM2::SR::UIF::InterruptPending::IsSet()); 
  TIM2::CR1::CEN::Disable::Set();

  TIM2::SR::UIF::NoInterruptPending::Set();
}

int main()
{
  const unsigned int ButPeriod = 100U; 
  unsigned int LedsPeriod = 500U;       // Initial period of LED blinking
  unsigned int counter = 0;             // Counts how much ms past since last LEDs toggling
  bool isCurrentlyOn = 0;
  
  RCC::CR::HSEON::On::Set();
  while(!RCC::CR::HSERDY::Ready::IsSet());

  RCC::CFGR::SW::Hse::Set();
  while(!RCC::CFGR::SWS::Hse::IsSet());
  
  RCC::APB1ENR::TIM2EN::Enable::Set();
  
  RCC::AHB1ENR::GPIOCEN::Enable::Set();
  RCC::AHB1ENR::GPIOAEN::Enable::Set();
  GPIOC::MODER::MODER13::Input::Set();
  GPIOC::MODER::MODER5::Output::Set();
  GPIOA::MODER::MODER5::Output::Set();
  GPIOC::MODER::MODER9::Output::Set();
  GPIOC::MODER::MODER8::Output::Set();

  while(1)
  {
    delay_100ms();
    
    counter += ButPeriod;

    if(GPIOC::IDR::IDR13::Low::IsSet())
    {
      LedsPeriod += ButPeriod;
      counter = 0U;
    }
    
    if(counter >= LedsPeriod)
    {
      if(!isCurrentlyOn)
      {
        GPIOC::BSRR::BS8::High::Write();
        GPIOC::BSRR::BS9::High::Write();
        GPIOC::BSRR::BS5::High::Write();
        GPIOA::BSRR::BS5::High::Write();
        isCurrentlyOn = 1;
      }
      else
      {
        GPIOC::BSRR::BR9::Low::Write();
        GPIOC::BSRR::BR8::Low::Write();
        GPIOC::BSRR::BR5::Low::Write();
        GPIOA::BSRR::BR5::Low::Write();
        isCurrentlyOn = 0;
      }
      
      counter = 0;
    }
  }
  
  return 1;
}