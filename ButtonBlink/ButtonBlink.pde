/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(13, OUTPUT);   
  pinMode(8, INPUT);
  digitalWrite(8, HIGH);
}

int delayValue = 10;
int buttonState = 0;
int pressed = 0;
unsigned long pressedTime = 0;

void loop() {

  buttonState = digitalRead(8);
  if (buttonState && !pressed)
  {
    pressedTime = millis();
    pressed = 1;
    Serial.println("Press started");
  } else if (!buttonState && pressed) {
    Serial.println("Press released");
    if (millis() - pressedTime >= 500)
    {
      Serial.println("Toggled");
      if (10 == delayValue)
        delayValue = 2;
      else
        delayValue = 10;
    }
    pressed = 0;
    pressedTime = 0;
  }
  
  digitalWrite(13, HIGH);   // set the LED on
  delay(delayValue * 100);  // wait for a second
  digitalWrite(13, LOW);    // set the LED off
  delay(delayValue * 100);  // wait for a second
}
