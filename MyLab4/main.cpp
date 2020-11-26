#include "rccregisters.hpp"
#include "gpiocregisters.hpp"
#include "gpioaregisters.hpp"
#include <iostream>
#include "tim2registers.hpp"

constexpr std::uint32_t CpuClock = 8'000'000U;

auto delay_ms(std::uint32_t period)
{
  // Update request source: 
  // counter owerflow can generate an update interrupt
  TIM2::CR1::URS::OverflowEvent::Set();
  
  const std::uint32_t timerValue = (CpuClock * 1000U) * period - 1U;
  
  // Wirte desired value to TIM2_ARR
  TIM2::ARR::Write(timerValue);
  
  TIM2::SR::UIF::NoInterruptPending::Set();
  
  // Counter register
  TIM2::CNT::Write(0U);  
  
  // Enable counter
  TIM2::CR1::CEN::Enable::Set();
  while(TIM2::SR::UIF::InterruptPending::IsSet());
  
  TIM2::CR1::CEN::Disable::Set();
  
  // Update interrupt flag
  TIM2::SR::UIF::NoInterruptPending::Set();
}

int main()
{
  unsigned int ButPeriod = 100U;
  unsigned int LedsPeriod = 500U;
  unsigned int counter = 0;

  bool flag = false;
  
  // Enable external HSE clock and wait until it's stable
  RCC::CR::HSEON::On::Set();
  while(!RCC::CR::HSERDY::Ready::IsSet());
  
  // Select HSE oscillator as system clock source
  RCC::CFGR::SW::Hse::Set();
  while(!RCC::CFGR::SWS::Hse::IsSet());

  // Set required pins and registers
  RCC::APB1ENR::TIM2EN::Enable::Set();
  RCC::AHB1ENR::GPIOCEN::Enable::Set();
  RCC::AHB1ENR::GPIOAEN::Enable::Set();
  GPIOC::MODER::MODER13::Input::Set();
  GPIOC::MODER::MODER5::Output::Set();
  GPIOA::MODER::MODER5::Output::Set();
  GPIOC::MODER::MODER9::Output::Set();
  GPIOC::MODER::MODER8::Output::Set();
  
  // Use block diagrams to implement main logic of the program!
  while(1)
  {
    // Implement a delay using timer TIM2
    delay_ms(ButPeriod);
    
    // If user pushed a button 
    if(GPIOC::IDR::IDR13::Low::IsSet())
    {
      LedsPeriod += 100U;
      counter = 0;
    }
    counter = counter + ButPeriod;
    
    if(counter >= LedsPeriod)
    {
      if(!flag)
      {
        GPIOC::BSRR::BS8::High::Write();
        GPIOC::BSRR::BS9::High::Write();
        GPIOC::BSRR::BS5::High::Write();
        GPIOA::BSRR::BS5::High::Write();
        flag = true;
      }
      else
      {
        GPIOC::BSRR::BR9::Low::Write();
        GPIOC::BSRR::BR8::Low::Write();
        GPIOC::BSRR::BR5::Low::Write();
        GPIOA::BSRR::BR5::Low::Write();
        flag = false;
      }
      
      counter = 0;
    }
  }
  return 1;
}