#include <msp430f2274.h>
#include "btUART.h"
#include "delay.h"

//-------------------------BLUTOOTH/UART SETUP & FUNCTIONS & INTERRUPTS-------------------------------------//
void Setup_UART(void) {
  P3SEL = BIT4 + BIT5;                                  // P3.5 = RXD, P3.4=TXD
  UCA0CTL1 |= UCSSEL_2;                                 // SMCLK
  UCA0BR0 = 138;                                        // 16MHz 115200
  UCA0BR1 = 0;                                          // 16MHz 115200
  UCA0MCTL = UCBRS2 + UCBRS1 + UCBRS0;                  // Modulation UCBRSx = 7
  UCA0CTL1 &= ~UCSWRST;                                 // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                                      // Enable USCI_A0 RX interrupt
  
  __bis_SR_register(/*LPM0_bits + */GIE);               // Enter LPM0, interrupts enabled
}

void sendData(char* string) {
  int j = 0;
  while (*(string+j)) {
    outChar = *(string+j);
    j++;
    IE2 |= UCA0TXIE;
    delay_us(1000);
  }
  delay_us(1000);
}

//  Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  while (!(IFG1&UCA0TXIFG));          // USCI_A0 TX buffer ready?
  if (UCA0RXBUF != '\0') {
    trigger[i] = (int)UCA0RXBUF - 48;
    i++;
  }
  if (i == 5) {
    i = 0;
  }
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
  UCA0TXBUF = outChar;            // Copy a character to the transmit buffer
  IE2 &= ~UCA0TXIE;               // Disable TX interrupt
}
//----------------------------------------------------------------------------------------------------//



void btConfig(void) {
  //----------------------RN42 CONFIQ----------------------------//
  sendString("$$$\r");
  sendString("SF,1\r");
  sendString("SA,0\r");
  sendString("SN,Helicopter\r");
  sendString("S~,0\r");
  sendString("---\r");
  sendString("R,1\r");
  
  sendString("$$$\r");   
  sendString("SM,0\r"); //slave mode
  sendString("ST,15\r");
  sendString("R,1\r");
  sendString("---\r");
  //-------------------------------------------------------------//
}