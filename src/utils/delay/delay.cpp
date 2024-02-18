#include "delay.h"

#include <msp430.h>

extern "C" void Timer_A1(void) __attribute((interrupt(TIMER0_A1_VECTOR)));

void Timer_A1(void)
{
    TA0CTL = 0;
    LPM0_EXIT;
}


void delay_us(uint16_t val)
{
    TA0CCR0 = val;
    TA0CTL = TASSEL_2 + ID_3 + TACLR + MC_1 + TAIE;

    __bis_SR_register(LPM0_bits + GIE);
}


void delay_ms(uint16_t val)
{
    uint32_t val_us = (uint32_t) val * 1000;
    constexpr uint32_t singleIterationMaxDelayUs = 32000;

    while (val_us != 0) {
        if (val_us <= singleIterationMaxDelayUs) {
            delay_us(val_us);
            break;
        } else {
            delay_us(singleIterationMaxDelayUs);
            val_us -= singleIterationMaxDelayUs;
        }
    }
}
