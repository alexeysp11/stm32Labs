#include "Port.hpp"
#include "ChristmasTree.hpp"
#include "Timer.hpp"
#include "Button.hpp"

#include "gpiocregisters.hpp" //for GPIOC
#include "gpioaregisters.hpp" //for GPIOA
#include "rccregisters.hpp"   //for RCC
#include "tim2registers.hpp"   //for SPI2
#include "nvicregisters.hpp"  //for NVIC

extern "C"
{
  int __low_level_init(void)
  {
    
    //Switch on clock on PortA and PortC,
    RCC::AHB1ENRPack<
      RCC::AHB1ENR::GPIOCEN::Enable,
      RCC::AHB1ENR::GPIOAEN::Enable
      >::Set() ;
    
    RCC::APB1ENRPack<
      RCC::APB1ENR::TIM2EN::Enable,  
      >::Set() ;
    
    // LED1 on PortA.5, set PortA.5 as output
    GPIOA::MODER::MODER5::Output::Set() ;
        
    
    // LED2 on PortC.9, LED3 on PortC.8, LED4 on PortC.5 so set PortC.5,8,9 as output
    GPIOC::MODERPack<
      GPIOC::MODER::MODER5::Output,
      GPIOC::MODER::MODER8::Output,
      GPIOC::MODER::MODER9::Output
    >::Set() ;
        
    
     NVIC::ISER0::Write(1 << 28) ;
     TIM2::PSC::Write(8000) ;
     TIM2::ARR::Write(1000) ;
     TIM2::DIER::UIE::Enable::Set() ;
     TIM2::SR::UIF::NoUpdate::Set();
     TIM2::CNT::Write(0);
     TIM2::CR1::CEN::Enable::Set() ; 
    return 1;
  }
}

IButton* button = new Button(13, portC);
ChristmasTree ct(button);

int main()
{
  ct.Run(); 
  
  ct.~ChristmasTree(); 
  button->~IButton(); 
  
  return 0;
}