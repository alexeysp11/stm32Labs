#include "TempMeasurement.hpp"

#include "rccregisters.hpp"
#include "gpiocregisters.hpp"
#include "gpioaregisters.hpp"
#include "adc1registers.hpp"
#include "adccommonregisters.hpp"

extern "C"
{
  int __low_level_init(void)
  {
    RCC::CR::HSEON::On::Set();
    while (!RCC::CR::HSERDY::Ready::IsSet());
    RCC::CFGR::SW::Hse::Set();

    while (!RCC::CFGR::SWS::Hse::IsSet());
    RCC::CR::HSION::Off::Set();
    
    // Configure ADC. 
    RCC::APB2ENR::ADC1EN::Enable::Set();
    ADC1::SQR3::SQ1::Value18::Set();            // Channel 18 (for temperature sensor). 
    ADC_Common::CCR::TSVREFE::Value1::Set();    // Temperature sensor and VREFINT channel enabled. 
    ADC1::CR1::RES::Value0::Set();              // 12-bit (15 ADCCLK cycles)
    ADC1::CR2::CONT::Value0::Set();             // Single conversion mode. 
    ADC1::CR2::EOCS::Value0::Set();             // The EOC bit is set at the end of each sequence of regular conversions. Overrun detection is enabled only if DMA=1.
    ADC1::SQR1::L::Value0::Set();               // 1 conversion. 
    ADC1::SMPR1::SMP18::Cycles84::Set();        // 84 cycles. 
    ADC1::CR2::ADON::Value1::Set();             // Enable ADC. 
    
    return 1;
  }
}

int main()
{
  TempMeasurement tm; 
  tm.Run();
  
  return 0;
}