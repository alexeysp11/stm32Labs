// File Temperature.cpp contains implementation of class Temperature. 

#include "Temperature.hpp"

/*
* Invokes temperature measuring and notifies all observers. 
*/
void Temperature::Run()
{
  float temperature = this->GetValue(); 
  
  for(auto& observer: _observers)
  {
    observer->OnUpdate(temperature, NULL, NULL);
  }
}

/*
* Measure temperature using ADC. 
*/
float Temperature::GetValue()
{
  Adc adc; 
  adc.Convert(); 
  
  // Read from DR register and calibration address. 
  std::uint32_t Temp_Data = adc.GetTempFromDR();
  float temp = (((30.0f-110.0f)*Temp_Data+(TS_CAL1*110.0f-TS_CAL2*30.0f))/(TS_CAL1-TS_CAL2));
  
  return temp; 
}

/*
* Adds new observer to the list of IObserverMeasurer. 
*/
void Temperature::Subscribe(IObserverMeasurer& observer)
{
  _observers.push_back(&observer);
}

/*
* Removes an observer from the list of IObserverMeasurer. 
*/
void Temperature::Unsubscribe(IObserverMeasurer& observer)
{
  _observers.remove(&observer);
}