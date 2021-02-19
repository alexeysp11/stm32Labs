#include "Adc.hpp"
#include "adc1registers.hpp"

Adc::Adc() 
{
}

uint8_t Adc::Convert()
{
  ADC1::CR2::SWSTART::Value1::Set();            // Start conversion. 
  while(ADC1::SR::EOC::Value0::IsSet());        // While conversion not complete.
  
  return 0; 
}

void Adc::Write()
{
}