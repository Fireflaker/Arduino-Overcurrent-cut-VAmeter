#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <Wire.h> // Required Library 1


float voltageReference = 10;// Set Reference Voltage  (see notes)
float AmperageReference = 3.3;// Set Reference Voltage  (see notes)
float AmperageLimit = 2;
float R1 = 10000; // VCC_Resistor of Potential Divider (10K)
float R2 = 1000; // GND_Resistor of Potential Divider (1K)


void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(500); // Pause for 2 seconds

}


void loop() {
  display.clearDisplay();


  float voltageInput = (analogRead(3) * voltageReference) / 1023.0;
  float Voltage = voltageInput / (R2 / (R1 + R2));
  if (voltageInput < 0.09) {
    Voltage = 0;
  }
  float AmperageInput = (analogRead(2) * AmperageReference) / 1023.0;
  float Amperage = AmperageInput / (R2 / (R1 + R2));
  if (AmperageInput < 0.09) {
    Amperage = 0;
  }

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' fon

  display.print(Voltage);
  display.print("V");

  display.setCursor(0, 10);
  display.print(Amperage);
  display.print("A");
  display.print("   ");



  
  display.display();

  delay(30);

}
