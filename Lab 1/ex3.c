#include <msp430.h>
#include <stdint.h>

volatile uint8_t * p2DIR_reg;
volatile uint8_t * p2OUT_reg;
volatile uint8_t * p2REN_reg;
volatile uint8_t * p2in_reg;

volatile uint8_t * p6DIR_reg;
volatile uint8_t * p6OUT_reg;

uint8_t p23Value = 1;

extern void myHardDelay(uint32_t x);

int main(void){
    uint8_t temp;
    uint8_t thePinChanged; // 0 = No Change, 1 = Pin Changed

    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;
impedance mode  // to activate previously configured port settings

    //load pointers with address of Port 2 MMR regs
    p2IN_reg = 0x201;
    p2OUT_reg = 0x203;
    p2DIR_reg = 0x205;
    p2REN_reg = 0x207;

    p6OUT_reg = 0x243;
    p6DIR_reg = 0x245;

    *p2DIR_reg = *p2DIR_reg & 0xF7;
    *p2REN_reg = *p2REN_reg | 0x08;
    *p2OUT_reg = *p2OUT_reg | 0x08;

    *p6DIR_reg = *p6DIR_reg | 0x40;
    *p6OUT_reg = *p6DIR_reg & 0xBF;

    while(1){
        thePinChanged =checkS1();
        if(thePinChanged == 1){
            if(p23Value == 1){
                // Button Released
            } else{
                temp = *p6OUT_reg;
                temp = temp ^ 0x40;
                *p6OUT_reg = temp;
            }
        }
    }

}
