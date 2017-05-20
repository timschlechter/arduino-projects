/*
Adafruit Arduino - Lesson 3. RGB LED
*/
 
int redPin = 11;
int greenPin = 10;
int bluePin = 9;
 
//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE
 
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}
 
void loop()
{
  setColor(255, 0, 0); 
  
  for (int g=0; g<=255; g++) {
    setColor(255-g, g, 0);
  }     

  for (int b=0; b<=255; b++) {
    setColor(0, 255-b, b);     
  }

  for (int r=0; r<=255; r++) {
    setColor(r, 0, 255-r);     
  }
}
 
void setColor(int red, int green, int blue)
{
  
  delay(10);
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
