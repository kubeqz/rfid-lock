#ifndef UTILS_TRACE_TRACE_H
#define UTILS_TRACE_TRACE_H

#include "drivers/uart/uart_driver.h"
#include "utils/printf/printf.h"

#ifdef TRACE_ENABLED
#define TRACE(fmt, ...) printf((char*) fmt "\r\n",  ##__VA_ARGS__)
#else
#define TRACE(fmt, ...)
#endif

class Trace
{
public:
    Trace(Uart::UartDriver &uartDriver);

    static void putc( void* p, char c);

private:
    static Uart::UartDriver *m_uartDriver;
};

#endif /* UTILS_TRACE_TRACE_H_ */
