#include <Adafruit_NeoPixel.h>

#define LED_PIN 4
const unsigned char PLAYER_PIN[3] = {2, 3, 5};
#define HOST_RESET_PIN 6
#define HOST_ANIMATE_PIN 7

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

void showHostAnimation()
{
    unsigned long long COLORS[] = {0xff0000, 0x00ff00, 0x0000ff, 0xffffff};
    for (int color = 0; color < 4; color++)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int playerNumber = 0; playerNumber < 3; playerNumber++)
            {
                strip.setPixelColor(8 * playerNumber + i, COLORS[color]);
                strip.setPixelColor(8 * (playerNumber + 1) - i - 1, COLORS[color]);
                strip.show();
            }
            delay(30);
        }
    }
    clearStrip();
}

void setup() {
    for (int player = 0; player < 3; player++)
        pinMode(PLAYER_PIN[player], INPUT_PULLUP);
    pinMode(HOST_RESET_PIN, INPUT_PULLUP);
    pinMode(HOST_ANIMATE_PIN, INPUT_PULLUP);
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

int lockedInPlayer = -1;

void loop() 
{
    // Look for first player to buzz in.
    if (-1 == lockedInPlayer)
    {
        for (int player = 0; player < 3; player++)
        {
            if (!digitalRead(PLAYER_PIN[player]))
            {
                lockedInPlayer = player;
            }
        }
    }
    // Animate for locked-in player
    if (-1 != lockedInPlayer)
        showWinAnimation(lockedInPlayer);
    // Reset lock-in.
    if (!digitalRead(HOST_RESET_PIN))
        lockedInPlayer = -1;

    if (!digitalRead(HOST_ANIMATE_PIN))
    {
        while (!digitalRead(HOST_ANIMATE_PIN))
        {
            showHostAnimation();
        }
        clearStrip();
    }
}

