#include <drivers/uart/hw_uart_driver.h>

namespace Uart
{

void HwUartDriver::initialise()
{
    m_hal.initialise();
    m_hal.setRxListener(*this);
    m_hal.setTxListener(*this);

    m_hal.enableRxIrq(true);
}

void HwUartDriver::write(unsigned char data)
{
    __disable_interrupt();

    m_txBuffer.write(data);

    m_hal.enableTxIrq(true);

    __enable_interrupt();
}

void HwUartDriver::write(unsigned char* buffer, size_t length)
{
    while(length--) {
        write(*buffer);
        ++buffer;
    }
}

unsigned char HwUartDriver::read(unsigned char* data, size_t length)
{
    unsigned char * ptr = data;

    while(length-- && (m_rxBuffer.getAvailable() != 0)) {
        __disable_interrupt();
        m_rxBuffer.read(*data);
        __enable_interrupt();

        ++data;
    }

    return data - ptr;
}

unsigned char HwUartDriver::available()
{
    return m_rxBuffer.getAvailable();
}

void HwUartDriver::resetRx()
{
    __disable_interrupt();

    m_rxBuffer.reset();

    __enable_interrupt();
}

void HwUartDriver::resetTx()
{
    __disable_interrupt();

    m_txBuffer.reset();

    __enable_interrupt();
}

void HwUartDriver::onUartRx(unsigned char data)
{
    // assumption: called from IRQ, not needed to disable interrupts
    m_rxBuffer.write(data);
}

void HwUartDriver::onUartTx()
{
    // assumption: called from IRQ, not needed to disable interrupts
    uint8_t data = 0;

    if (m_txBuffer.read(data)) {
        m_hal.put(data);
    } else {
        m_hal.enableTxIrq(false);
    }
}

} // namespace
