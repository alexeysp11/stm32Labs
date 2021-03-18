/*******************************************************************************
*  FILENAME:      uartconfig.hpp
*
*  DESCRIPTION:   This file contains registers configuration for using 
*                 a class `Uart` defined in `uart.hpp` file. 
* 
******************************************************************************/

#include "uart.hpp"                     // for `Uart` class. 
#include "usart2registers.hpp"          // for UART2. 

inline Uart<USART2> uart; 
