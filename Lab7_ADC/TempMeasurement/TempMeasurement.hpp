#pragma once

#include "port.h"
#include "portsconfig.h"
#include "Led.hpp"
#include "Voltage.hpp"

#include <cstdint>

class TempMeasurement
{
public: 
  TempMeasurement();
  void Run(); 
}; 

extern TempMeasurement tm;