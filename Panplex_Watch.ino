// Define everything DHT
#include "DHT.h"
#define DHTPIN 10 // Pin DHT sensor connects to.
#define DHTTYPE DHT22 // Type of DHT sensor
DHT dht(DHTPIN, DHTTYPE); // Defining the DHT sensor varible.

// Define push button pins.
const int but1 = 11;
const int but2 = 12;

// Button state varible.
int but1state = 0;
int but2state = 0;

// Delay function using millis.
int period = 4000;
unsigned long time_now = 0;

// Define Arduino pins.
// Pins 2,3,4,5 declared in digitone.
// Pins 6,7,8,9 declared in digittwo.

// Display Enable pin.
int PWR = 14;

// Array To Drive Disaply.
char nibble[16][4] =
{
  {0, 0, 0, 0}, //0 0
  {1, 0, 0, 0}, //1 1
  {0, 1, 0, 0}, //2 2
  {1, 1, 0, 0}, //3 3
  {0, 0, 1, 0}, //4 4
  {1, 0, 1, 0}, //5 5
  {0, 1, 1, 0}, //6 6
  {1, 1, 1, 0}, //7 7
  {0, 0, 0, 1}, //8 8
  {1, 0, 0, 1}, //9 9
  {0, 1, 0, 1}, //A 10
  {1, 1, 0, 1}, //B 11
  {0, 0, 1, 1}, //C 12
  {1, 0, 1, 1}, //D 13
  {0, 1, 1, 1}, //E 14
  {1, 1, 1, 1}, //F 15
};

void setup()
{
  // Enables Arduino pins to output. Sets pin mode.
  // Pins 2,3,4,5 on Arduino.
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  // Pins 6,7,8,9 on Arduino.
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  // Arduino does not have the output power.
  // MOSFET/Transistor needed.
  pinMode(PWR, OUTPUT);
  digitalWrite(PWR, LOW);
  digitalWrite(but1, LOW);
  digitalWrite(but2, LOW);
  // Starts the DHT sensor.
  dht.begin();

}

void digitone(byte digit) //Loop that retreves data from array.
{
  byte zero_pin = 2; // Declares pins to be advanced by loop.
  for (byte bitCount = 0; bitCount < 4; ++bitCount) // Bitcount scans the nibble aka the X axis.
  {
    digitalWrite(zero_pin, nibble[digit][bitCount]); // Digit is the Y axis aka HEX in binary.
    ++zero_pin; // Advanced to the next one by this statment.
  }
}

void digittwo(byte digit) //Loop that retreves data from array.
{
  byte one_pin = 6; // Declares pins to be advanced by loop.
  for (byte bitCount = 0; bitCount < 4; ++bitCount)
  {
    digitalWrite(one_pin, nibble[digit][bitCount]);
    ++one_pin;
  }
}

void loop()
{
  // Reads buttons
  but1state = digitalRead(but1);
  but2state = digitalRead(but2);

  // React to button 1 press.
  if (but1state == HIGH) // If the button is pressed the code will take a humiderty reading & display.
  {
    time_now = millis(); // Current milliseconds count.
    while (millis() < time_now + period) // Millsecons to pass.
    {
      // Code to read humiderty from DHT sensor.
      int humi = dht.readHumidity();
      int tens;
      int ones;
      tens = humi / 10;
      ones = humi % 10;
      digitone(tens);
      digittwo(ones);
    }
  }
  else // Run temp code all the time.
  {
    // Code to read temp from DHT sensor.
    int temp = dht.readTemperature();
    int tens;
    int ones;
    tens = temp / 10;
    ones = temp % 10;
    digitone(tens);
    digittwo(ones);
  }

  // React to button 2 press.
  if (but2state == HIGH)
  {
    time_now = millis(); // Current milliseconds count.
    while (millis() < time_now + period) // Millsecons to pass.
    {
      digitone(6); // Sets digit to 6
      digittwo(9); // Sets digit to 9
    }
  }
  else
  {
    // Code to read temp from DHT sensor.
    int temp = dht.readTemperature();
    int tens;
    int ones;
    tens = temp / 10;
    ones = temp % 10;
    digitone(tens);
    digittwo(ones);
  }
}
