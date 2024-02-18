#ifndef LOGIC_IMMO_H
#define LOGIC_IMMO_H

#include "drivers/buzzer/buzzer.h"
#include "drivers/servo/servo.h"
#include "drivers/rfid/rfid.h"
#include "drivers/pwr/pwr.h"

class LockLogic
{
public:
    enum ImmoState {
        LOCK_IDLE,
        LOCK_CHECK_TAG,
        LOCK_MOVE
    };

    LockLogic(Servo& servo, Pwr& pwr, Buzzer& buzzer, Rfid& rfid)
      : m_servo(servo)
      , m_pwr(pwr)
      , m_buzzer(buzzer)
      , m_rfid(rfid)
    {
    }

    bool checkTag();

    void process();

private:
    Servo& m_servo;
    Pwr& m_pwr;
    Buzzer& m_buzzer;
    Rfid& m_rfid;
};

#endif /* LOGIC_IMMO_H */
