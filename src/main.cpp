#include <Wire.h>

// OV7670 I2C address (commonly 0x21 or 0x42 >> 1 = 0x21 for 7-bit)
#define OV7670_I2C_ADDR 0x21

void setup() {
  Serial.begin(115200);
  Wire.begin();

  Serial.println("Initializing camera...");

  if (testCameraConnection()) {
    Serial.println("Camera connected successfully!");
  } else {
    Serial.println("Camera not detected! Check wiring.");
  }

  delay(1000);
}

void loop() {
  simulateImageCapture();
  delay(1000);
}

bool testCameraConnection() {
  Wire.beginTransmission(OV7670_I2C_ADDR);
  byte error = Wire.endTransmission();
  return (error == 0);
}

void simulateImageCapture() {
  // Fake 8x8 grayscale image output
  const int width = 8;
  const int height = 8;

  Serial.println("Simulated Image:");
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int pixel = random(0, 256);  // Simulated grayscale value
      char shade = mapPixelToAscii(pixel);
      Serial.print(shade);
    }
    Serial.println();
  }
  Serial.println();
}

char mapPixelToAscii(int value) {
  const char* shades = " .:-=+*#%@";
  int index = map(value, 0, 255, 0, 9);
  return shades[index];
}
