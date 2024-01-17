#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SD.h>
#include <SPI.h>
#include <ACS712.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SD_CS_PIN 5  
#define FILENAME "acs712.txt"  // File name to store data

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// 33: The pin to which the ACS712 sensor is connected.
// 3.3: The reference voltage for the ADC (Analog-to-Digital Converter) on esp32. This is often the supply voltage.
// 4095: The maximum ADC value, representing the maximum possible value the ADC can read (for a 12-bit ADC).
// 185: The sensitivity of the ACS712 sensor in mV per Ampere.
ACS712  ACS(33, 3.3, 4095, 185);

int voltageSensorPin = 32;

File dataFile;

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) // Address 0x3D for 128x64
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();

  // Initialize SD card
  if (SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialized.");
    dataFile = SD.open(FILENAME, FILE_WRITE);
    if (dataFile) {
      dataFile.println("Current(mA),Voltage(V)");
      dataFile.close();
    }
  } else {
    Serial.println("SD card initialization failed!");
  }
}

void loop() {
  // Read current from ACS712 sensor
  float current_mA = ACS.mA_DC();

  // Read voltage from voltage sensor
  int sensorValue = analogRead(voltageSensorPin);
  float voltage = map(sensorValue, 0, 4095, 0, 12000) / 1000.0;


  // Print the values to the Serial Monitor
  Serial.print("Current: ");
  Serial.print(current_mA);
  Serial.println(" mA");

  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  // Save data to SD card
  dataFile = SD.open(FILENAME, FILE_WRITE);
  if (dataFile) {
    dataFile.print(current_mA);
    dataFile.print(",");
    dataFile.println(voltage);
    dataFile.close();
  } else {
    Serial.println("Error opening data file.");
  }

  // Display the values on the OLED display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Current: ");
  display.print(current_mA);
  display.print(" mA");

  display.setCursor(0, 16);
  display.print("Voltage: ");
  display.print(voltage);
  display.print(" V");

  display.display();

  delay(1000);
}
