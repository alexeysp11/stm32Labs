/*******************************************************************************
*  FILENAME:      uartdriver.hpp
*
*  DESCRIPTION:   This file contains declaration of a class `UartDriver`   
*                 to use UART (class `Uart` in AbstractHardware folder). 
* 
* This file include `uartconfig.hpp` that defines an instance of template 
* class `Uart`. 
* This instance is called `uart` and used by `UartDriver` class.
* When interrupt occured in 
* 
******************************************************************************/

#ifndef _UARTDRIVER_HPP_
#define _UARTDRIVER_HPP_

#include "uartconfig.hpp"       // for declaration of `Uart` class using UART2. 

#include <cassert>
#include <array>

/*
* Provides method for sending a message using UART. 
*/
class UartDriver
{
public: 
  UartDriver() {}

  /*
  * Sends a message via UART. 
  * 
  * In infinite `for` loop checks if a message is completely sent. 
  * If it is true, set byte index equal to zero, disable interrupts 
  * and disable transmission. 
  * If it is false, checks if transfer register is empty. 
  * 
  * If transfer register is empty, write next byte into transfer register. 
  * If transfer register is not empty, do nothing and repeat the cycle again. 
  */ 
  void SendMessage(const char* message, size_t aSize)
  {
    assert(size <= 255);
    memcpy(buffer.data(), message, aSize);
    size = aSize;
    byteIndex = 0U;
    
    for(;;)
    {
      uart.InterruptsEnable(); 
      uart.TransmitEnable(); 
      
      if (byteIndex >= size)      // Check if message is completely sent. 
      {
        byteIndex = 0U;           // Set index equal to zero. 

        uart.InterruptsDisable(); 
        uart.TransmitDisable(); 

        break; 
      }

      if (uart.IsTransferRegisterEmpty())
      {
        uart.WriteByte(buffer[byteIndex++]); 
      }
    }
  }

private:
  std::uint8_t byteIndex = 0; 
  size_t size = 0; 
  std::array<std::uint8_t, 255> buffer; 
};

#endif // _UARTDRIVER_HPP_