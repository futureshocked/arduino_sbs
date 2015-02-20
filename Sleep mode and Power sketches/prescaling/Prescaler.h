
/*
 * prescaler.h
 *
 * Provides useful tools to manage the clock prescaler and issues
 * related to time and delays. Allows to easily set the prescaler
 * and get access to its value. Also provides alternative functions
 * to the millis() and delay() functions.
 * 
 * (c) 2008 Sofian Audry | info(@)sofianaudry(.)com
 * http://sofianaudry.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef PRESCALER_INC
#define PRESCALER_INC

#include "Arduino.h"

/**
 * Prescaler division 
*/
#define CLOCK_PRESCALER_1   (0x0)
#define CLOCK_PRESCALER_2   (0x1)
#define CLOCK_PRESCALER_4   (0x2)
#define CLOCK_PRESCALER_8   (0x3)
#define CLOCK_PRESCALER_16  (0x4)
#define CLOCK_PRESCALER_32  (0x5)
#define CLOCK_PRESCALER_64  (0x6)
#define CLOCK_PRESCALER_128 (0x7)
#define CLOCK_PRESCALER_256 (0x8)

// Initialize global variable.
static uint8_t __clock_prescaler = (CLKPR & (_BV(CLKPS0) | _BV(CLKPS1) | _BV(CLKPS2) | _BV(CLKPS3)));

inline void setClockPrescaler(uint8_t clockPrescaler) {
  if (clockPrescaler <= CLOCK_PRESCALER_256) {
    // Disable interrupts.
    uint8_t oldSREG = SREG;
    cli();

    // Enable change.
    CLKPR = _BV(CLKPCE); // write the CLKPCE bit to one and all the other to zero

    // Change clock division.
    CLKPR = clockPrescaler; // write the CLKPS0..3 bits while writing the CLKPE bit to zero

    // Copy for fast access.
    __clock_prescaler = clockPrescaler;

    // Recopy interrupt register.
    SREG = oldSREG;
  }
}

inline uint8_t getClockPrescaler() {
  return (__clock_prescaler);
}

inline uint16_t getClockDivisionFactor() {
  return ((uint16_t)(1 << __clock_prescaler));
}

/**
 * Time in milliseconds.
 *
 * NOTE: This is the equivalent of the millis() function but it readjusts it according
 * to the current clock division. As such, be careful of how you make use of it, in
 * particular remember it will be wrong if the clock division factor is changed during the
 * course of computation. Remember that you can reset the overflow counter by calling the
 * init() function from wiring.h.
 */
inline unsigned long trueMillis()
{
  return millis() * getClockDivisionFactor();
}

// Waits for #ms# milliseconds.
// NOTE: Please see comment above.
inline void trueDelay(unsigned long ms)
{
  unsigned long start = trueMillis();
  while (trueMillis() - start < ms);
}

/**
 * Rescales given delay time according to division factor. Should be called before a call 
 * to delay(). Insures compatibility with function using delay().
 * Example use:
 * delay( rescaleDelay(1000) ); // equivalent to wait(1000)
 */
inline unsigned long rescaleDuration(unsigned long d) {
  return (d / getClockDivisionFactor());
}

/**
 * Rescales given time (in milliseconds or microseconds) according to division factor. Should
 * be called 
 */
inline unsigned long rescaleTime(unsigned long t) {
  return (t * getClockDivisionFactor());
}

#endif
