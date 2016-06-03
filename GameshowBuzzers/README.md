#Brian's Arduino Gameshow Buzzers

[Brian's Arduino Gameshow Buzzers][project] is an Open Source hardware and software design for building gameshow buzzers based around an Arduino-compatible microprocessor. These buzzers let up to 3 people race to answer a question first; the first person to hit their buzzer will “lock out” the other two from answering. The moderator then has a reset button to unlock the system for the next question.

This project is copyright 2016 by [Brian Enigma][briane] and licensed under [the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License][cclic].

[project]: https://github.com/BrianEnigma/Arduino/tree/master/GameshowBuzzers
[briane]: https://netninja.com/about/
[cclic]: http://creativecommons.org/licenses/by-nc-sa/4.0/

#Background

At my workplace, we have all-company Friday lunches. Often we will have a speaker giving a presentation — either someone from within the company or someone from the local community. Once, we had a silly game show. It was successful enough that we're bringing it back a second time, but this time with a little more planning and polish. The fellow running the gameshow project asked me if I might be able to build some gameshow-style lockout buzzers on the cheap. Aside from a spool of telephone cord, I had all the electronics parts and scrap wood from previous projects to create an effective buzz-in system.

#Description

TODO / PICTURES

#Materials

At its essence, you need the following parts:

- An Arduino. I used an older Diecimila, which doesn't have as much memory or as elegant hardware as the current-gen Uno R3. The software for a gameshow buzzer is dead-simple, and I was glad to finally find a home for this board.
- Three normally-open momentary pushbuttons. I used some older arcade buttons I found in a surplus store, which have a satisfying tactile click.
- A [strip of Neopixel](https://www.adafruit.com/categories/183) RGB LED lights. I had about 2ft leftover from a bar lighting project.
- Multiconductor wire, enough to stretch between the individual buttons (the contestants), and over to the controller (which has the reset button).

Optionally, you could also add:

- Nice enclosures for the buttons and lights.
- A nice enclosure or mount for the controller board and reset button.
- Screw-down terminal blocks for the multiconductor wire connections.

#Theory of Operation

**The Pushbuttons** each go from a digital pin on the Arduino to ground. We make use of the internal pull-up resistors on these pins so that no other special hardware is required.

**The LEDs** electrically form one single strip, segmented into three equal sections. For mine, I had 8 LEDs per player. This means that LEDs 1-8 are player one, 9-16 are player two, and 17-24 are player three.

**The Wiring** is up to you. I chained everything together so that the controller plugs into the player one unit (which carries the pushbutton wires for all three players). The player one unit then chains to the player two unit (which carries the pushbutton wires for itself and player three). And finally, the player two unit plugs into the player three unit (which only carries wires for its own pushbutton). All three player units carry power, ground, and the LED strip data connection. For more specific detail, please see [the schematic diagram PDF](./Hardware/schematic.pdf).




