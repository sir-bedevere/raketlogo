#include <TeensyDmx.h>
#include <WS2812Serial.h>

#define DMX_REDE 2      // MAX485 PINS
#define CHANNEL 0       // DMX Start channel
#define NUMCHANNELS 3   // Num channels per strip

#define LED_PIN 5       // Output to pixel
#define NUM_LED 751      // Total number of Leds
#define NUMSTRANDS 15   // Controllable pieces per strand
#define STRANDSIZE 100  // Leds per piece

// STROBE + CHANNEL

int ledArray[NUMSTRANDS][STRANDSIZE] = {
  { 0, 1 },
  { 62, 63, 64, 65 }  
};


int backupColor[NUMSTRANDS];


byte drawingMemory[NUM_LED*3];         //  3 bytes per LED
DMAMEM byte displayMemory[NUM_LED*12]; // 12 bytes per LED

TeensyDmx Dmx(Serial2, DMX_REDE);
WS2812Serial leds(NUM_LED, displayMemory, drawingMemory, LED_PIN, WS2812_GRB);

void setup() {
  Serial.begin(9600);
  leds.begin();
  Dmx.setMode(TeensyDmx::DMX_IN);
}

uint32_t c = 0x00FF00;
uint32_t c_bak;

uint32_t c_driehoek = 0xFF0000;
uint32_t c_logo = 0x00FF00;
uint32_t c_cirkels = 0x0000FF;

volatile uint8_t *dmxBuf;


void loop() {
  driehoek(0xFF0000);
  driehoek_logo(0xFF00FF);
  cirkels(0x0000FF);
  logo(0x00FF00);
  rest(0xffff00);
  leds.show();
  delay(1000);
  /*

  Dmx.loop();

  c = getRGB(0);

  if ( c != c_bak ){  
    setPixels(c, 0, 750 );
    leds.show(); 
    c_bak = c; 
  }
  */
}

void driehoek(uint32_t color){
  setPixels(color, 0, 8);
  setPixels(color, 18, 20);
  setPixels(color, 26, 43);
  setPixels(color, 54, 62);
  setPixels(color, 74, 82);
  setPixels(color, 93, 110);
  setPixels(color, 117, 119);
  setPixels(color, 131, 136);
}

void driehoek_logo(uint32_t color){
  setPixels(color, 9, 17);
  setPixels(color, 21, 25);
  setPixels(color, 44, 53);
  setPixels(color, 63, 73);
  setPixels(color, 83, 92);
  setPixels(color, 111, 116);
  setPixels(color, 120, 130);
}

void logo(uint32_t color){
  setPixels(color, 229, 392);  
  setPixels(color, 401, 402);
  setPixels(color, 411, 561);
  setPixels(color, 569, 570);
  setPixels(color, 578, 750);
}

void cirkels(uint32_t color){
  setPixels(color, 137, 228);
}

void rest(uint32_t color){
  setPixels(color, 393, 400);
  setPixels(color, 403, 410);
  setPixels(color, 562, 568);
  setPixels(color, 571, 577);
}

uint32_t getRGB(int ch){
  byte r = Dmx.getChannel(ch);
  byte g = Dmx.getChannel(ch+1);
  byte b = Dmx.getChannel(ch+2);

  return r * 0x10000 + g * 0x100 + b;
}

void setPixels(uint32_t color, int from, int to){
  for ( int c = from; c <= to; c++ ){
    leds.setPixel(c, color);    
  }
}
