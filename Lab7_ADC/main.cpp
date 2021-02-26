/*
* This program uses ADC in order to measure temperature and supply voltage. 
* Using a value of supply voltage allows to get more precise estimation of 
* temperature. 
* 
* When temperature is etimated, an object of LedsController class should 
* switch on or switch off some LEDs depending on the temperature estimation. 
* 
* Observer pattern is used in this application as a main design pattern. 
*/

#include "Observers.hpp"
#include "LedsController.hpp"
#include "Led.hpp"
#include "port.h"
#include "portsconfig.h"
#include "Solver.hpp"
#include "Temperature.hpp"
#include "Voltage.hpp"
#include "Adc.hpp"

#include "rccregisters.hpp"
#include "gpiocregisters.hpp"
#include "gpioaregisters.hpp"
#include "adc1registers.hpp"
#include "adccommonregisters.hpp"

#include <cstdint>

extern "C"
{
  int __low_level_init(void)
  {
    RCC::CR::HSEON::On::Set();
    while (!RCC::CR::HSERDY::Ready::IsSet());
    RCC::CFGR::SW::Hse::Set();

    while (!RCC::CFGR::SWS::Hse::IsSet());
    RCC::CR::HSION::Off::Set();
    RCC::APB2ENR::ADC1EN::Enable::Set();
    RCC::AHB1ENR::GPIOAEN::Enable::Set();
    GPIOA::MODER::MODER0::Analog::Set();
    
    // Configure ADC. 
    RCC::APB2ENR::ADC1EN::Enable::Set();
    ADC1::SQR3::SQ1::Value18::Set();            // Channel 18 (for temperature sensor). 
    ADC_Common::CCR::TSVREFE::Value1::Set();    // Temperature sensor and VREFINT channel enabled. 
    ADC1::CR1::RES::Value0::Set();              // 12-bit (15 ADCCLK cycles)
    ADC1::CR2::CONT::Value1::Set();             // Continuous conversion mode. 
    ADC1::CR2::EOCS::Value0::Set();             // The EOC bit is set at the end of each sequence of regular conversions. Overrun detection is enabled only if DMA=1.
    ADC1::SQR1::L::Value0::Set();               // 1 conversion. 
    ADC1::SMPR1::SMP18::Cycles84::Set();        // 84 cycles. 
    ADC1::CR2::ADON::Value1::Set();             // Enable ADC. 
    
    return 1;
  }
}

int main()
{
  // Create instances of class Led. 
  Led led01(5, portC);
  Led led02(8, portC);
  Led led03(9, portC);
  Led led04(5, portA);
  
  // Make an array of LEDs. 
  Led ledsArray[4] = {
    led01, 
    led02,
    led03, 
    led04
  }; 
  
  // Create instances of measurement devices. 
  Temperature temperature; 
  Voltage voltage; 
  
  // Create an instance of class Solver. 
  Solver solver; 
  
  // Create an instance of class LedsController. 
  LedsController ledController(ledsArray); 
  
  // Define relationships between subjects and observers. 
  solver.Subscribe(ledController); 
  temperature.Subscribe(solver); 
  voltage.Subscribe(solver); 
  
  while(true)
  {
    temperature.Run(); 
    voltage.Run();
  }
  
  return 0;
}