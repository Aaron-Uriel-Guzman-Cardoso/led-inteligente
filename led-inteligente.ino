#include <Adafruit_NeoPixel.h>
#include <math.h>
/*#include "SPIFFS.h"*/

#define PIN_SENSOR 2
#define PIN_ARRAY 32
#define PIN_SON 18
Adafruit_NeoPixel array = Adafruit_NeoPixel(64,PIN_ARRAY,NEO_GRB + NEO_KHZ800);


void setup() {
   Serial.begin(115200);
 /* if(!SPIFFS.begin(true)){
    Serial.println("Error");
    return;
  }
  File file= SPIFFS.open("/prueba.txt");
  if(!file) {
    Serial.println("Error dos");
    return;
    }
    Serial.println("File content:"); 
  while(file.available()){
    Serial.write(file.read()); }
    */
  
  array.begin();
  array.show(); //Muestra en la tira lo que antes se haya configurado colores o matriz limpia
  pinMode(PIN_SENSOR,INPUT);
  pinMode(PIN_SON, INPUT);
 
}

void loop() {
  
  while(digitalRead(PIN_SON) == LOW && digitalRead(PIN_SENSOR) == LOW);  //Semantiene ahí si no hay movimiento o sonido, no enciende
  if(digitalRead(PIN_SON)==HIGH || digitalRead(PIN_SENSOR) == HIGH) //Enciende si hay sonido o movimiento
  {  
    Serial.println("Movimiento detectado");
    array.setBrightness(10);  //brillo
    for(int i = 0; i < 64;i++)
    {
      array.setPixelColor(i,255*sin(i/64.0 * 2*M_PI),255*cos(i/64.0 * 2*M_PI),255*sin(i/64.0 * 2*M_PI) + M_PI/2); //led, r, g ,b
      //array.setPixelColor(i,186,74,0); //led, r, g ,b
      array.show();
      delay(100);
    }
    delay(2000);
    array.clear();  //comando para apagar todos los leds, limpiar matriz
    array.show();
    
  }
}
