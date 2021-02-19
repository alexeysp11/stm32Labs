#include "TempMeasurement.hpp"

TempMeasurement::TempMeasurement()
{
}

void TempMeasurement::Run()
{
  // Create an instance of class Voltage. 
  IVoltage* voltage = new Voltage();
  
  // Get number of LEDs to be on. 
  std::uint8_t num_leds = voltage->GetNumOfLeds(); 
  
  // Delete an instance of class Voltage. 
  voltage->~IVoltage();
  
  // Create instances of class Led. 
  ILed* led01 = new Led(5, portC);
  ILed* led02 = new Led(8, portC);
  ILed* led03 = new Led(9, portC);
  ILed* led04 = new Led(5, portA);
  
  // Make an array of LEDs. 
  ILed* LedsArray[4] = {
    led01, 
    led02,
    led03, 
    led04
  }; 
  
  // Switch on (and switch off) required LEDs in for cycle. 
  for (std::uint8_t i = 0; i < sizeof(LedsArray); i++)
  {
    if (i <= num_leds)
    {
      LedsArray[i]->SetHigh();  // Set high. 
    }
    else
    {
      LedsArray[i]->SetLow();   // Set low. 
    }
  }
  
  delete LedsArray;
  
  // Delete instances of class Led. 
  led01->~ILed();
  led02->~ILed();
  led03->~ILed();
  led04->~ILed();
}