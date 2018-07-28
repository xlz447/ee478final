#include <msp430f2274.h>
#include "timer.h"
#include "delay.h"
//----------------------------------------TIMER SETUP & INTERRUPTS--------------------------------------------------//

/*
 * Setup_Timer()
 *
 * Description: This function sets up the timer interrupt
 *
 * Operation:   This function sets up the timer by the following steps
 *              1. enable Capture/compare interrupt
 *              2. set Capture/compare timer control to set smclk, count up mode, 
 *                 with a divider of 8.
 * 
 * Argument: none
 *
 * Return value: none
 *
 */
void Setup_Timer(void) {
  TACCTL0 = CCIE;                           // CCR0 interrupt enabled
  TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode 
  TACCR0 = 59;                              // 16M/8/59 = 33898HZ
}


/*
 * Timer_A()
 *
 * Description: This function is the interrupt service routine for the timer
 *              these code will be excuted after the timer has timed out
 *
 * Operation:   This function controls flying of the helicopter
 *              In order for this too work there is few conditions
 *                1. The PWM frequency that the helicopter need is 333 Hz.
 *                2. the duty cycle is veried to change the speed of the motors
 *                3. the duty cycle is changed over time, not instantaneous 
 *              Therefore, the timer is set at 33333 Hz, with a software counter that will
 *              count up to 100 and toggle the GPIO to simulate the 333 HZ PWM. And the 
 *              duty cycle can be easily controled by the software counter.
 *              For a fully functional helicopter, we need throttle, elevator, aileron and rudder
 *              Therefore we have 4 channels to control, each of them needs their own duty cycle counter
 *              This way, the duty cycles of the 4 channels can be set separately.
 *              As for throttle, it's very different than others, it is a state machine 
 *              It as take off, slow up, slow down, and idle states
 *              when on the ground, give a throttle input, will bring the helicopter into
 *              take off state, in which the helicopter will increase the Thro duty cycle
 *              to 60% over 3 seconds to take off, after taking off, throttle input will
 *              enter slow up mode (increase 1% duty cucle / second), and no throttle
 *              input will enter slow down mode (decrease 1%/s). After 20 seconds of slow down mode
 *              the helicopter will be landed and return to idle state.
 *              The rudder is also a sepcial one, because it needs to compensate for rotational
 *              force the throttle gave to the body, so its a function over throttle.
 *              The other two channles are fixed ammount duty cycle changes.
 *              The function first checks the state of the helicopter (throttle state),
 *              then it adjust the duty cycle of each channel according to the tiggers.
 *              At the end, there is a dead man's switch that throttle will cut power if
 *              its been at 60% for 10 seconds.
 * Argument: none
 *
 * Return value: none
 *
 */
// Timer A0 interrupt service routine 
#pragma vector=TIMERA0_VECTOR 
__interrupt void Timer_A (void) 
{ 

  switch (state) {
  //Idle
  case 0:
    if (trigger[0] == 1) {
    state = 1;              //enter TakeOff mode
    } 
    break;
    
    //TakeOff
  case 1:
    timeCount++;
    if (timeCount == TAKEOFFCOUNT) {
    timeCount = 0;
      if (thro_dc < HIGHDC) {
    thro_dc++;
      } else {                //dc >= HIGHDC
    holdCount++;
        if (holdCount > HOVTIME) {
    holdCount = 0;
          state = 2;          //enter SlowUp mode
        }
        }
      }
      break;
    
    //SlowUp
  case 2:
    timeCount++;
    if (timeCount == SLOWUPCOUNT) {
    timeCount = 0;
      if (thro_dc < HIGHDC) {
    thro_dc++;
      }
    if (thro_dc == 57) {
      secondCount++;
    } else {
      secondCount = 0;
    }
    }
    if (trigger[0] == 0) {
    state = 3;              //enter SlowDown mode
    } 
    break;
    
    //SlowDown
  case 3:
    timeCount++;
    if (timeCount == SLOWDOWNCOUNT) {
    timeCount = 0;
      if (thro_dc >= LOWDC) {
    thro_dc -= 1;
      } else {
    state = 0;            // enter Idle mode
      }
      }
      if (trigger[0] == 1) {
    state = 2;              //enter SlowUp mode
      }
    break;
  }
    
  if (trigger[1]) {   // elevator
  elev_dc = 48;
  } else if (trigger[2]) {
  elev_dc = 50;
  } else if (!trigger[1] && !trigger[2]) {
  elev_dc = 49;
  }
  
  if (trigger[3]) { //aileron
  aile_dc = 49;
  } else if (trigger[4]) {
  aile_dc = 47;
  } else if (!trigger[3] && !trigger[4]){
  aile_dc = 48;
  }
  
  thro_dcCount++;   //toggle throttle pwm
  if (thro_dcCount <= thro_dc) {
  P1OUT |= BIT1;
  } else {
  P1OUT &= ~BIT1;
  }
  if (thro_dcCount == 100) {
  thro_dcCount = 0;
  }
  
  aile_dcCount++;   //toggle aile pwm
  if (aile_dcCount <= aile_dc) {
  P1OUT |= BIT2;
  } else {
  P1OUT &= ~BIT2;
  }
  if (aile_dcCount == 100) {
  aile_dcCount = 0;
  }
  
  elev_dcCount++;   //toggle elev pwm
  if (elev_dcCount <= elev_dc) {
  P1OUT |= BIT3;
  } else {
  P1OUT &= ~BIT3;
  }
  if (elev_dcCount == 100) {
  elev_dcCount = 0;
  }
  
  if (secondCount > 10) { //dead man's switch
  thro_dc = 37;
    state = 0;
  }
  } 
  //-------------------------------------------------------------------------------------------------------------// 