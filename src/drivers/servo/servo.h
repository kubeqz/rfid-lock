#ifndef DRIVERS_SERVO_SERVO_H
#define DRIVERS_SERVO_SERVO_H

#include <msp430.h>
#include <cstdint>

class Servo
{
public:
    Servo()
    {
        P1DIR |= BIT6;
    }

    void setDuty(uint16_t duty)
    {
        P1SEL |=  BIT6;
        P1SEL2 &= ~BIT6;
        P1OUT |= BIT6;

        // assume that SMCLK is 1MHz

        // This will give us a signal with a period of about 20ms with a duty-cycle of 1.5ms
        TA0CCTL1 = OUTMOD_7;          // Reset/set
        TA0CCR0  = 20000;             // Period
        TA0CCR1  = duty;              // Duty-cycle
        TA0CTL   = (TASSEL_2 | MC_1); // SMCLK, timer in up-mode
    }

    void reset()
    {
        setDuty(1000);
    }

    void set()
    {
        setDuty(2500);
    }
};

#endif /* DRIVERS_SERVO_SERVO_H */
