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
  pinMode(BUTTONPIN, INPUT);
  digitalWrite(BUTTONPIN, HIGH);
  
  pinMode(REDPIN1, OUTPUT);
  pinMode(GREENPIN1, OUTPUT);
  pinMode(BLUEPIN1, OUTPUT);
  pinMode(REDPIN2, OUTPUT);
  pinMode(GREENPIN2, OUTPUT);
  pinMode(BLUEPIN2, OUTPUT);

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
      // Fade string one from green to black to red
      fadeBetween(1, 0, 128, 0, 0, 0, 0, XMAS_STEP_VALUE, XMAS_STEP_DELAY);
      fadeBetween(1, 0, 0, 0, 128, 0, 0, XMAS_STEP_VALUE, XMAS_STEP_DELAY);
      // Fade string two from green to black to red
      fadeBetween(2, 0, 128, 0, 0, 0, 0, XMAS_STEP_VALUE, XMAS_STEP_DELAY);
      fadeBetween(2, 0, 0, 0, 128, 0, 0, XMAS_STEP_VALUE, XMAS_STEP_DELAY);
    //}
  }
}

void loop() {
  loopXmas();
}

