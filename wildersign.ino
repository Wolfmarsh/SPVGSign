#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 0

uint16_t state;
long loopcount;
long randNumber;
long wipeNumber;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(32, PIN, NEO_RGBW + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  rainbowCycle(20);

  randomSeed(analogRead(2));

  state = 2;
}

void loop() {

  //determine which state we are in and do something
  switch (state) {
    case 0:
      //add to the counter
      loopcount += 1;
      if(loopcount >= 1800) {  //3000 is about 5 minutes, 600 is a minute, 1800 is 3 minutes
        state = 1;
      }
      delay(100);
      break;
    case 1:
      //pick a random display effect
      randNumber = random(21);
      switch (randNumber) {
        case 0:
          rainbowCycle(20);
          break;
        case 1:
          theaterChase(strip.Color(0, 0, 255), 60); // Blue
          break;
        case 2:
          theaterChase(strip.Color(255, 0, 0), 60); // Red
          break;
        case 3:
          theaterChase(strip.Color(0, 255, 0), 60); // green
          break;
        case 4:
          rainbowCycle(20);
          break;
        case 5:
          theaterChase(strip.Color(0, 0, 0, 255), 60); // white
          break;
        case 6:
          theaterChase(strip.Color(255, 0, 255, 0), 60); // purple
          break;
        case 7:
          theaterChase(strip.Color(255, 255, 0, 0), 60); // yellow
          break;
        case 8:
          theaterChase(strip.Color(0, 255, 255, 0), 60); // aqua
          break;
        case 9:
          rainbowCycle(20);
          break;
        case 10:
          theaterChase(strip.Color(random(0,255), random(0,255), random(0,255)), random(50,101)); // random color and speed
          break;
        case 11:
          CylonBounce(strip.Color(0, 0, 0, 255), 4, 10, 50); //White
          break;
        case 12:
          CylonBounce(strip.Color(255, 0, 255, 0), 4, 10, 50); //purple
          break;
        case 13:
          CylonBounce(strip.Color(0, 0, 255, 0), 4, 10, 50); //blue
          break;
        case 14:
          CylonBounce(strip.Color(255, 0, 0, 0), 4, 10, 50); //red
          break;
        case 15:
          rainbowCycle(20);
          break;
        case 16:
          CylonBounce(strip.Color(0, 255, 0, 0), 4, 10, 50); //green
          break;
        case 17:
          CylonBounce(strip.Color(0, 255, 255, 0), 4, 10, 50); //yellow
          break;
        case 18:
          CylonBounce(strip.Color(random(0,255), random(0,255), random(0,255), 0), random(2,6), random(10,26), random(50,101)); //random color, size, and speed
          break;
        case 19:
          Sparkle(strip.Color(0, 0, 0, 255), 10); //do a stadium photography effect
          break;
        case 20:
          Sparkle(strip.Color(random(50,255), random(50,255), random(50,255), 0), random(10,25)); //do a random color stadium photography effect
          break;
      }
      state = 2;
      break;
    case 2:
      //reset everything
      state = 0;
      loopcount = 0;

      
      wipeNumber = random(2);
      switch (wipeNumber) {
        case 0:
          colorWipe(strip.Color(0, 0, 0, 255), 40); // White RGBW
          break;
        case 1:
          colorWipeReverse(strip.Color(0, 0, 0, 255), 40); // White RGBW
          break;
        default:
          colorWipe(strip.Color(0, 0, 0, 255), 40); // White RGBW
          break;
      }
      
      
      //for(uint16_t i=0; i<strip.numPixels(); i++) {
      //  strip.setPixelColor(i, strip.Color(0, 0, 0, 255));
      //}
      //strip.show();
      
      break;
    default:
      state = 2;
      break;
  }  
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void colorWipeReverse(uint32_t c, uint8_t wait) {
  for(uint16_t i=strip.numPixels(); i>0; i--) {
    strip.setPixelColor(i-1, c);
    strip.show();
    delay(wait);
  }
}

void setAll(uint32_t c) {
  for(int i = 0; i < strip.numPixels(); i++ ) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}

//void rainbow(uint8_t wait) {
//  uint16_t i, j;
//
//  for(j=0; j<256; j++) {
//    for(i=0; i<strip.numPixels(); i++) {
//      strip.setPixelColor(i, Wheel((i+j) & 255));
//    }
//    strip.show();
//    delay(wait);
//  }
//}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*3; j++) { // 3 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<25; j++) {  //do 25 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void CylonBounce(uint32_t c, int EyeSize, int SpeedDelay, int ReturnDelay){

  long loopstodo;
  loopstodo = random(3,8);

  for(int b = 0; b < loopstodo; b++) {
    for(int i = 0; i < strip.numPixels()-EyeSize-2; i++) {
      
      setAll(strip.Color(0, 0, 0, 0));
      
      strip.setPixelColor(i, c);
      for(int j = 1; j <= EyeSize; j++) {
        strip.setPixelColor(i+j, c); 
      }
      strip.setPixelColor(i+EyeSize+1, c);
      strip.show();
      delay(SpeedDelay);
    }
  
    delay(ReturnDelay);
  
    for(int i = strip.numPixels()-EyeSize-2; i > 0; i--) {
      setAll(strip.Color(0, 0, 0, 0));
      strip.setPixelColor(i, c);
      for(int j = 1; j <= EyeSize; j++) {
        strip.setPixelColor(i+j, c); 
      }
      strip.setPixelColor(i+EyeSize+1, c);
      strip.show();
      delay(SpeedDelay);
    }
    
    delay(ReturnDelay);
  }
}

void Sparkle(uint32_t c, int SpeedDelay) {

  long sparklestodo;
  sparklestodo = random(150,301);

  setAll(strip.Color(0, 0, 0, 0));

  for(int i = 0; i < sparklestodo; i++) {
    int Pixel = random(strip.numPixels());
    strip.setPixelColor(Pixel, c);
    strip.show();
    delay(SpeedDelay);
    strip.setPixelColor(Pixel, strip.Color(0, 0, 0, 0));
  }
}




