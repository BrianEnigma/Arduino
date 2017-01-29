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
    //Serial.begin(9600);
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

// 30 seconds *------*  green
// 23 seconds .*----*.  yellow
// 16 seconds ..*--*..  orange
// 9 seconds  ...**...  red
// 0 seconds end animation

void do30SecondCountdown()
{
    unsigned long long COLORS[] = {
        0x00ff00, 0x00ff00, 0x00ff00, 0x00ff00,
        0x009900, 0x00ff00, 0x00ff00, 0x00ff00,
        
        0x000000, 0xffff00, 0xffff00, 0xffff00,
        0x000000, 0x999900, 0xffff00, 0xffff00,
        
        0x000000, 0x000000, 0xffa500, 0xffa500,
        0x000000, 0x000000, 0x995200, 0xffa500,
        
        0x000000, 0x000000, 0x000000, 0xff0000,
        0x000000, 0x000000, 0x000000, 0x990000
    };
    int countdown = 30;
    unsigned long nextSecond = millis() + 1000; // Can wrap after 50 days. Don't leave the buzzers plugged in for that long!
    bool resetButtonPushed = false;
    int resetButtonHitCount = 0;
    while (countdown > 0)
    {
        // Handle host hitting reset several times to cancel (in case this was triggered accidentally).
        resetButtonPushed = resetButtonPushed || digitalRead(HOST_RESET_PIN);
        if (resetButtonPushed && !digitalRead(HOST_RESET_PIN)) // no longer pushed
        {
            resetButtonPushed = false;
            resetButtonHitCount++;
            //Serial.println("Reset button pressed and released.\n");
        }
        if (resetButtonHitCount >= 3)
        {
            //Serial.println("Aborting countdown.\n");
            clearStrip();
            return;
        }

        // Figure out color pair
        int offset;
        if (countdown >= 23)
            offset = 0;
        else if (countdown >= 16)
            offset = 8;
        else if (countdown >= 9)
            offset = 16;
        else
            offset = 24;

        //Serial.print(countdown); Serial.print(" "); Serial.println(offset);

        // Do the animation.
        for (int animationOffset = 0; animationOffset <= 1; animationOffset++)
        {
            for (int playerNumber = 0; playerNumber < 3; playerNumber++)
            {
                for (int pos = 0; pos < 4; pos++)
                {
                    strip.setPixelColor(8 * playerNumber + pos, COLORS[offset + pos + 4 * animationOffset]);
                    strip.setPixelColor(8 * (playerNumber + 1) - pos - 1, COLORS[offset + pos + 4 * animationOffset]);
                }
            }
            strip.show();
            delay(100);
        }

        // Count time.
        if (millis() >= nextSecond)
        {
            countdown -= 1;
            nextSecond += 1000;
        }
    }
    for (int flashCount = 0; flashCount < 5; flashCount++)
    {
        for (int i = 0; i < 24; i++)
            strip.setPixelColor(i, 0xff0000);
        strip.show();
        delay(100);
        clearStrip();
        delay(100);
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
    {
        lockedInPlayer = -1;
        if (!digitalRead(HOST_ANIMATE_PIN))
        {
            //Serial.println("Both buttons pressed. Starting timer.");
            do30SecondCountdown();
        }
    }

    if (!digitalRead(HOST_ANIMATE_PIN))
    {
        while (!digitalRead(HOST_ANIMATE_PIN))
        {
            showHostAnimation();
        }
        clearStrip();
    }
}

