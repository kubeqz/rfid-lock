#ifndef BUZZER_H
#define BUZZER_H

#include <msp430.h>
#include "utils/delay/delay.h"

class Buzzer
{
public:
    Buzzer()
    {
        P2DIR |= BIT1;
        P2OUT &= ~BIT1;
    }

    void singleBeep(uint16_t ms)
    {
        P2OUT |= BIT1;
        delay_ms(ms);
        P2OUT &= ~BIT1;
    }

    void doubleBeep(uint16_t beepMs, uint16_t beepDelay)
    {
        singleBeep(beepMs);
        delay_ms(beepDelay);
        singleBeep(beepMs);
    }
};

#endif // BUZZER_H
