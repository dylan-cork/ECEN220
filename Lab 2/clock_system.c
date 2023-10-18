#include <msp430.h>
#include <stdint.h>

void InitializeClockSystem(void)
{
    // pointers to registers
    volatile uint16_t * pFRCTL0 = (uint16_t *)0x01A0;
    volatile uint16_t * pCSCTL0 = (uint16_t *)0x0180;
    volatile uint16_t * pCSCTL1 = (uint16_t *)0x0182;
    volatile uint16_t * pCSCTL2 = (uint16_t *)0x0184;
    volatile uint16_t * pCSCTL3 = (uint16_t *)0x0186;
    volatile uint16_t * pCSCTL4 = (uint16_t *)0x0188;
    volatile uint16_t * pCSCTL7 = (uint16_t *)0x018E;

    // Configure two FRAM waitstate as required by the device datasheet for MCLK
    // operation at 24MHz(beyond 8MHz) before configuring the clock system.
    *pFRCTL0 = (0xA5 << 8) | (2 << 4);

    __bis_SR_register(SCG0);        // disable FLL

    // Reference section 3.3 from MSP430 users guide
    *pCSCTL3 = 0;                   // REFOLP = 0: low power disabled
                                    // SELREF = 0: FLL reference source = XT1CLK
                                    // FLLREFDIV = 0: div by 1
    *pCSCTL0 = 0;                   // clear DCO and MOD registers
    *pCSCTL1 = (7 << 1);            // DCORSEL = 7: DCO 24 MHz
    *pCSCTL2 = (731 << 0);                 // FLLD = 0: FLL loop divider = 1
                                    // FLLN = 731: N of DCO i.e. (731 + 1) * 32.768kHz = 23.986 MHz

    __bic_SR_register(SCG0);        // enable FLL

    // wait for FLL to lock
    while(((*pCSCTL7) & (3 << 8)) != 0)
    {
        // wait
    }

    *pCSCTL4 = (1 << 8);            // SELMS = 000b: MCLK and SMCLK source is DCOCLKDIV
                                    // SELA = 01b:  ACLK source is REFO
}
