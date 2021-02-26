// File Adc.cpp contains implementation of class Adc.

#include "Adc.hpp"
#include "adc1registers.hpp"

#include <cstdint>

/*
* Make conversion using ADC. 
*/
uint8_t Adc::Convert()
{
  ADC1::CR2::SWSTART::Value1::Set();            // Start conversion. 
  while(ADC1::SR::EOC::Value0::IsSet());        // While conversion not complete.
  
  return 0; 
}

/*
* Gets voltage to the DR register. 
* 
* @returns floating point number. 
*/
float Adc::GetVoltageFromDR()
{
  return ADC1::DR::DATA::Get();
}

/*
* Gets voltage to the DR register. 
* 
* @returns unsigned int 32 bit. 
*/
std::uint32_t Adc::GetTempFromDR()
{
  return ADC1::DR::DATA::Get();
}