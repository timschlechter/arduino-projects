#include "LedControl.h"

// LED matrix display (MAX7219):
//   - VCC -> 5V
//   - GND -> GND
//   - DIN -> 12
//   - CS  -> 10
//   - CLK -> 11

LedControl lc = LedControl(12, 11, 10, 1);  // DIN, CLK, CS, NRDEV

int photocellPin = 0;  // the cell and 10K pulldown are connected to a0
int photocellReading;  // the analog reading from the sensor divider

void setup(void) {
  Serial.begin(9600);

  int devices = lc.getDeviceCount();
  for (int address = 0; address < devices; address++) {
    lc.shutdown(address, false);
    lc.setIntensity(address, 8);
    lc.clearDisplay(address);
  }
}

byte happy[] = {
    B00000000, B00100100, B00100100, B00000000,
    B00000000, B01000010, B00111100, B00000000,
};

byte sad[] = {
    B00000000, B00100100, B00100100, B00000000,
    B00000000, B00111100, B01000010, B00000000,
};

void loop(void) {
  photocellReading = analogRead(photocellPin);

  Serial.print("Analog reading = ");
  Serial.println(photocellReading);

  if (photocellReading < 50) {
    set_leds(happy);
  } else {
    set_leds(sad);
  }
}

void set_leds(byte pattern[]) {
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, pattern[i]);
  }
}
