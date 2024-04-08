#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int oxygenSensorPin = A0; // Analog pin connected to the oxygen sensor

void setup() {
  Serial.begin(9600);

  // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();

  // Initialize the oxygen sensor
  pinMode(oxygenSensorPin, INPUT);
}

void loop() {
  // Read analog value from the oxygen sensor
  int oxygenValue = analogRead(oxygenSensorPin);

  // Convert analog value to oxygen level (you may need to calibrate this based on sensor datasheet)
  float oxygenLevel = map(oxygenValue, 0, 1023, 0, 100); // assuming 0-1023 range, and 0-100% oxygen level

  // Print oxygen level to serial monitor
  Serial.print("Oxygen Level: ");
  Serial.print(oxygenLevel);
  Serial.println("%");

  // Display oxygen level on OLED display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Oxygen Level:");
  display.setCursor(0,10);
  display.print(oxygenLevel);
  display.print("%");
  display.display();

  delay(1000); // Wait for 1 second before reading again
}
