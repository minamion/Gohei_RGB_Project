#include <Adafruit_NeoPixel.h>
#include <Bounce2.h> 
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 9 
#define LED_NUMBER 20
#define BUTTON1 10 
#define BUTTON2 11
#define BUTTON3 12
int color = 0;
int light = 0;
// Instantiate a Bounce object
Bounce b1b = Bounce();
Bounce b2b = Bounce();
Bounce b3b = Bounce();
int button1 = 0;
int button2 = 0;
int button3 = 0;
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NUMBER, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {

	// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
	if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
	// End of trinket special code
	pinMode(BUTTON1, INPUT_PULLUP);
	pinMode(BUTTON2, INPUT_PULLUP);
	pinMode(BUTTON3, INPUT_PULLUP);
	b1b.attach(BUTTON1);
	b2b.attach(BUTTON2);
	b3b.attach(BUTTON3);
	b1b.interval(10); // interval in ms
	b2b.interval(10); // interval in ms
	b3b.interval(10); // interval in ms
	strip.begin();
	
	strip.show(); // Initialize all pixels to 'off'

}
int Button1_old = HIGH;
int Button2_old = HIGH;
int Button3_old = HIGH;

void loop() {

	b1b.update();
	b2b.update();
	b3b.update();
	button1 = b1b.read();
	button2 = b2b.read();
	button3 = b3b.read();
	//button1£ºcolor ID+
	if (button1 != Button1_old && button1 == LOW) {
		if (color == 15) {
			color = 0;
		}
		else {
			color += 1;
		}
	}
	//button1£ºcolor ID-
	if (button2 != Button2_old && button2 == LOW) {
		if (color == 0) {
			color = 15;
		}
		else {
			color -= 1;
		}
	}
	//button1£ºLight+
	if (button3 != Button3_old && button3 == LOW) {
		if (light == 5) {
			light = 0;

		}
		else {
			light += 1;

		}
	}
	
	switch (light) {
	case 0:strip.setBrightness(10); break;
	case 1:strip.setBrightness(25); break;
	case 2:strip.setBrightness(50); break;
	case 3:strip.setBrightness(75); break;
	case 4:strip.setBrightness(100); break; //more than 100 too light
	}
	Button1_old = button1;
	Button2_old = button2;
	Button3_old = button3;
	LED_setAll(color);
}

void LED_setAll(int c) {
	for (int i = 0; i < strip.numPixels(); i++) {
		switch (c) {  
		case 0:strip.setPixelColor(i, 127, 127, 127); break; //Marisa(White        
		case 1:strip.setPixelColor(i, 255, 0, 0); break; //Reimu(Red
		case 2:strip.setPixelColor(i, 0, 255, 0); break; //Sanae(Green
		case 3:strip.setPixelColor(i, 0, 0, 255); break;//Nitori(Blue
		case 4:strip.setPixelColor(i, 127, 127, 0); break;//Alice(Yello
		case 5:strip.setPixelColor(i, 135, 206, 250); break;//light blue  
		case 6:strip.setPixelColor(i, 144, 200, 144); break;//light green			    
		case 7:strip.setPixelColor(i, 160, 32, 240); break;//Yukari(purple
		case 8:strip.setPixelColor(i, 255, 192, 203); break;//Yuyuko(pink       
		case 9:strip.setPixelColor(i, 0, 127, 127); break;//Tenshi(cyan		    
		case 10:strip.setPixelColor(i, 186, 85, 211); break;//Akyuu(violet   
		case 11:strip.setPixelColor(i, 0, 250, 154); break;//Utsuho(dark green
		case 12:strip.setPixelColor(i, 255, 182, 193); break;//light pink
		case 13:strip.setPixelColor(i, 255, 165, 0); break;//Kosuzu(Orange    
		case 14:strip.setPixelColor(i, 50, 205, 50); break;//Sanae(Lime green
		case 15:strip.setPixelColor(i, 0, 191, 255); break;//Cirno(Deep sky blue
		}
		strip.show();
	
	}
};