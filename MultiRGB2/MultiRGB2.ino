#if 0 // little string
#define REDPIN1 3
#define GREENPIN1 6
#define BLUEPIN1 5
#define REDPIN2 9
#define GREENPIN2 11
#define BLUEPIN2 10
#else // front porch string
#define REDPIN1 3
#define GREENPIN1 5
#define BLUEPIN1 6
#define REDPIN2 9
#define GREENPIN2 10
#define BLUEPIN2 11
#endif

#define BUTTONPIN 0
 
#define FADESPEED 5     // make this higher to slow down
 
void setup() {
  randomSeed(analogRead(0));
  pinMode(BUTTONPIN, INPUT);
  digitalWrite(BUTTONPIN, HIGH);
  
  pinMode(REDPIN1, OUTPUT);
  pinMode(GREENPIN1, OUTPUT);
  pinMode(BLUEPIN1, OUTPUT);
  pinMode(REDPIN2, OUTPUT);
  pinMode(GREENPIN2, OUTPUT);
  pinMode(BLUEPIN2, OUTPUT);

  digitalWrite(REDPIN1, LOW);
  digitalWrite(REDPIN2, LOW);
  digitalWrite(GREENPIN1, LOW);
  digitalWrite(GREENPIN2, LOW);
  digitalWrite(BLUEPIN1, LOW);
  digitalWrite(BLUEPIN2, LOW);

  analogWrite(REDPIN1, 0);
  analogWrite(REDPIN2, 0);
  analogWrite(GREENPIN1, 0);
  analogWrite(GREENPIN2, 0);
  analogWrite(BLUEPIN1, 0);
  analogWrite(BLUEPIN2, 0);
  
  Serial.begin(9600);
}

void checkButton()
{
  while (!digitalRead(BUTTONPIN))
  {
    unsigned char red = 255;
    unsigned char green = 255;
    unsigned char blue = 255;
    analogWrite(REDPIN1, red);
    analogWrite(REDPIN2, red);
    analogWrite(GREENPIN1, green);
    analogWrite(GREENPIN2, green);
    analogWrite(BLUEPIN1, blue);
    analogWrite(BLUEPIN2, blue);
    
  }
}

void fadeBetween(int stringNumber,
                 int red1, 
                 int green1, 
                 int blue1, 
                 int red2, 
                 int green2, 
                 int blue2,
                 unsigned char stepValue,
                 unsigned char sleepValue)
{
  //Serial.print("1: "); Serial.print(red1); Serial.print(","); Serial.print(green1); Serial.print(","); Serial.print(blue1); Serial.println("");
  //Serial.print("2: "); Serial.print(red2); Serial.print(","); Serial.print(green2); Serial.print(","); Serial.print(blue2); Serial.println("");
  while ((red1 != red2) || (green1 != green2) || (blue1 != blue2))
  {
    //Serial.print("1l: "); Serial.print(red1); Serial.print(","); Serial.print(green1); Serial.print(","); Serial.print(blue1); Serial.println("");
    //Serial.print("2l: "); Serial.print(red2); Serial.print(","); Serial.print(green2); Serial.print(","); Serial.print(blue2); Serial.println("");
    // Step the red
    if (red1 < red2 - stepValue)
      red1 += stepValue;
    else if (red1 > red2 + stepValue)
      red1 -= stepValue;
    else if (abs(red1 - red2) <= stepValue)
      red1 = red2;
    // Step the green
    if (green1 < green2 - stepValue)
      green1 += stepValue;
    else if (green1 > green2 + stepValue)
      green1 -= stepValue;
    else if (abs(green1 - green2) <= stepValue)
      green1 = green2;
    // Step the blue
    if (blue1 < blue2 - stepValue)
      blue1 += stepValue;
    else if (blue1 > blue2 + stepValue)
      blue1 -= stepValue;
    else if (abs(blue1 - blue2) <= stepValue)
      blue1 = blue2;
    if (1 == stringNumber || 3 == stringNumber)
    {
      analogWrite(REDPIN1, red1);
      analogWrite(GREENPIN1, green1);
      analogWrite(BLUEPIN1, blue1);
    }
    if (2 == stringNumber || 3 == stringNumber) 
    {
      analogWrite(REDPIN2, red1);
      analogWrite(GREENPIN2, green1);
      analogWrite(BLUEPIN2, blue1);
    }
    delay(sleepValue);
    checkButton();
  }
}

#if 1
#define STEP_VALUE 1
#define DELAY_VALUE 50

void loopHalloween()
{
  unsigned char i;
  Serial.println("Going from black to red");
  fadeBetween(3, 0, 0, 0, 128, 0, 0, STEP_VALUE, 50);
  while (1)
  {
    for (i = 0; i < 10; i++)
    {
      Serial.println("Going to orange");
      fadeBetween(3, 128, 0, 0, 128, 15, 0, STEP_VALUE, 1000);
      delay(1000);
      Serial.println("Going to red");
      fadeBetween(3, 128, 15, 0, 128, 0, 0, STEP_VALUE, 1000);
      delay(1000);
    }
    fadeBetween(3, 128, 0, 0, 0, 64, 0, STEP_VALUE, 1000);
    for (i = 0; i < 10; i++)
    {
      Serial.println("Going to violet");
      fadeBetween(3, 0, 64, 0, 64, 0, 0, STEP_VALUE, 1000);
      fadeBetween(3, 64, 0, 0, 64, 0, 64, STEP_VALUE, 1000);
      delay(1000);
      Serial.println("Going to green");
      fadeBetween(3, 64, 0, 64, 64, 0, 0, STEP_VALUE, 1000);
      fadeBetween(3, 64, 0, 0, 0, 64, 0, STEP_VALUE, 1000);
      delay(1000);
    }
    fadeBetween(3, 0, 64, 0, 128, 0, 0, STEP_VALUE, 1000);
  }
}

#define XMAS_STEP_VALUE 1
#define XMAS_STEP_DELAY 15

void loopXmas()
{
  //unsigned char i;
  Serial.println("Going from black to red");
  fadeBetween(3, 0, 0, 0, 128, 0, 0, XMAS_STEP_VALUE, XMAS_STEP_DELAY);
  while (1)
  {
    //Serial.println("Red/Green Alternate");
    //for (i = 0; i < 10; i++)
    //{
      // Fade string one from red to black to green
      fadeBetween(1, 128, 0, 0, 0, 0, 0, XMAS_STEP_VALUE, XMAS_STEP_DELAY);
      fadeBetween(1, 0, 0, 0, 0, 128, 0, XMAS_STEP_VALUE, XMAS_STEP_DELAY);
      // Fade string two from red to black to green
      fadeBetween(2, 128, 0, 0, 0, 0, 0, XMAS_STEP_VALUE, XMAS_STEP_DELAY);
      fadeBetween(2, 0, 0, 0, 0, 128, 0, XMAS_STEP_VALUE, XMAS_STEP_DELAY);
      // Pause
      delay(5000);
      // Fade string one from green to black to red
      fadeBetween(1, 0, 128, 0, 0, 0, 0, XMAS_STEP_VALUE, XMAS_STEP_DELAY);
      fadeBetween(1, 0, 0, 0, 128, 0, 0, XMAS_STEP_VALUE, XMAS_STEP_DELAY);
      // Fade string two from green to black to red
      fadeBetween(2, 0, 128, 0, 0, 0, 0, XMAS_STEP_VALUE, XMAS_STEP_DELAY);
      fadeBetween(2, 0, 0, 0, 128, 0, 0, XMAS_STEP_VALUE, XMAS_STEP_DELAY);
      delay(5000);
    //}
  }
}
#endif

#define RED_STEP_VALUE 1
#define RED_STEP_DELAY 60
void loopRed()
{
  Serial.println("Going from black to red");
  // All red
  fadeBetween(3, 0, 0, 0, 96, 0, 0, RED_STEP_VALUE, RED_STEP_DELAY);
  while (1)
  {
    // Dim
    fadeBetween(3, 96, 0, 0, 16, 0, 0, RED_STEP_VALUE, RED_STEP_DELAY);
    // Brighten
    fadeBetween(3, 16, 0, 0, 96, 0, 0, RED_STEP_VALUE, RED_STEP_DELAY);
  }
}

#define GREEN_STEP_VALUE 1
#define GREEN_STEP_DELAY 60
void loopGreen()
{
  Serial.println("Going from black to red");
  // All red
  fadeBetween(3, 0, 0, 0, 0, 96, 0, GREEN_STEP_VALUE, GREEN_STEP_DELAY);
  while (1)
  {
    // Dim
    fadeBetween(3, 0, 96, 0, 0, 16, 0, GREEN_STEP_VALUE, GREEN_STEP_DELAY);
    // Brighten
    fadeBetween(3, 0, 16, 0, 0, 96, 0, GREEN_STEP_VALUE, GREEN_STEP_DELAY);
  }
}

#define RV_STEP_VALUE 1
#define RV_STEP_DELAY 60
#define RV_MAX 64
#define RV_MIN 8
void loopRedViolet()
{
  // Bright red
  fadeBetween(3, 0, 0, 0, RV_MAX, 0, 0, RV_STEP_VALUE, RV_STEP_DELAY);
  while (1)
  {
    // Dim red
    fadeBetween(3, RV_MAX, 0, 0, RV_MIN, 0, 0, RV_STEP_VALUE, RV_STEP_DELAY);
    // Bright purple red
    fadeBetween(3, RV_MIN, 0, 0, RV_MAX, 0, RV_MAX, RV_STEP_VALUE, RV_STEP_DELAY);
    // Dim purple red
    fadeBetween(3, RV_MAX, 0, RV_MAX, RV_MIN, 0, RV_MIN, RV_STEP_VALUE, RV_STEP_DELAY);
    // Bright red
    fadeBetween(3, RV_MIN, 0, RV_MIN, RV_MAX, 0, 0, RV_STEP_VALUE, RV_STEP_DELAY);
  }
}

#define RWB_STEP_VALUE 1
#define RWB_STEP_DELAY 30
#define RWB_MAX 32
#define RWB_MIN 8
void loopRedWhiteBlue()
{
  // Red
  fadeBetween(3, 0, 0, 0, RWB_MAX, 0, 0, RWB_STEP_VALUE, RWB_STEP_DELAY);
  while (1)
  {
    // White
    fadeBetween(3, RWB_MAX, 0, 0, RWB_MAX, RWB_MAX, RWB_MAX, RWB_STEP_VALUE, RWB_STEP_DELAY);
    delay(3000);
    // Blue
    fadeBetween(3, RWB_MAX, RWB_MAX, RWB_MAX, 0, 0, RWB_MAX, RWB_STEP_VALUE, RWB_STEP_DELAY);
    delay(3000);
    // Red
    fadeBetween(3, 0, 0, RWB_MAX, RWB_MAX, 0, 0, RWB_STEP_VALUE, RWB_STEP_DELAY);
    delay(3000);
  }
}

#define GREEN_RAND_STEP_VALUE 1
#define GREEN_RAND_STEP_DELAY 60
void loopRandomGreen()
{
    unsigned int r1 = 0, g1 = 0, b1 = 0;
    unsigned int r2 = 0, g2 = 96, b2 = 0;
    Serial.println("Going from black to green");
    // All red
    fadeBetween(3, r1, g1, b1, r2, g2, b2, GREEN_RAND_STEP_VALUE, GREEN_RAND_STEP_DELAY);
    while (1)
    {
        r1 = r2; g1 = g2; b1 = b2;
        g2 = random(48, 96);
        r2 = random(0, g2 / 3);
        b2 = random(0, g2 / 3);
		Serial.print(r2); Serial.print(","); Serial.print(g2); Serial.print(","); Serial.print(b2); Serial.println("");
        fadeBetween(3, r1, g1, b1, r2, g2, b2, GREEN_RAND_STEP_VALUE, GREEN_RAND_STEP_DELAY);
        delay(2000);
    }
}

#define BLUE_STEP_VALUE 1
#define BLUE_STEP_DELAY 30
void loopBlueWhite()
{
  Serial.println("Going from black to red");
  // All red
  fadeBetween(3, 0, 0, 0, 0, 0, 64, BLUE_STEP_VALUE, BLUE_STEP_DELAY);
  while (1)
  {
    // Dim
    fadeBetween(3,  0,  0, 64,  0,  0, 32, BLUE_STEP_VALUE, BLUE_STEP_DELAY);
    fadeBetween(3,  0,  0, 32, 32, 32, 32, BLUE_STEP_VALUE, BLUE_STEP_DELAY);
    delay(2000);
    // Brighten
    fadeBetween(3, 32, 32, 32,  0,  0, 32, BLUE_STEP_VALUE, BLUE_STEP_DELAY);
    fadeBetween(3,  0,  0, 32,  0,  0, 64, BLUE_STEP_VALUE, BLUE_STEP_DELAY);
    delay(5000);
  }
}

void loopBlue()
{
  Serial.println("Going from black to red");
  // All red
  fadeBetween(3, 0, 0, 0, 0, 0, 64, BLUE_STEP_VALUE, BLUE_STEP_DELAY);
  while (1)
  {
    // Dim
    fadeBetween(3,  0,  0, 64,  0,  0, 32, BLUE_STEP_VALUE, BLUE_STEP_DELAY);
    delay(2000);
    // Brighten
    fadeBetween(3,  0,  0, 32,  0,  0, 64, BLUE_STEP_VALUE, BLUE_STEP_DELAY);
    delay(2000);
  }
}

void loop() {
    //loopRedWhiteBlue();
    //loopRed();
    //loopRedViolet();
    //loopHalloween();
    //loopBlueWhite();
    //loopBlue();
    //loopGreen();
    //loopRandomGreen();
    loopXmas();
}
