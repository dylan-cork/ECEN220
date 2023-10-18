/*
 *  This program toggles the LED on p1.0 when the switch on p4.1 is pressed
 */

#include <msp430.h>
#include <stdint.h>

volatile uint8_t * p4DIR_reg;   // volatile stops the optimizer from cutting out this "do nothing" code
volatile uint8_t * p4OUT_reg;
volatile uint8_t * p4REN_reg;
volatile uint8_t * p4IN_reg;

//volatile uint8_t * p1DIR_reg;
//volatile uint8_t * p1OUT_reg;

volatile uint8_t * ledDIR_reg;
volatile uint8_t * ledOUT_reg;

uint8_t p41Value = 1;

extern void myHardDelay(uint32_t x);

uint8_t checkS1() {
    // read P2.3
    uint8_t currentValue;
    currentValue = *p4IN_reg;
    currentValue = (currentValue & 0x02) >> 1;
    if(currentValue != p41Value){
        myHardDelay(20);
        if(currentValue != p41Value){
            p41Value = currentValue;
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
    p4DIR_reg = 0x225;
    p4OUT_reg = 0x223;
    p4REN_reg = 0x227;
    p4IN_reg = 0x221;

    ledDIR_reg = 0x204;
    ledOUT_reg = 0x202;

//      p1DIR_reg = 0x204;
//      p1OUT_reg = 0x202;

//      *p1DIR_reg = 0x04;

    *p4DIR_reg = 0x00;
    *p4REN_reg = 0x02;
    *p4OUT_reg = 0x02;

    *ledDIR_reg = 0x01;
    *ledOUT_reg = 0x00;

    while (1) {
        thePinChanged = checkS1();
        if(thePinChanged == 1) {
            if(p41Value == 1) {
                // button released
            }
            else {
                temp = *ledOUT_reg;
                temp = temp ^ 0x01; // XOR with a 1 inverts the bit
                *ledOUT_reg = temp;

//                temp = *p1OUT_reg;
//                temp = temp ^ 0x04; // XOR with a 1 inverts the bit
//                *p1OUT_reg = temp;
            }
        }
    }
}
