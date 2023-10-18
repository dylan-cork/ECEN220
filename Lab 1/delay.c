#include <msp430.h>
#include <stdint.h>

//This program delays a certain number of clock cycles

void myHardDelay(uint32_t x){   //or while(x !=0)
    while(x){
        __delay_cycles(1000); // 1ms delay for a 1MHz CPU clock
        x--;
    }
}
