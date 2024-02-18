#include <logic/lock.h>
#include "drivers/rfid/rfid.h"
#include "drivers/clock/clock.h"
#include "utils/trace/trace.h"

#include <cstring>
#include <msp430.h>

bool LockLogic::checkTag()
{
    m_rfid.setPower(true);
    m_rfid.initialise();

    bool tagPresent = true;

    uint8_t cardTag[4] = {};
    if (m_rfid.readCard(cardTag, sizeof(cardTag))) {
        TRACE("TAG ID: 0x%x 0x%x 0x%x 0x%x", cardTag[0], cardTag[1], cardTag[2], cardTag[3]);
        uint8_t validCardTag[4] = {0xdd, 0x30, 0xca, 0x55};

        for (unsigned i = 0; i < sizeof(cardTag); ++i) {
            if (cardTag[i] != validCardTag[i]) {
                tagPresent = false;
                break;
            }
        }
    } else {
        tagPresent = false;
    }

    m_rfid.setPower(false);

    return tagPresent;
}

void LockLogic::process()
{
    initFastClock();
    bool result = checkTag();

    initSlowClock();

    if (result) {
        m_buzzer.doubleBeep(50, 100);
        m_servo.set();
    } else {
        m_servo.reset();
    }

    // give servo enough time to move
    for (unsigned i = 0; i <= 800; i++) {
        __delay_cycles(1000);
    }

    m_pwr.off();
}
