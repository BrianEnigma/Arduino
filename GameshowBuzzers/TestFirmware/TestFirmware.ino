#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
const unsigned char PLAYER_PIN[3] = {3, 4, 5};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, LED_PIN, NEO_GRB + NEO_KHZ800);

void clearStrip()
{
    for (int i = 0; i < 24; i++)
        strip.setPixelColor(i, 0);
    strip.show();
}

void testAnimation()
{
    unsigned long long COLORS[] = {0xff0000, 0x00ff00, 0x0000ff, 0xffffff, 0x000000};
    for (int color = 0; color < 5; color++)
    {
        for (int i = 0; i < 24; i++)
        {
            strip.setPixelColor(i, COLORS[color]);
            strip.show();
            delay(20);
        }
    }
    clearStrip();
}

void setup() {
    for (int player = 0; player < 3; player++)
        pinMode(PLAYER_PIN[player], INPUT_PULLUP);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    testAnimation();
}

void showWinAnimation(int playerNumber)
{
    unsigned long long COLORS[] = {0x00ff00, 0x000000};
    for (int color = 0; color < 2; color++)
    {
        for (int i = 0; i < 4; i++)
        {
            strip.setPixelColor(8 * playerNumber + i, COLORS[color]);
            strip.setPixelColor(8 * (playerNumber + 1) - i - 1, COLORS[color]);
            strip.show();
            delay(30);
        }
    }
}

void loop() {
    for (int player = 0; player < 3; player++)
    {
        if (!digitalRead(PLAYER_PIN[player]))
        {
            showWinAnimation(player);
        }
    }
}

