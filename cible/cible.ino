
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

bool partieEtat[6] = {true,true,true,true,true,true};
int partiePin[6] = {A0,A1,A2,A3,A4,A5};
int partieSeuil[6] = {400,400,400,300,400,400};
int compteurFin=0;


#define LEDVAL 150
#define LEDMAX 255


#define PINLED 6

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(6, PINLED, NEO_GRB + NEO_KHZ800);

void setPix(int id, int r, int v, int b){
  pixels.setPixelColor(id, pixels.Color(r,v,b));
  pixels.show();
}
void set6Pix(int r, int v, int b){
  pixels.setPixelColor(0, pixels.Color(r,v,b));
  pixels.setPixelColor(1, pixels.Color(r,v,b));
  pixels.setPixelColor(2, pixels.Color(r,v,b));
  pixels.setPixelColor(3, pixels.Color(r,v,b));
  pixels.setPixelColor(4, pixels.Color(r,v,b));
  pixels.setPixelColor(5, pixels.Color(r,v,b));
  pixels.show();
}


void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off'
  setPix(0,LEDVAL,LEDVAL,LEDVAL);
  setPix(1,LEDMAX,LEDMAX,LEDMAX);
  setPix(2,LEDVAL,LEDVAL,LEDVAL);
  setPix(3,LEDMAX,LEDMAX,LEDMAX);
  setPix(4,LEDMAX,LEDVAL,LEDVAL);
  setPix(5,LEDVAL,LEDVAL,LEDVAL);

}

void loop() {
 int compteOff=0;
 int value=0;
 for(int i=0;i<6;i++)
 {
  if(partieEtat[i]==true)
  {
     value=analogRead(partiePin[i]);
     if(value>partieSeuil[i])
     {
      partieEtat[i]=false;
      setPix(i,0,0,0);
     }
  }
  else
  {
    compteOff++;
  }
 }
 if(compteOff==6)
 {
  compteurFin++;
  setPix(0,LEDVAL,LEDVAL,LEDVAL);
  delay(50);
  setPix(0,0,0,0);
  setPix(5,LEDVAL,LEDVAL,LEDVAL);
  delay(50);
  setPix(5,0,0,0);
  setPix(2,LEDVAL,LEDVAL,LEDVAL);
  delay(50);
  setPix(2,0,0,0);
  setPix(4,LEDVAL,LEDVAL,LEDVAL);
  delay(100);
  setPix(4,0,0,0);
  setPix(2,LEDVAL,LEDVAL,LEDVAL);
  delay(50);
  setPix(2,0,0,0);
  setPix(5,LEDVAL,LEDVAL,LEDVAL);
  delay(50);
  setPix(5,0,0,0);
  setPix(0,LEDVAL,LEDVAL,LEDVAL);
  delay(50);
  setPix(0,0,0,0);
  setPix(1,LEDMAX,LEDMAX,LEDMAX);
  delay(50);
  setPix(1,0,0,0);
  setPix(2,LEDVAL,LEDVAL,LEDVAL);
  delay(50);
  setPix(2,0,0,0);
  setPix(3,LEDMAX,LEDMAX,LEDMAX);
  delay(50);
  setPix(3,0,0,0);
  setPix(4,LEDVAL,LEDVAL,LEDVAL);
  delay(50);
  setPix(4,0,0,0);
  setPix(5,LEDVAL,LEDVAL,LEDVAL);
  delay(50);
  setPix(5,LEDVAL,LEDVAL,LEDVAL);  
  if(compteurFin>5)
  {
    compteurFin=0;
    compteOff=0;
     for(int i=0;i<6;i++)
     {
      setPix(i,LEDVAL,LEDVAL,LEDVAL); 
      partieEtat[i]=true;
     }
  }
 }

}
