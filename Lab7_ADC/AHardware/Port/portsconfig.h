// File portsconfig.h contains definition of portC and portA. 

#ifndef _STM32LABS_PORTSCONFIG_H_
#define _STM32LABS_PORTSCONFIG_H_

#include "gpiocregisters.hpp" //for GPIOC
#include "gpioaregisters.hpp" //for GPIOA

#include "port.h"

inline  Port<GPIOC> portC;
inline  Port<GPIOA> portA;

#endif