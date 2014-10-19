// Low power NeoPixel goggles example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!
 
#include <Adafruit_NeoPixel.h>
 
#define OUTPUT_PIN 4
#define BUTTON_PIN 0
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, OUTPUT_PIN);
 
uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t color  = 0xFF0000; // Start red
uint32_t prevTime;
 
void setup() 
{
    pinMode(BUTTON_PIN, INPUT);
    digitalWrite(BUTTON_PIN, HIGH); // activate pullup
    pixels.begin();
    pixels.setBrightness(85); // 1/3 brightness
    prevTime = millis();
}

uint32_t debounceTime = 0;            // debounce counter
unsigned char buttonState = 0;        // Current acknowledged button state
unsigned char lastButtonState = 0;    // Last read button state
unsigned char haveReturnedButton = 0; // Only return a TRUE value once

unsigned char switchPressed()
{
    unsigned char currentState = !digitalRead(BUTTON_PIN);
    if (currentState != lastButtonState)
    {
        debounceTime = millis();
    }
        
    if ((millis() - debounceTime) > 100)
    {
        if (currentState != buttonState)
        {
            buttonState = currentState;
            if (!buttonState)
                haveReturnedButton = 0;
        }
    }
    lastButtonState = currentState;

    if (buttonState && !haveReturnedButton)
    {
        haveReturnedButton = 1;
        return 1;
    }
    return 0;
}

unsigned char rainbowOffset = 0;
void rainbow()
{
    uint8_t i;
    uint32_t c;
    for (i = 0; i < 32; i++)
    {
        switch((i + rainbowOffset) % 16)
        {
            case 0:  c = 0xFF0000; break;
            case 1:  c = 0xFF4000; break;
            case 2:  c = 0xFF8000; break;
            case 3:  c = 0xFFC000; break;
            case 4:  c = 0xFFFF00; break;
            case 5:  c = 0xAAFF00; break;
            case 6:  c = 0x55FF00; break;
            case 7:  c = 0x00FF00; break;
            case 8:  c = 0x00AA55; break;
            case 9:  c = 0x0055AA; break;
            case 10: c = 0x0000FF; break;
            case 11: c = 0x1900D4; break;
            case 12: c = 0x3200AB; break;
            case 13: c = 0x4B0082; break;
            case 14: c = 0x6700C0; break;
            case 15: c = 0x8F00FF; break;
        }
        pixels.setPixelColor(i, c);
    }
    rainbowOffset = (rainbowOffset + 1) % 16;
    pixels.show();
}

unsigned char hasSetWhite = 0;
void loop() {
    uint8_t  i;
    //uint32_t t;

    if (switchPressed())
    {
        for(i = 0; i < 32; i++) 
            pixels.setPixelColor(i, 0);
        mode = (mode + 1) % 6;
    }

    switch(mode) {
    // Spinny wheels (8 LEDs on at a time)
    case 0:
    case 1:
    case 2:
        if (0 == mode)
            color = 0xFF0000;
        else if (1 == mode)
            color = 0x00FF00;
        else
            color = 0x0000FF;
        for(i = 0; i < 16; i++) 
        {
            uint32_t c = 0;
            if(((offset + i) & 7) < 2) 
                c = color; // 4 pixels on...
            pixels.setPixelColor(     i, c); // First eye
            pixels.setPixelColor(31 - i, c); // Second eye (flipped)
        }
        pixels.show();
        offset++;
        delay(50);
        break;
    case 3: //spinny rainbow
        rainbow();
        delay(50);
        break;
    case 4: //random colors
        for(i = 0; i < 32; i++) 
            pixels.setPixelColor(i, random(0xFFFFFF));
        pixels.show();
        delay(50);
        break;
        /*
    case 5:
        color = 0xFF0000;
        // todo: eye blink

        break;
    */
    case 5:
        if (!hasSetWhite)
        {
            for(i = 0; i < 32; i++) 
                pixels.setPixelColor(i, 0xFFFFFF);
            pixels.show();
            hasSetWhite = 1;
        }
        delay(50);
        break;
    }
    if (5 != mode)
        hasSetWhite = 0;
}
