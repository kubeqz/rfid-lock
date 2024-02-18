
#ifndef DRIVERS_RFID_RFID_H
#define DRIVERS_RFID_RFID_H

#include "drivers/uart/uart_driver.h"
#include <cstdint>
#include <cstddef>

class Rfid
{
public:
    virtual void initialise() = 0;
    virtual void setPower(bool power) {};
    virtual bool readCard(uint8_t * id, size_t idMaxLen) = 0;
};

class Mfrc522Rfid : public Rfid
{
public:
    Mfrc522Rfid(Uart::UartDriver& uart)
      : m_uart(uart)
    {
    }

    void initialise() final;
    bool readCard(uint8_t * id, size_t idMaxLen) final;

private:
    Uart::UartDriver& m_uart;
};

#endif /* DRIVERS_RFID_RFID_H */
