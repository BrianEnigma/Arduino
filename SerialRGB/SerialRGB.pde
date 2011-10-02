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
  
  Serial.begin(9600);
}

void flushSerial()
{
  while (Serial.available() > 0)
    Serial.read();
}

int readNumber(const char *prompt)
{
  int result = 0;
  int ch = 0;
  unsigned char gotDigit = 0;
  flushSerial();
  Serial.print(prompt);
  while (1) {
    // Wait until serial data
    while (Serial.available() == 0)
      delay(100);
    ch = Serial.read();
    if (ch < 0)
      continue;
    // User typed a digit, so record it
    if (ch >= '0' && ch <= '9')
    {
      gotDigit = 1;
      result = result * 10 + ch - '0';
      Serial.print((char) ch);
    }
    // User hit return without entering a number -- reprint the prompt
    if (ch < ' ')
    {
      if (!gotDigit)
      {
        Serial.println();
        Serial.print(prompt);
      }
      if (gotDigit)
      {
        flushSerial();
        break;
      }
    }
  }
  Serial.println();
  return result;
}

void loop() {
  int r = 0, g = 0, b = 0;
  r = readNumber("Red value: ");
  g = readNumber("Green value: ");
  b = readNumber("Blue value: ");
  Serial.print("("); Serial.print(r); Serial.print(","); Serial.print(g); Serial.print(","); Serial.print(b); Serial.println(")");
  analogWrite(REDPIN1, r);
  analogWrite(REDPIN2, r);
  analogWrite(GREENPIN1, g);
  analogWrite(GREENPIN2, g);
  analogWrite(BLUEPIN1, b);
  analogWrite(BLUEPIN2, b);
}

