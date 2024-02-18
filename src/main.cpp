#include <drivers/servo/servo.h>
#include <msp430.h>

#include <drivers/uart/hw_uart_driver.h>
#include <logic/lock.h>
#include "drivers/uart/sw_uart_driver.h"
#include "drivers/uart/sw_uart_driver.h"
#include "drivers/buzzer/buzzer.h"
#include "drivers/clock/clock.h"
#include "drivers/rfid/rfid.h"
#include "drivers/pwr/pwr.h"
#include "drivers/servo/servo.h"
#include "drivers/wdt/wdt.h"
#include "hals/uart/uart_hal.h"

#include "utils/delay/delay.h"
#include "utils/trace/trace.h"

Uart::HwUartDriver& getHwUartDriver()
{
    static Uart::UartHal hal;
    static Uart::HwUartDriver driver(hal);

    driver.initialise();
    return driver;
}

Buzzer& getBuzzer()
{
    static Buzzer buzzer;
    return buzzer;
}

Rfid& getRfid()
{
    static Mfrc522Rfid rfid(getHwUartDriver());
    return rfid;
}

Uart::SwUartDriver& getSwUartDriver()
{
    static Uart::SwUartDriver swUart;
    swUart.initialise();

    return swUart;
}

Pwr& getPwr()
{
    static Pwr pwr;
    return pwr;
}

Servo& getServo()
{
    static Servo servo;
    return servo;
}

int main()
{
    Wdt().disable();

    // set P3 for power saving
    P3DIR = 0xFF;
    P3OUT = 0;

    initFastClock();

    initSlowClock();

    LockLogic lockLogic(getServo(), getPwr(), getBuzzer(), getRfid());
    lockLogic.process();

    LPM3;
}
