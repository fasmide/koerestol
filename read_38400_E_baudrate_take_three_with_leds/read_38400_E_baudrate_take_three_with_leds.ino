#include "FastLED.h"

FASTLED_USING_NAMESPACE

#define DATA_PIN    5
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    13
CRGB leds[NUM_LEDS];

#define BRIGHTNESS  96
uint8_t gHue = 0; // rotating "base color" used by many of the patterns


int frame[7];

unsigned long timeToDo = 0;
unsigned long timeout = 0;
boolean timedOut = true;
void setup()  
{
  frame[0] = 74;
  frame[1] = 0;
  frame[2] = 0;
  frame[3] = 0;
  frame[4] = 0;
  frame[5] = 181;
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial1.begin(38400, SERIAL_8E1);
  disable();
  
  //pinMode(0, INPUT_PULLUP);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  } 
  enable();

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

}

void disable() {
  UCSR1B &= ~bit (TXEN1); //disable TX
}
void enable() {
  //enables both rx and tx, even though rx is enabled already
  UCSR1B = (1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1);
}

void loop() // run over and over
{
  if(Serial.available()) {
    frame[0] = Serial.read();
    frame[1] = Serial.read();
    frame[2] = Serial.read();
    frame[3] = Serial.read();
    frame[4] = Serial.read();
    frame[5] = Serial.read();
    timeout = millis()+1000;
    timedOut = false;
  }

  if( millis() >= timeout) {
    timedOut = true;
  }

  if(timedOut) {
      disable();
    } else {
      enable();  
    }
  
  if (!timedOut && millis() >= timeToDo){
    
    for(int i = 0; i < 6; i++) {
      Serial1.write(frame [i]);
    }
     Serial1.flush();
     
    delayMicroseconds(500);
    disable();

    delay(3);

    enable();
    
    timeToDo = millis()+10;

  }

  while(Serial1.available()) {
    Serial.write(Serial1.read());  
  }
  
  renderLeds();
  

}




void renderLeds()
{

  FastLED.show();
  leds[3].r = 255;
  leds[3].g = 255;
  leds[3].b = 255;
}

