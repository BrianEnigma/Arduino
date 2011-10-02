# README

This is a random collection of little Arduino projects I've been working on.

## Simplistic
 - ButtonBlink :: Pushing the button (debounced) toggles the blink rate of the LED on pin 13.

## RGB LED Strip
These use a pair of flexible LED strips (from Adafruit <http://www.adafruit.com/products/285>) wired via MOSFETS (see <http://www.ladyada.net/products/rgbledstrip/#usage>) to PWM pins 3, 5, and 6 for the one string and PWM pins 9, 10, and 11 for the other).

 - DualRGBInterface :: The hardware interface between the Arduino, Proto Shield, and two strings of LED lights.

 - MultiRGB :: Cycle between colors.  This is the example program for the string of RGB LEDs, but modified to work against my dual-strings.
 - MultiRGB2 :: More fancy cycle between colors, Halloween themed -- reds, oranges, greens, purples.
 - SerialRGB :: Take an integer red, green, and blue value from the serial port and set the LED colors based on that.  Useful for choosing and fine-tuning colors.

