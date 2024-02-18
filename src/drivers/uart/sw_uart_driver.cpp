#include "drivers/uart/sw_uart_driver.h"
#include <cstdint>

#include <msp430.h>

namespace Uart {

#define CLOCK                   8000000     // [cycles per second]

#define UART_BAUDRATE           9600       // speed [9600]

#define UART_TX_PORT            P2OUT
#define UART_TX_DIR             P2DIR
#define UART_TX_BIT             BIT2

#define UART_TX_TIME            8          // cycles for tx single bit operation [19200:12, 9600:8]

#define UART_TX_CPB             ((CLOCK / UART_BAUDRATE) - UART_TX_TIME)    // tx cycles per bit

#define UART_PIN_SET            UART_TX_PORT |= UART_TX_BIT
#define UART_PIN_CLR            UART_TX_PORT &= ~UART_TX_BIT
#define UART_PIN_XOR            UART_TX_PORT ^= BIT2

#define UART_SEND_1  UART_PIN_SET    //use high as 1
#define UART_SEND_0  UART_PIN_CLR    //use low as 0

void SwUartDriver::initialise()
{
    UART_TX_DIR |= UART_TX_BIT;
    UART_SEND_1;                              //make sure tx state before start bit
}

void SwUartDriver::write(unsigned char data)
{
    uint8_t bitcounter;

    // make sure tx state before start bit
    UART_SEND_1;

    __disable_interrupt();

    // start bit
    UART_SEND_0;
    __delay_cycles(UART_TX_CPB);

    bitcounter = 8;
    do
    {
        if (data & 0x01) {
            UART_SEND_1;
        } else {
            UART_SEND_0;
        }

        __delay_cycles(UART_TX_CPB);

        data >>= 1;
    }
    while (--bitcounter);

    // stop bit
    UART_SEND_1;
    __delay_cycles(UART_TX_CPB);

    __enable_interrupt();
}

void SwUartDriver::write(unsigned char* data, size_t length)
{
    while (length--)
    {
        write(*data);
        ++data;
    }
}

} // namespace
