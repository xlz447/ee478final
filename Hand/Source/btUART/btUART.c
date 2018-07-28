#include "btUART.h"

//-------------------------BLUTOOTH/UART SETUP & FUNCTIONS & INTERRUPTS-------------------------------------//
/*
 * Setup_UART()
 *
 * Description: This function initiates the uart for bluetooth comunication
 *
 * Operation:   This function sets up the uart by the following step
 *              1. open port 3.4 3.5 for bluetooth rx and tx
 *              2. set universal serial comunication control registor 1(UCA0CTL1) to run smclk
 *              3. set brad rate to 115200
 *              4. set universal serial comunication master control registor (UCA0MCTL) to select modulation 7
 *              5. initialize usc interrupt state machine
 *              6. enable usc interrupt
 * Argument: none
 *
 * Return value: none
 *
 */
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

/*
 * sendString()
 *
 * Description: This function sents the string to bluetooth
 *
 * Operation:   This function controls the sending of a string to bluetooth
 *              the process is to sent one character at a time until the whole string has been sent
 *              when a character is ready to be sent, the transmit interrupt is enabled
 *              and when the character is done sending, the interrupt will disable its self
 *              when the last character has been sent, the transmit interrupt will not be enabled
 *              between each character, there is a small delay that lets the bluetooth sent the character
 *              over to the helicopter
 *              
 * Argument: char* string, the character string that will be sent
 *
 * Return value: none
 *
 */
void sendString(char* string) {
  int j = 0;
  while (*(string+j)) {
    outChar = *(string+j);
    j++;
    IE2 |= UCA0TXIE;
    delay_us(1000);
  }
  delay_us(1000);
}

/*
 * USCI0RX_ISR()
 *
 * Description: This function is the interrupt service routine for usc read 
 *
 * Operation:   This function recives the message from bluetooth, and sets the warning and
 *              state flags right away, so other method can use it in time.
 *              while reciving, it is actually decoding a 6 digit string that is sent from helicopter
 *              first 4 digits are temperature, fifth digit is warning and sixth digit is state.
 *
 * Argument: none
 *
 * Return value: none
 *
 */

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  //  Echo back RXed character, confirm TX buffer is ready first
  int k = 0;
  while (!(IFG1&UCA0TXIFG));          // USCI_A0 TX buffer ready?
  if (UCA0RXBUF != '\0') {
    receivedString[k] = UCA0RXBUF;
    k++;
  }
  warning = receivedString[4] - 48;
  state = receivedString[5] - 48;
  if (k == 6) {
    stringReady = 1;
    k = 0;
  }
  receivedString[6] = '\0';
}

/*
 * USCI0TX_ISR()
 *
 * Description: This function is the interrupt service routine for usc transmit 
 *
 * Operation:   This function sents the current character over TX
 *              it will disable its self after it finishes the trasmit
 *              while reciving, it is actually decoding a 6 digit string that is sent from helicopter
 *              first 4 digits are temperature, fifth digit is warning and sixth digit is state.
 *
 * Argument: none
 *
 * Return value: none
 *
 */
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
  UCA0TXBUF = outChar;                  // Copy a character to the transmit buffer
  IE2 &= ~UCA0TXIE;                     // Disable TX interrupt
}
//----------------------------------------------------------------------------------------------------//

/*
 * btConfig()
 *
 * Description: This function initiates the bluetooth module by sending commands to it via uart
 *
 * Operation:   This function initiates the bluetooth module in the following steps
 *              1. sent $$$ enter command mode
 *              2. sent SF,1  factory reset
 *              3. sent SA,0 turn off authentication
 *              4. sent SN,Hand Gesture change bluetooth name to Hand Gesture
 *              5. sent S~,0  SPP mode
 *              6. sent R,1  restart module
 *              7. sent --- exit command mode
 *              The following command is to set up and connect to helicopter bluetooth
 *              1. sent $$$ enter command mode
 *              2. sent C  connect
 *              3. sent SM,3 auto master mode
 *              4. sent SR,0006666D9ED7  connect to 0006666D9ED7, slave mac address
 *              5. sent R,1  restart module
 *              6. sent --- exit command mode
 * Argument: none
 *
 * Return value: none
 *
 */
void btConfig(void) {
  //----------------------RN42 CONFIQ----------------------------//
  sendString("$$$\r");
  sendString("SF,1\r");
  sendString("SA,0\r");
  sendString("SN,Hand Gesture\r");
  sendString("S~,0\r");
  sendString("R,1\r");
  sendString("---\r");
  
  sendString("$$$\r");
  sendString("C\r");
  sendString("SM,3\r"); //master mode
  sendString("SR,0006666D9ED7\r"); //slave address
  sendString("R,1\r");
  sendString("---\r");
  //-------------------------------------------------------------//
}
