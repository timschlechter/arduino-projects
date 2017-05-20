// Inladen van de ledcontrol bibliotheek.
#include "LedControl.h"
#include "asciitable.h"

// VCC -> 5V
// GND -> GND
// DIN -> 12
// CS  -> 11
// CLK -> 10

LedControl lc=LedControl(12, 10, 11, 1); // DIN, CLK, CS, NRDEV
 
char text[] = "Koen Nienke Renate en Tim  ";
int text_len = strlen(text);

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

void loop() { 
    for (int i = 0; i < text_len; i++){
      char c1 = text[i];
      char c2 = text[(i+1)%text_len];

      byte* c1_pattern = ASCIITABLE[c1];
      byte* c2_pattern = ASCIITABLE[c2];
      
      for (int s=0; s<8; s++) {
        byte pattern[8];        
        shift(c1_pattern, c2_pattern, s, pattern);
        set_leds(pattern);        
        delay(75); 
      } 
    }    
}

void shift(byte a[8], byte b[8], int amount, byte result[8]) {
  for (int r = 0; r < 8; r++) {
    result[r] = shift_row(a[r],b[r], amount);
  }
}

byte shift_row(byte a, byte b, int amount) {
  uint16_t i = (a << 8) | b;
  i = i << amount;  
  return i >> 8;
}

void set_leds(byte pattern[8]) {
  for (int i = 0; i < 8; i++)  { 
    lc.setRow(0,i,pattern[i]); 
  }
}
