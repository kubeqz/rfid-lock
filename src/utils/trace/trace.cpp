
#include "trace.h"

Uart::UartDriver *Trace::m_uartDriver = nullptr;

Trace::Trace(Uart::UartDriver &uartDriver)
{
    m_uartDriver = &uartDriver;
    init_printf(NULL, putc);
}

void Trace::putc( void* /*p*/, char c)
{
    if (m_uartDriver) {
        m_uartDriver->write(c);
    }
}
