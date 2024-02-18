#ifndef SW_UART_DRIVER_H
#define SW_UART_DRIVER_H

#include "uart_driver.h"

namespace Uart {

class SwUartDriver : public UartDriver
{
public:
    void initialise();

    void write(unsigned char data) final;
    void write(unsigned char * data, size_t length) final;

    // read is not supported
    unsigned char read(unsigned char* data, size_t length) final { return '0'; }
    unsigned char available() final { return 0; }
};

} // namespace

#endif // SW_UART_DRIVER_H
