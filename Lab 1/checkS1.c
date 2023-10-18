#include <msp430.h>
#include <stdint.h>
#include "ex3.c"

uint8_t checkS1(){
    // read P2.3
    uint8_t currentValue;
    currentValue = *p2IN_reg;
    currentValue = (currentValue & 0x08) >> 3;
    if(currentValue != p23Value){
        myHardDelay(20);
        if(currentValue != p23Value){
            p23Value = currentValue;
        return 1;
        }
    }
return 0;
}
