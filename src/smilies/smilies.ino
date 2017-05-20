// Inladen van de ledcontrol bibliotheek.
#include "LedControl.h"

// VCC -> 5V
// GND -> GND
// DIN -> 12
// CS  -> 11
// CLK -> 10

LedControl lc=LedControl(12, 10, 11, 1); // DIN, CLK, CS, NRDEV
 
void setup() {
    // Haal het aantal apparaten op dat we hebben "gecreëerd" met Ledcontrol.
    int devices=lc.getDeviceCount();
    // Alle apparaten initialiseren (in een loop).
    for(int address=0;address<devices;address++) {
        // De MAX72XX IC is in slaapstand modus bij opstarten.
        lc.shutdown(address,false);
        // Zet de helderheid op een medium niveau.
        lc.setIntensity(address,8);
        // Maak de dot matrix leeg (clear display).
        lc.clearDisplay(address);
    }
}
 
byte happy[] = {
  B00000000,
  B00100100,
  B00100100,
  B00000000,
  B00000000,
  B01000010,
  B00111100,
  B00000000,
};

byte sad[] = {
  B00000000,
  B00100100,
  B00100100,
  B00000000,
  B00000000,
  B00111100,
  B01000010,  
  B00000000,
};

void loop() { 
    // Lees het aantal apparaten uit.
    int devices=lc.getDeviceCount();
  
    setLeds(sad);
    delay(1000);
    setLeds(happy);
    delay(1000);
}

void setLeds(byte pattern[]) {
  for (int i = 0; i < 8; i++)  { lc.setRow(0,i,pattern[i]); }
}

