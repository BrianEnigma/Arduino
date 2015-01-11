#include <Bounce.h>
#include <Adafruit_NeoPixel.h>

#define BUTTON_UP 2
#define BUTTON_DOWN 3
#define BUTTON_LEFT 4
#define BUTTON_RIGHT 5
#define NEOPIXELS 6
#define NEOPIXEL_COUNT 40
#define LED 13

Bounce bouncerUp = Bounce(BUTTON_UP, 5); 
Bounce bouncerDown = Bounce(BUTTON_DOWN, 5); 
Bounce bouncerLeft = Bounce(BUTTON_LEFT, 5); 
Bounce bouncerRight = Bounce(BUTTON_RIGHT, 5); 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEOPIXEL_COUNT, NEOPIXELS, NEO_GRB + NEO_KHZ800);

void lightsOut()
{
    uint32_t color = strip.Color(0, 0, 0);
    for (uint16_t pixel = 0; pixel < NEOPIXEL_COUNT; pixel++) 
        strip.setPixelColor(pixel, color);
    strip.show();
}

void setup() {
    pinMode(BUTTON_UP, INPUT_PULLUP);
    pinMode(BUTTON_DOWN, INPUT_PULLUP);
    pinMode(BUTTON_LEFT, INPUT_PULLUP);
    pinMode(BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(LED,OUTPUT);
//  Serial.begin(9600);
//  strip.show(); // Initialize all pixels to 'off'
    randomSeed(analogRead(0));
    strip.begin();
    lightsOut();
}

#define MODE_OFF     0
#define MODE_WHITE   1
#define MODE_RED     2
#define MODE_GREEN   3
#define MODE_BLUE    4
#define MODE_RANDOM  5
#define MODE_STRIPES 6
#define MODE_MAX     7
unsigned char g_mode = 0;
unsigned char g_previousMode = 255;
unsigned char g_brightness = 128;

/* ============================================================================ */

const unsigned char WHITE_STEP = 10;
void startWhite()
{
    uint32_t color;
    for (int value = 0; value <= g_brightness; value += WHITE_STEP)
    {
        color = strip.Color(value, value, value);
        for (uint16_t pixel = 0; pixel < NEOPIXEL_COUNT; pixel++) 
            strip.setPixelColor(pixel, color);
        strip.show();
        delay(10);
    }
}
void doWhite(bool up, bool down)
{
    uint32_t color;
    color = strip.Color(g_brightness, g_brightness, g_brightness);
    for (uint16_t pixel = 0; pixel < NEOPIXEL_COUNT; pixel++) 
        strip.setPixelColor(pixel, color);
    strip.show();
    if (up || down)
    {
        if (up)
            g_brightness += WHITE_STEP;
        else
            g_brightness -= WHITE_STEP;
        delay(100);
    } else
    {
        delay(100);
    }
}
void endWhite()
{
    uint32_t color;
    for (int value = g_brightness; value >= 0; value -= WHITE_STEP)
    {
        color = strip.Color(value, value, value);
        for (uint16_t pixel = 0; pixel < NEOPIXEL_COUNT; pixel++) 
            strip.setPixelColor(pixel, color);
        strip.show();
        delay(10);
    }
}

/* ============================================================================ */

const unsigned char RGB_STEP = 10;
void startRGB(unsigned char colorMode)
{
    uint32_t color;
    for (int value = 0; value <= g_brightness; value += WHITE_STEP)
    {
        color = strip.Color(1 == colorMode ? value : 0, 2 == colorMode ? value : 0, 3 == colorMode ? value : 0);
        for (uint16_t pixel = 0; pixel < NEOPIXEL_COUNT; pixel++) 
            strip.setPixelColor(pixel, color);
        strip.show();
        delay(10);
    }
}
void doRGB(bool up, bool down, unsigned char colorMode)
{
    uint32_t color;
    color = strip.Color(1 == colorMode ? g_brightness : 0, 2 == colorMode ? g_brightness : 0, 3 == colorMode ? g_brightness : 0);
    for (uint16_t pixel = 0; pixel < NEOPIXEL_COUNT; pixel++) 
        strip.setPixelColor(pixel, color);
    strip.show();
    if (up || down)
    {
        if (up)
            g_brightness += WHITE_STEP;
        else
            g_brightness -= WHITE_STEP;
        delay(100);
    } else
    {
        delay(100);
    }
}
void endRGB(unsigned char colorMode)
{
    uint32_t color;
    for (int value = g_brightness; value >= 0; value -= WHITE_STEP)
    {
        color = strip.Color(1 == colorMode ? value : 0, 2 == colorMode ? value : 0, 3 == colorMode ? value : 0);
        for (uint16_t pixel = 0; pixel < NEOPIXEL_COUNT; pixel++) 
            strip.setPixelColor(pixel, color);
        strip.show();
        delay(10);
    }
}

/* ============================================================================ */

uint32_t randomColors[NEOPIXEL_COUNT];
unsigned char randomCounter = 0;
void doOneRandomPixel(unsigned char pixel)
{
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            randomColors[pixel] = (randomColors[pixel] << 8) | (random(0, g_brightness) / (i == 49 ? 1 : 4));
        }
        strip.setPixelColor(pixel, strip.Color(
                            (randomColors[pixel] >> 16) & 0xFF,
                            (randomColors[pixel] >>  8) & 0xFF,
                            (randomColors[pixel]      ) & 0xFF));            
        strip.show();
        delay(30);
    }
}
void doAllRandomPixels()
{
    randomCounter = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int pixel = 0; pixel < NEOPIXEL_COUNT; pixel++)
        {
            for (int j = 0; j < 3; j++)
            {
                randomColors[pixel] = (randomColors[pixel] << 8) | (random(0, g_brightness) / (i == 49 ? 1 : 4));
            }
            strip.setPixelColor(pixel, strip.Color(
                                (randomColors[pixel] >> 16) & 0xFF,
                                (randomColors[pixel] >>  8) & 0xFF,
                                (randomColors[pixel]      ) & 0xFF));            
        }
        strip.show();
        delay(1);
    }
}
void startRandom()
{
    doAllRandomPixels();
}
void doRandom(bool up, bool down)
{
    if (++randomCounter == 20)
    {
        doOneRandomPixel(random(0, NEOPIXEL_COUNT));
        randomCounter = 0;
    } else {
        delay(100);
    }
    if (up || down)
    {
        if (up)
            g_brightness += WHITE_STEP;
        else
            g_brightness -= WHITE_STEP;
        doAllRandomPixels();
    }
}
void endRandom()
{
    doAllRandomPixels();
    for (uint16_t pixel = NEOPIXEL_COUNT - 2; pixel >= 1; pixel--)
    {
        randomColors[pixel] = 0;
        strip.setPixelColor(pixel, 0);
    }
    strip.show();
}

/* ============================================================================ */

unsigned int stripeCounter = 0;
const uint32_t RAINBOW[] = {0xFF0000,0xFF4000,0xFF8000,0xFFC000,0xFFFF00,0xAAFF00,0x55FF00,0x00FF00,0x00AA55,0x0055AA,0x0000FF,0x1900D4,0x3200AB,0x4B0082,0x6700C0,0x8F00FF};
void doStripes(bool up, bool down, bool doDelay)
{
    
    // TODO: scale based on g_brightness
    
    if (!doDelay || ++stripeCounter >= 20)
    {
        for (uint16_t pixel = NEOPIXEL_COUNT - 2; pixel >= 1; pixel--)
            strip.setPixelColor(pixel, strip.getPixelColor(pixel - 1));
        strip.setPixelColor(0, RAINBOW[random(0, 16)]);
        strip.show();
        stripeCounter = 0;
    }
    if (doDelay)
        delay(100);
}
void startStripes()
{
    for (uint16_t pixel = 0; pixel < NEOPIXEL_COUNT; pixel++) 
    {
        doStripes(false, false, false);
        delay(10);
    }
    stripeCounter = 0;
}
void endStripes()
{
    for (uint16_t pixel = 0; pixel < NEOPIXEL_COUNT; pixel++) 
    {
        for (uint16_t pixel = NEOPIXEL_COUNT - 2; pixel >= 1; pixel--)
            strip.setPixelColor(pixel, strip.getPixelColor(pixel - 1));
        strip.setPixelColor(0, 0);
        strip.show();
        delay(10);
    }
    stripeCounter = 0;
}

/* ============================================================================ */

bool stripVisible = false;
bool buttonUp = false;
bool buttonDown = false;
bool buttonLeft = false;
bool buttonRight = false;
void loop() 
{
    // Update the debouncer
    if (bouncerUp.update())
        if (bouncerUp.risingEdge())
            buttonUp = true;
    if (bouncerDown.update())
        if (bouncerDown.risingEdge())
            buttonDown = true;
    if (bouncerLeft.update())
        if (bouncerLeft.risingEdge())
            buttonLeft = true;
    if (bouncerRight.update())
        if (bouncerRight.risingEdge())
            buttonRight = true;
 
    if (buttonLeft)
        g_mode = (g_mode + MODE_MAX - 1) % MODE_MAX;
    if (buttonRight)
        g_mode = (g_mode + 1) % MODE_MAX;
    
    if (g_mode != g_previousMode)
    {
        switch(g_previousMode)
        {
        case MODE_OFF:          break;
        case MODE_WHITE:        endWhite(); break;
        case MODE_RED:          endRGB(1); break;
        case MODE_GREEN:        endRGB(2); break;
        case MODE_BLUE:         endRGB(3); break;
        case MODE_RANDOM:       endRandom(); break;
        case MODE_STRIPES:      endStripes(); break;
        }
        switch(g_mode)
        {
        case MODE_OFF:          break;
        case MODE_WHITE:        startWhite(); break;
        case MODE_RED:          startRGB(1); break;
        case MODE_GREEN:        startRGB(2); break;
        case MODE_BLUE:         startRGB(3); break;
        case MODE_RANDOM:       startRandom(); break;
        case MODE_STRIPES:      startStripes(); break;
        }
    }
    
    switch(g_mode)
    {
    case MODE_OFF:
        if (g_previousMode != g_mode)
            lightsOut();
        break;
    case MODE_WHITE:            doWhite(buttonUp, buttonDown); break;
    case MODE_RED:              doRGB(buttonUp, buttonDown, 1); break;
    case MODE_GREEN:            doRGB(buttonUp, buttonDown, 2); break;
    case MODE_BLUE:             doRGB(buttonUp, buttonDown, 3); break;
    case MODE_RANDOM:           doRandom(buttonUp, buttonDown); break;
    case MODE_STRIPES:          doStripes(buttonUp, buttonDown, true); break;
    }
 
    buttonUp = buttonDown = buttonLeft = buttonRight = false;
    g_previousMode = g_mode;
}

