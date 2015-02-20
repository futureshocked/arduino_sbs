/**
 * Narcoleptic - A sleep library for Arduino
 * Copyright (C) 2010 Peter Knight (Cathedrow)
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

/*
** Welcome to Narcoleptic. This library allows you to dramatically reduce
** the power consumption of your Arduino project.
**
** Whilst in a Narcoleptic delay, the CPU current consumption drops from
** around 15mA down to about 7µA.
**
** Note that Narcoleptic only shuts down the CPU. It does not shut down
** anything else consuming current - LEDs, or the USB to serial chip.
** For low current applications, consider using boards without those,
** such as the Sparkfun Arduino Pro with the power LED removed.
**
** Narcoleptic is available from: http://narcoleptic.googlecode.com
*/

/* To use Narcoleptic, you will need the following line. Arduino will
** auto-insert it if you select Sketch > Import Library > Narcoleptic. */

#include <Narcoleptic.h>

void setup() {
  pinMode(2,INPUT);
  digitalWrite(2,HIGH);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}

void loop() {

  // Going to sleep. Connect digital pin 2 to ground to wake up.
  Narcoleptic.delay(10000); // During this time power consumption is minimised
                            // Longest delay I achieved is 32767msec due to
                            // the signed integer capacity of the delay function
  while (digitalRead(2) == LOW) {
    // Wake up CPU.
    digitalWrite(13,HIGH);
    delay(5000);
    digitalWrite(13,LOW);
    delay(5000);
  }
  // Back to sleep
}
