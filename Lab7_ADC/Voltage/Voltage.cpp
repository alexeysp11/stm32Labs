// File Voltage.cpp contains implementation of class Voltage. 

#include "Voltage.hpp"

/*
* Invokes voltage measuring and notifies all observers. 
*/
void Voltage::Run()
{
  float voltage = this->GetValue(); 
  
  for(auto& observer: _observers)
  {
    observer->OnUpdate(NULL, voltage, K);
  }
}

/*
* Measure supply voltage using ADC. 
*/
float Voltage::GetValue()
{
  Adc adc; 
  adc.Convert(); 
  
  // Read from DR register and calibration address. 
  float Vref_Data = adc.GetVoltageFromDR(); 
  K = V_REF / Vref_Data;
  float voltage = (Vref_Data*(3.3F/4095.0F))*K;
  
  return voltage;
}

/*
* Adds new observer to the list of IObserverMeasurer. 
*/
void Voltage::Subscribe(IObserverMeasurer& observer)
{
  _observers.push_back(&observer);
}

/*
* Removes an observer from the list of IObserverMeasurer. 
*/  
void Voltage::Unsubscribe(IObserverMeasurer& observer)
{
  _observers.remove(&observer);
}
