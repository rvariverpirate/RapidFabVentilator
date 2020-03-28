/*********
  BMP 280
  Complete project details at http://randomnerdtutorials.com
  Thanks to: https://randomnerdtutorials.com/esp8266-bme280-arduino-ide/
*********/

/* I2C LCD with Arduino example code. More info: https://www.makerguides.com */

// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// BMP 280 Initialization 
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27,16,2) for 16x2 LCD.

// Delay the loop
unsigned long delayTime;

// Need to Store our Sensor Data
// Sensor 1
float Temp1;
float Pressure1;
float Humidity1;
// Sensor 2
float Temp2;
float Pressure2;
float Humidity2;

// Need character Arrays for Row 1 and 2
char row1[100];
char row2[100];

void setup() {
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();

  // Setup Serial Communication
  Serial.begin(9600);
  Serial.println(F("BME280 test"));

  bool status;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    // Print 'Hello World!' on the first line of the LCD:
    lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
    lcd.print("BMP280 not detected"); // Print the string "Hello World!"
    lcd.setCursor(2, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
    lcd.print("Check Wiring");
    while (1);
  }

  Serial.println("-- Default Test --");
  delayTime = 250;
  Serial.println();
  
}

// The Main Loop
void loop() {
  // Get Sensor 1's Data
  Temp1 = bme.readTemperature();// (C)
  Pressure1 = bme.readPressure() / 100.0F;// (hPa)
  Humidity1 = bme.readHumidity();// (%)

  // Format data for Row 1
  sprintf(row1, "P=%.5f", Pressure1);

  // Format data for Row 1
  sprintf(row2, "H=%.2f, T=%.2f", Humidity1, Temp1);
  
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print(row1); // Print the string "Hello World!"
  lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  lcd.print(row2);

  // Print BMP Sensor data to Serial Port
  bmpSerialPrint(Temp1, Pressure1, Humidity1);
  delay(delayTime);
}



// Print BMP values to Serial
void bmpSerialPrint(float temp, float pressure, float humidity) {
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(" *C");
  
  // Convert temperature to Fahrenheit
  /*Serial.print("Temperature = ");
  Serial.print(1.8 * bme.readTemperature() + 32);
  Serial.println(" *F");*/
  
  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.println();
}
