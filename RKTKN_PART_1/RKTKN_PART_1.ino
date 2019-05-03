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
  setPixels(color, 0, 14);
  setPixels(color, 27, 106);
  setPixels(color, 131, 135);
}

void driehoek_logo(uint32_t color){
  setPixels(color, 15, 26);
  setPixels(color, 107, 119);
  setPixels(color, 120, 130);
}

void logo(uint32_t color){
  setPixels(color, 163, 212);
  setPixels(color, 216, 218);
  setPixels(color, 234, 287);
  setPixels(color, 294, 453);
  setPixels(color, 455, 455);
  setPixels(color, 460, 464);
  setPixels(color, 476, 481);
  setPixels(color, 497, 502);
  setPixels(color, 510, 510);
  setPixels(color, 515, 557);
  setPixels(color, 560, 607);
}

void cirkels(uint32_t color){
  setPixels(color, 136, 162); 
  setPixels(color, 219, 233);
}

void rest(uint32_t color){
  setPixels(color, 213, 215);
  setPixels(color, 288, 293);
  setPixels(color, 454, 454);
  setPixels(color, 456, 459);
  setPixels(color, 465, 475);
  setPixels(color, 482, 496);
  setPixels(color, 503, 509);
  setPixels(color, 511, 514);
  setPixels(color, 558, 559);
  setPixels(color, 608, 610);
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
