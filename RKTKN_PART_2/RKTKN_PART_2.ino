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
  
  rate = Dmx.getChannel(16);  

  if ( rate != rate_bak ){
    t.update(map(rate, 0, 255, 1000000, 20000));
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
