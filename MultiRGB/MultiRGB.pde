// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
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
}

void checkButton()
{
  while (!digitalRead(BUTTONPIN))
  {
    unsigned char red = 0;
    unsigned char green = 255;
    unsigned char blue = 0;
    analogWrite(REDPIN1, red);
    analogWrite(REDPIN2, red);
    analogWrite(GREENPIN1, green);
    analogWrite(GREENPIN2, green);
    analogWrite(BLUEPIN1, blue);
    analogWrite(BLUEPIN2, blue);
    
  }
}
 
void loop() {
  int r, g, b;
 
  // fade from blue to violet
  for (r = 0; r < 256; r++) { 
    analogWrite(REDPIN1, r);
    analogWrite(REDPIN2, r);
    delay(FADESPEED);
    checkButton();
  }
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    analogWrite(BLUEPIN1, b);
    analogWrite(BLUEPIN2, b);
    delay(FADESPEED);
    checkButton();
  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    analogWrite(GREENPIN1, g);
    analogWrite(GREENPIN2, g);
    delay(FADESPEED);
    checkButton();
  } 
  // fade from yellow to green
  for (r = 255; r > 0; r--) { 
    analogWrite(REDPIN1, r);
    analogWrite(REDPIN2, r);
    delay(FADESPEED);
    checkButton();
  } 
  // fade from green to teal
  for (b = 0; b < 256; b++) { 
    analogWrite(BLUEPIN1, b);
    analogWrite(BLUEPIN2, b);
    delay(FADESPEED);
    checkButton();
  } 
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    analogWrite(GREENPIN1, g);
    analogWrite(GREENPIN2, g);
    delay(FADESPEED);
    checkButton();
  } 
}

