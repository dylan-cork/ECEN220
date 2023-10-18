/**
 * main.c
 */
// This program toggles the GPIO pin by reading in the direction pin and then switching the direction

#include <msp430.h>
#include <stdint.h>

volatile uint8_t * p1DIR_reg; // volatile stops the optimizer from cutting out this "do nothing" code
volatile uint8_t * p1OUT_reg;

extern void myHardDelay(uint32_t x); //to prevent compiler error

int main(void) {
    uint8_t temp;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Disable the BPIO poer-on default high-impedance mode to activate previously configured port settings

    //load pointers with address of Port 1 MMR regs
    p1DIR_reg = 0x204;
    p1OUT_reg = 0x202;

    //make P1.2 an output i.e. set bit 2 to a 1 (via a read-modify-write operation)
    temp = *p1DIR_reg;
    temp = temp | 0x04; // OR with 0000 0100
    *p1DIR_reg = temp;

    while(1){
        myHardDelay(50);
        temp = *p1OUT_reg;
        temp = temp ^ 0x04; // XOR with a 1 inverts the bit
        *p1OUT_reg = temp;
    }
}
