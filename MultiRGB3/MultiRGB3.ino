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
 
unsigned char string1ColorCurrent[3];
unsigned char string2ColorCurrent[3];
unsigned char string1ColorDestination[3];
unsigned char string2ColorDestination[3];
unsigned char string1ColorStep[3];
unsigned char string2ColorStep[3];

#define STEP_VALUE 1
#define POWER_ON_DELAY_VALUE 5
#define DELAY_VALUE 20
#define PAUSE 8000
#define MAX_COLOR 128

void setup() {
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

  // Start both black
  string1ColorCurrent[0] = 0; string1ColorCurrent[1] = 0; string1ColorCurrent[2] = 0;
  string2ColorCurrent[0] = 0; string2ColorCurrent[1] = 0; string2ColorCurrent[2] = 0;
  // Fade to one red, one green
  string1ColorDestination[0] = MAX_COLOR; string1ColorDestination[1] = 0; string1ColorDestination[2] = 0;
  string2ColorDestination[0] = 0; string2ColorDestination[1] = MAX_COLOR; string2ColorDestination[2] = 0;
  // Step toward
  string1ColorStep[0] = 1; string1ColorStep[1] = 1; string1ColorStep[2] = 1;
  string2ColorStep[0] = 1; string2ColorStep[1] = 1; string2ColorStep[2] = 1;
  
  Serial.begin(9600);
}

unsigned char fadeStep()
{
  unsigned char somethingChanged = 0;
  int i;
  // Step toward the destination colors
  for (i = 0; i < 3; i++)
    if (string1ColorCurrent[i] != string1ColorDestination[i])
    {
      string1ColorCurrent[i] += string1ColorStep[i];
      somethingChanged = 1;
    }
  for (i = 0; i < 3; i++)
    if (string2ColorCurrent[i] != string2ColorDestination[i])
    {
      string2ColorCurrent[i] += string2ColorStep[i];
      somethingChanged = 1;
    }
  analogWrite(REDPIN1, string1ColorCurrent[0]);
  analogWrite(GREENPIN1, string1ColorCurrent[1]);
  analogWrite(BLUEPIN1, string1ColorCurrent[2]);
  analogWrite(REDPIN2, string2ColorCurrent[0]);
  analogWrite(GREENPIN2, string2ColorCurrent[1]);
  analogWrite(BLUEPIN2, string2ColorCurrent[2]);
  return somethingChanged;
}

void loop() {
  while (fadeStep())
  {
    delay(POWER_ON_DELAY_VALUE);
  }
  delay(PAUSE);
  while (1)
  {
    // Fade to green/red
    string1ColorDestination[0] = 0; string1ColorDestination[1] = MAX_COLOR; string1ColorDestination[2] = 0;
    string2ColorDestination[0] = MAX_COLOR; string2ColorDestination[1] = 0; string2ColorDestination[2] = 0;
    // Step toward in the correct direction
    string1ColorStep[0] = -1 * STEP_VALUE; string1ColorStep[1] = STEP_VALUE; string1ColorStep[2] = STEP_VALUE;
    string2ColorStep[0] = STEP_VALUE; string2ColorStep[1] = -1 * STEP_VALUE; string2ColorStep[2] = STEP_VALUE;
    while (fadeStep())
    {
      delay(DELAY_VALUE);
    }
    delay(PAUSE);
    // Fade to green/red
    string1ColorDestination[0] = MAX_COLOR; string1ColorDestination[1] = 0; string1ColorDestination[2] = 0;
    string2ColorDestination[0] = 0; string2ColorDestination[1] = MAX_COLOR; string2ColorDestination[2] = 0;
    // Step toward in the correct direction
    string1ColorStep[0] = STEP_VALUE; string1ColorStep[1] = -1 * STEP_VALUE; string1ColorStep[2] = STEP_VALUE;
    string2ColorStep[0] = -1 * STEP_VALUE; string2ColorStep[1] = STEP_VALUE; string2ColorStep[2] = STEP_VALUE;
    while (fadeStep())
    {
      delay(DELAY_VALUE);
    }
    delay(PAUSE);
  }
}

