/*
 *  This program toggles the LED on p6.6 when the switch on p2.3 is pressed
 */

#include <msp430.h>
#include <stdint.h>
#include "adc.h"

volatile uint8_t * p2DIR_reg;   // volatile stops the optimizer from cutting out this "do nothing" code
volatile uint8_t * p2OUT_reg;
volatile uint8_t * p2REN_reg;
volatile uint8_t * p2IN_reg;

//volatile uint8_t * p1DIR_reg;
//volatile uint8_t * p1OUT_reg;

volatile uint8_t * p6DIR_reg;
volatile uint8_t * p6OUT_reg;

uint8_t p23Value = 1;

extern void myHardDelay(uint32_t x);

uint8_t checkS1() {
    // read P2.3
    uint8_t currentValue;
    currentValue = *p2IN_reg;
    currentValue = (currentValue & 0x08) >> 3;
    if(currentValue != p23Value){
        myHardDelay(20);
        if(currentValue != p23Value){
            p23Value = currentValue;
        } return 1;
    }
    return 0;
}

int main(void) {
    uint8_t temp;
    uint8_t thePinChanged; // 0 = no change, 1 = pin changed

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the BPIO power-on default high-impedance mode
                                // to activate previously configured port settings

    // load pointers with address of Port 2 MMR regs
    p2DIR_reg = 0x205;
    p2OUT_reg = 0x203;
    p2REN_reg = 0x207;
    p2IN_reg = 0x201;

    p6DIR_reg = 0x245;
    p6OUT_reg = 0x243;

//      p1DIR_reg = 0x204;
//      p1OUT_reg = 0x202;
//
//      *p1DIR_reg = 0x04;

    *p2DIR_reg = /**p2DIR_reg & 0xF7;*/ 0x00;
    *p2REN_reg = /*p2REN_reg | 0x08;*/ 0x08;
    *p2OUT_reg = /*p2OUT_reg | 0x08;*/ 0x08;

    *p6DIR_reg = /*p6DIR_reg | 0x40;*/ 0x40;
    *p6OUT_reg = /*p6DIR_reg & 0xBF;*/ 0x00;

    while (1) {
        thePinChanged = checkS1();
        if(thePinChanged == 1) {
            if(p23Value == 1) {
                // button released
            }
            else {



            }
        }
    }
}
