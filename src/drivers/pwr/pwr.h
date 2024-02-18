#ifndef DRIVERS_PWR_PWR_H
#define DRIVERS_PWR_PWR_H

#include <msp430.h>

class Pwr
{
public:
    Pwr()
    {
        P1DIR |= BIT3;
        // hold power
        P1OUT |= BIT3;
    }

    void off()
    {
        // back to input, external pull-up will disable mosfet
        P1DIR &= ~BIT3;
    }
};

#endif /* DRIVERS_PWR_PWR_H */
