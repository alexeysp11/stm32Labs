/*******************************************************************************
*  FILENAME:      uart.hpp
*
*  DESCRIPTION:   This file contains declaration of a template class `Uart`  
*                 and pure abstract class `IUartBase`. 
* 
******************************************************************************/

#ifndef _STM32LABS_UART_HPP_
#define _STM32LABS_UART_HPP_

#include <cstdint>

/*
* Abstract base class for UART. 
*/
class IUartBase
{
public:
  virtual void WriteByte(std::uint8_t byte) = 0;
  virtual void TransmitEnable() = 0; 
  virtual void TransmitDisable() = 0; 
  virtual void InterruptsEnable() = 0; 
  virtual void InterruptsDisable() = 0; 
};

/*
* Template class for UART. 
*/
template<typename UartReg>
class Uart : public IUartBase
{
public: 
  Uart()
  {
  }
  
  void WriteByte(std::uint8_t byte)
  {
    UartReg::DR::Write(byte);
  } 

  /*
  * Returns true if transmit data register is empty and TXE interrupt 
  * enableb. 
  */
  bool IsTransferRegisterEmpty()
  {
    bool isRegisterEmpty = UartReg::SR::TXE::Value1::IsSet();           // Data is transferred to the shift register. 
    bool isInterruptEnabled = UartReg::CR1::TXEIE::Value1::IsSet();     // An USART interrupt is generated whenever TXE=1 in the USART_SR register. 

    return isRegisterEmpty && isInterruptEnabled; 
  }

  void TransmitEnable()
  {
    UartReg::CR1::TE::Enable::Set();                    // Transmitter is enabled. 
    UartReg::CR1::RE::Enable::Set();                    // Receiver is enabled and begins searching for a start bit. 
  }

  void TransmitDisable()
  {
    UartReg::CR1::TE::Enable::Set();                    // Transmitter is disabled. 
    UartReg::CR1::RE::Disable::Set();                   // Receiver is disabled. 
  }

  void InterruptsEnable()
  {
    UartReg::CR1::TXEIE::Value1::Set();                 // An USART interrupt is generated whenever TXE=1 in the USART_SR register. 
  }

  void InterruptsDisable()
  {
    UartReg::CR1::TXEIE::Value0::Set();                 // Interrupt is inhibited. 
  }
};

#endif  // _STM32LABS_UART_HPP_
