#ifndef HW_UART_DRIVER_H
#define HW_UART_DRIVER_H

#include "uart_driver.h"
#include "utils/buffers/ring_buffer.h"
#include "hals/uart/uart_hal.h"

namespace Uart
{

class HwUartDriver : public UartRxListener, public UartTxListener, public UartDriver
{
public:
    HwUartDriver(UartHal& hal)
      : m_rxBuffer(m_rxBufferArray, m_RxBufferSize)
      , m_txBuffer(m_txBufferArray, m_TxBufferSize)
      , m_hal(hal)
    {
    }

    void initialise();

    void write(unsigned char data) final;
    void write(unsigned char * data, size_t length) final;

    unsigned char read(unsigned char* data, size_t length) final;
    unsigned char available() final;

    void resetRx() final;
    void resetTx() final;

    void onUartRx(unsigned char data) final;
    void onUartTx() final;

private:
    static const uint8_t m_RxBufferSize = 16;
    static const uint8_t m_TxBufferSize = 16;

    uint8_t m_rxBufferArray[m_RxBufferSize];
    uint8_t m_txBufferArray[m_RxBufferSize];

    RingBuffer m_rxBuffer;
    RingBuffer m_txBuffer;

    UartHal& m_hal;
};

} // namespace

#endif // HW_UART_DRIVER_H
