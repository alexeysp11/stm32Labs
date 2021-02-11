#pragma once

#include "gpiocregisters.hpp" //for GPIOC
#include "gpioaregisters.hpp" //for GPIOA

#include "Port.hpp"

inline  Port<GPIOC> portC;
inline  Port<GPIOA> portA;