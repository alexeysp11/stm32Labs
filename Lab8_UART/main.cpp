// TODO: add description and comment all methods and classes. 

#include "uartdriver.hpp"
#include "timers.hpp"
#include "timersdriver.hpp"

#include "rccregisters.hpp"
#include "rccfieldvalues.hpp"
#include "gpiocregisters.hpp"
#include "gpioaregisters.hpp"
#include "usart2registers.hpp"          // for UART2.

// Set UART data rate equal to 9600 bps. 
constexpr std::uint32_t UartSpeed9600 = std::uint32_t(8000000U / 9600U);

extern "C"
{
  int __low_level_init(void)
  {
    RCC::CR::HSEON::On::Set();
    while (!RCC::CR::HSERDY::Ready::IsSet());
    RCC::CFGR::SW::Hse::Set();

    while (!RCC::CFGR::SWS::Hse::IsSet());
    RCC::CR::HSION::Off::Set();

    RCC::AHB1ENR::GPIOAEN::Enable::Set();       // Enable GPIOA port. 
    
    RCC::APB1ENR::USART2EN::Enable::Set();      // Connect USART to clocking source. 
    
    // USART ports configuration. 
    GPIOA::MODER::MODER2::Alternate::Set();     // Set port as alternative for Uart2 TX.
    GPIOA::MODER::MODER3::Alternate::Set();     // Set port as alternative for Uart2 RX.
    GPIOA::AFRL::AFRL2::Af7::Set();             // Specify alternate mode Uart2 TX. 
    GPIOA::AFRL::AFRL3::Af7::Set();             // Specify alternate mode Uart2 RX. 
    GPIOA::OTYPER::OT3::OutputPushPull::Set();  // Output push-pull (reset state). 
    GPIOA::PUPDR::PUPDR3::PullUp::Set();        // Port x configuration bits: these bits are written by software to configure the I/O pull-up or pull-down. 
        
    // USART data format configuration. 
    USART2::CR1::M::Value0::Set();              // 1 Start bit, 8 Data bits, n Stop bit
    USART2::CR1::OVER8::Value0::Set();          // Oversampling by 16
    //USART2::CR1::PS::Value1::Set();             // Odd parity. 
    //USART2::CR1::PCE::Value1::Set();            // Parity control enabled.
    USART2::CR2::STOP::Value0::Set();           // 1 Stop bits: these bits are used for programming the stop bits.
    USART2::CR2::LINEN::Value1::Set();          // LIN mode enabled: This bit is set and cleared by software.
    USART2::BRR::Write(UartSpeed9600);          // Set baud rate for USART. 
        
    return 1;
  }
}

int main()
{
  constexpr char *str = "Hello world!";         // Message to be send. 

  UartDriver uartdriver; 
  TimersDriver timersdriver; 
  timersdriver.Config(8000U, 1000U, 0U); 
  
  while (true)
  {
    uartdriver.SendMessage(str, strlen(str)); 
    timersdriver.Sleep(); 
  }
  
  return 0;
}