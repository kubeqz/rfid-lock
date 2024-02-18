
#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <cstddef>

namespace Uart {

class UartDriver
{
public:
    virtual void write(unsigned char data) = 0;
    virtual void write(unsigned char* buffer, size_t length) = 0;

    virtual unsigned char read(unsigned char* data, size_t length) = 0;
    virtual unsigned char available() = 0;

    virtual void resetRx() {}
    virtual void resetTx() {}
};

} // namespace

#endif /* UART_DRIVER_H */
