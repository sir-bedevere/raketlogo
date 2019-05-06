#include <TeensyDmx.h>
#include <WS2812Serial.h>

#define DMX_REDE 2
#define CHANNEL 0

#define LED_PIN 5
#define NUM_LED 751

byte drawingMemory[NUM_LED*3];         //  3 bytes per LED
DMAMEM byte displayMemory[NUM_LED*12]; // 12 bytes per LED

TeensyDmx Dmx(Serial2, DMX_REDE);
WS2812Serial leds(NUM_LED, displayMemory, drawingMemory, LED_PIN, WS2812_GRB);

IntervalTimer t;

void setup() {
  t.begin(shutter, 150000);
  leds.begin();
  Dmx.setMode(TeensyDmx::DMX_IN);
}

uint32_t c[5];
uint32_t c_bak[5];

uint8_t rate, rate_bak;

volatile boolean shutterOn;

void loop() {
  Dmx.loop();
  
  rate = Dmx.getChannel(15);  

  if ( rate != rate_bak ){
    t.update(map(rate, 0, 255, 500000, 15000));
    rate_bak = rate;
  }

  for ( int i=0; i<=4; i++){
    if ( shutterOn ){
      c[i] = getRGB(i*3);  
    } else{
      c[i] = 0;  
    }
  }
  
  if ( c[0] != c_bak[0] ){
    driehoek(c[0]);
    leds.show(); 
    c_bak[0] = c[0]; 
  }
  
  if ( c[1] != c_bak[1] ){
    logo(c[1]);
    leds.show(); 
    c_bak[1] = c[1]; 
  }
  
  if ( c[2] != c_bak[2] ){
    driehoek_logo(c[2]);
    leds.show(); 
    c_bak[2] = c[2]; 
  }
  
  if ( c[3] != c_bak[3] ){
    cirkels(c[3]);
    leds.show(); 
    c_bak[3] = c[3]; 
  }
  
  if ( c[4] != c_bak[4] ){
    rest(c[4]);
    leds.show(); 
    c_bak[4] = c[4]; 
  }
}

void shutter(){
  if ( rate == 0 ){
    shutterOn = true;  
  } else{
    shutterOn = not shutterOn;
  }
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
