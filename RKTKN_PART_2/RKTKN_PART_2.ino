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
  setPixels(color, 0, 16);
  setPixels(color, 28, 109);
  setPixels(color, 121, 129);
  setPixels(color, 136, 136);
}

void driehoek_logo(uint32_t color){
  setPixels(color, 17, 27); 
  setPixels(color, 110, 120);
  setPixels(color, 130, 135);
}

void logo(uint32_t color){
  setPixels(color, 165, 216);
  setPixels(color, 220, 224);
  setPixels(color, 239, 293);
  setPixels(color, 298, 326);
  setPixels(color, 331, 367);
  setPixels(color, 374, 380);
  setPixels(color, 385, 474);
  setPixels(color, 476, 476);
  setPixels(color, 481, 485);
  setPixels(color, 498, 523);
  setPixels(color, 531, 531);
  setPixels(color, 537, 578);
  setPixels(color, 580, 627);
}

void cirkels(uint32_t color){
  setPixels(color, 137, 164);
  setPixels(color, 225, 238);
}

void rest(uint32_t color){
  setPixels(color, 217, 219);
  setPixels(color, 294, 297);
  setPixels(color, 327, 330);
  setPixels(color, 368, 373);
  setPixels(color, 381, 384);
  setPixels(color, 475, 475);
  setPixels(color, 486, 497);  
  setPixels(color, 477, 480);
  setPixels(color, 524, 530);
  setPixels(color, 532, 536);
  setPixels(color, 579, 579);
  setPixels(color, 628, 631);
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
