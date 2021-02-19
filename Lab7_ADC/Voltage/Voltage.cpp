#include "Voltage.hpp"

Voltage::Voltage()
{
}

void Voltage::InvokeAdcConversions()
{
  IAdc* adc = new Adc();
  uint8_t result = adc->Convert();
  adc->~IAdc(); 
}

std::uint8_t Voltage::GetNumOfLeds()
{
  /*
  Note that supported temperature range of the ADC: –40 to 125 °C. 

  @returns number of LEDs to switch on. 
  */
  
  Voltage::InvokeAdcConversions();
  
  std::uint32_t data = ADC1::DR::Get(); 
  Temperature = ((((data*3.3f)/4096 - V25)/Avg_Slope) + 25.0f);
  
  std::cout << "Temperature: " <<  Temperature << std::endl;
  
  std::uint8_t tempStep = (maxTemp - minTemp) / 4;      // By default there's only 4 LEDs. 
  std::uint8_t numOfLeds = 0; 
  
  /*
  * If temperature is less than max temperature and more than min temperature, 
  * you can continue calculating number of LEDs to be on. 
  *
  * If temperature is outside the allowed range, just ignore this if statement 
  * and then return number of LEDs that is zero by default. 
  */
  if (Temperature < maxTemp && Temperature > minTemp)
  {
    for (std::uint8_t i = 0; i < 4; i++)         // By default there's only 4 LEDs. 
    {
      std::uint8_t temp_ref = minTemp + (tempStep * i); 
      
      if (Temperature >= temp_ref)
      {
        numOfLeds++; 
      }
    }
  }
  
  return numOfLeds; 
}

extern Voltage voltage;