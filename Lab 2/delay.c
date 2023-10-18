/*
 * This program delays a certain number of clock cycles
 */

#include <msp430.h>
#include <stdint.h>

void myHardDelay(uint32_t x) {

    while (x) {   // or while(x != 0)
    __delay_cycles(1000);  // 1 ms delay for a 1MHz CPU clock
    x--;
    }
}
