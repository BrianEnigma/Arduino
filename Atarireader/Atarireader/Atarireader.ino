void setup()
{
    // Set up address pins
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    // Set up data pins
    pinMode(8, INPUT);
    pinMode(7, INPUT);
    pinMode(6, INPUT);
    pinMode(5, INPUT);
    pinMode(4, INPUT);
    pinMode(3, INPUT);
    pinMode(2, INPUT);
    // Skip D1 so that we can use it as TX
    pinMode(0, INPUT);
    // Set up serial output for writing data bytes
    Serial.begin(9600);
    // Delay so we can hook up the serial monitor
    for (int seconds = 10; seconds >= 0; seconds--)
    {
        Serial.print("Delaying... ");
        Serial.println(seconds);
        delay(1000);
    }
    Serial.println("START");
}

const int addressLines[] = 
{
    A0,A1,A2,A3,A4,A5,13,12,11,10,9
};

const int dataLines[] = 
{
    8,7,6,5,4,3,2,0
};

unsigned char readByte(unsigned int address)
{
    unsigned char result = 0;
    // Push address bytes
    for (unsigned char bitCounter = 0; bitCounter < 11; bitCounter++)
    {
        digitalWrite(addressLines[bitCounter], address & 0x01);
        address >>= 1;
    }
    // Delay a bit to allow the ROM to stabilize
    delay(10);
    // Read data bytes
    for (unsigned char bitCounter = 0; bitCounter < 8; bitCounter++)
    {
        result = (result << 1) | digitalRead(dataLines[bitCounter]);
    }
    return result;
}

const unsigned int MAX_ADDRESS = 1024;
const unsigned int MAX_BLOCK = MAX_ADDRESS / 16;

void loop()
{
    unsigned int address;
    unsigned char dataByte;
#if 0
    // Print the first 32 bytes
   for (address = 0; address < 32; address++)
   {
     Serial.print(address, 16);
     Serial.print(" ");
     dataByte = readByte(address);
     Serial.println(dataByte, 16);
   }
#else
    address = 0;
    for (unsigned int block = 0; block < MAX_BLOCK; block++)
    {
        Serial.print("0x");
        Serial.print(address, 16);
        Serial.print("\t");
        for (unsigned int offset = 0; offset < 16; offset++)
        {
          dataByte = readByte(address);
          if (dataByte <= 0x0F)
              Serial.print("0");
          Serial.print(dataByte, 16);
          address++;
        }
        Serial.println("");
    }
#endif    
    Serial.println("END");
    // Wait 5 seconds before repeating
    for (unsigned int counter = 0; counter < 5; counter++)
    {
        delay(1000);
    }
}

