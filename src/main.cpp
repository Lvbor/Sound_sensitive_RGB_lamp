// ATTACHED LIBRARIES

#include <FastLED.h>
#include "R_Variables.h"
#include "R_Animations.h"
#include "R_Buttons.h"
#include "R_Temp.h"




CRGB leds[NUM_LEDS];

void setup() {

    Serial.begin(115200);
    
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
sensor_init();

// EEPROM INIT 
EEPROM.begin(EEPROM_INIT);
// EEPROM READ
bootstate = EEPROM.read(13);
if (bootstate == 255) {
    bootstate = 0;
}
Serial.println(bootstate);
if (bootstate == 1) {
ledbrightness = EEPROM.read(1);
ledsaturation = EEPROM.read(2);
setred = EEPROM.read(3);
setgreen = EEPROM.read(4);
setblue = EEPROM.read(5);
ledhue = EEPROM.read(6);
bouncehue = EEPROM.read(7);
blinkdelay = EEPROM.read(8)*5;
bouncedelay = EEPROM.read(9)*5;
fadedelay = EEPROM.read(10)*5;
burstdelay = EEPROM.read(11)*5;
wavedelay = EEPROM.read(12)*5;
}
else if (bootstate == 0) {
EEPROM.write(1, ledbrightness);
EEPROM.write(2, ledsaturation);
EEPROM.write(3, setred);
EEPROM.write(4, setgreen);
EEPROM.write(5, setblue);
EEPROM.write(6, ledhue);
EEPROM.write(7, bouncehue);
EEPROM.write(8, blinkdelay/5);
EEPROM.write(9, bouncedelay/5);
EEPROM.write(10, fadedelay/5);
EEPROM.write(11, burstdelay/5);
EEPROM.write(12, wavedelay/5);
bootstate = 1;
EEPROM.write(13, bootstate);
EEPROM.commit();
}

// OLED INIT
    oled.display();
    oled.setTextSize(1); 
    oled.setTextColor(SSD1306_WHITE);
    delay(SAFETY_DELAY);
    while (loading < 4) {
    loading_screen();
    loading++;
    }
    while (loading == 4) {
    button_setup();
    oled.clearDisplay();
    oled.setCursor(15, 20);
    oled.print(F("Press anything"));
    oled.setCursor(15, 30);
    oled.print(F("to start"));
    oled.display();
    oled.clearDisplay();
    loading++;
    }

// LED INIT
    FastLED.addLeds<LED_STRIP, DATA_PIN_LED, COLOR_TYPE_LED>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(OP_VOLTAGE, MAX_CURRENT);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    FastLED.show();
 



}


// EFFECTS

// COLOR BLINK EFFECT
void one_color_blink(byte setred, byte setgreen, byte setblue) {
    FastLED.clear();
    fill_solid(leds, NUM_LEDS, CHSV(ledhue, ledsaturation, ledbrightness));
    FastLED.show();
    delay(blinkdelay);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(blinkdelay);
}

// MOVING POINT EFFECT
void color_bounce() {
    FastLED.clear();
    if (shift == true) {
        ledchanger = ledchanger + 1;
        if (ledchanger == NUM_LEDS) {
            shift = false;
            ledchanger = ledchanger - 1;
        }
    }
    if (shift == false) {
        ledchanger = ledchanger - 1;
        if (ledchanger == 0) {
            shift = true;
        }
    }
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i == ledchanger) {
            leds[i] = CHSV(bouncehue, ledsaturation, ledbrightness);
        }
        else {
            leds[i] = CHSV(0, 0, 0);
        }
    }
    LEDS.show();
    delay(BOUNCE_DELAY);
}

// STATIC COLOR EFFECT
void static_color(byte setred, byte setgreen, byte setblue) {
    FastLED.clear();
    fill_solid(leds, NUM_LEDS, CHSV(ledhue, ledsaturation, ledbrightness));
    FastLED.show();
}

// FADING RAINBOW EFFECT
void rainbow_fade() {
    {
        FastLED.clear();
    }
    ledhue++;
    if (ledhue > 255) {
        ledhue = 0;
    }
    for (byte ledchanger = 0; ledchanger < NUM_LEDS; ledchanger++) {
        leds[ledchanger] = CHSV(ledhue, ledsaturation, ledbrightness);
    }
    LEDS.show();
    delay(FADE_DELAY);
}

// RANDOM FLASHING POINTS EFFECT
void random_burst() {
    FastLED.clear();
    ledchanger = random(0, NUM_LEDS);
    ledhue = random(0, 255);
    leds[ledchanger] = CHSV(ledhue, ledsaturation, ledbrightness);
    LEDS.show();
    delay(BURST_DELAY);
}

// STATIC RAINBOW EFFECT
void rainbow_static() {
    FastLED.clear();
    for (int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = CHSV(ledhue + (i * 5), ledsaturation, ledbrightness);
    }
    FastLED.show();
}

// MOVING RAINBOW EFFECT
void rainbow_wave() {
    FastLED.clear();
    for (int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = CHSV(ledhue + (i * 10), ledsaturation, ledbrightness);
    }
    delay(WAVE_DELAY);
    ledhue++;
    FastLED.show();
}

// RANDOM COLOR BLINK EFFECT
void random_color_blink(byte setred, byte setgreen, byte setblue) {
    FastLED.clear();
    ledhue = random(0, 255);
    fill_solid(leds, NUM_LEDS, CHSV(ledhue, ledsaturation, ledbrightness));
    FastLED.show();
    delay(blinkdelay);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(blinkdelay);
}

// SHORT (HUE) GRADIENT EFFECT
void short_hue_gradient() {
    FastLED.clear();
    for (int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = CHSV(startgradient + (i / 2), ledsaturation, ledbrightness);
    }
    FastLED.show();
}

// AVERAGE (HUE) GRADIENT EFFECT
void hue_gradient() {
    FastLED.clear();
    for (int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = CHSV(startgradient + i, ledsaturation, ledbrightness);
    }
    FastLED.show();
}

// LONG (HUE) GRADIENT EFFECT
void long_hue_gradient() {
    FastLED.clear();
    for (int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = CHSV(startgradient + (2 * i), ledsaturation, ledbrightness);
    }
    FastLED.show();
}

// REACT SOUND RAINBOW WAVE
void react_sound_r_wave() {
    if (db < 1021) {
    FastLED.clear();
	react_stabilizer = db;
        for (int i = 0; i < db/17; ++i) {
        leds[i] = CHSV(ledhue + (i * 5), ledsaturation, ledbrightness);
    }
    reactdelay++;
    if (reactdelay == 10) {
        ledhue++;
        reactdelay = 0;
    }
    FastLED.show();
    }
    else if (db > 1020) {
		db = 1020;
		react_stabilizer = db;
    FastLED.clear();
        for (int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = CHSV(ledhue + (i * 5), ledsaturation, ledbrightness);
    }
    reactdelay++;
    if (reactdelay == 10) {
        ledhue++;
        reactdelay = 0;
    }
    FastLED.show();
    }
	    else if (db == 0) {
		react_stabilizer-=51;	
		db = react_stabilizer;
    FastLED.clear();
        for (int i = 0; i < db/17; ++i) {
        leds[i] = CHSV(ledhue + (i * 5), ledsaturation, ledbrightness);
    }
    reactdelay++;
    if (reactdelay == 10) {
        ledhue++;
        reactdelay = 0;
    }
    FastLED.show();
    }
}

// REACT SOUND RAINBOW WAVE
void react_sound_st_color() {
    if (db < 1021) {
    FastLED.clear();
        for (int i = 0; i < db/17; ++i) {
        leds[i] = CHSV(reacthue, ledsaturation, ledbrightness);
    }
    FastLED.show();
    }
    else if (db > 1020) {
    FastLED.clear();
        for (int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = CHSV(reacthue, ledsaturation, ledbrightness);
    }
    FastLED.show();
    }
     else if (db == 0) {
		react_stabilizer-=51;	
		db = react_stabilizer;
    FastLED.clear();
        for (int i = 0; i < db/17; ++i) {
        leds[i] = CHSV(reacthue, ledsaturation, ledbrightness);
    }
    FastLED.show();
    }
}


// TEXT DISPLAY 2
void display_generator() {
    if (change == true & mode == 0) {
        switch (ledMode) {
        case 255: break;
        case 1:  text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Displaying:"), F("Color blink"), F(""), F("01/13"));  break;
        case 2:  text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Displaying:"), F("Color bounce"), F(""), F("02/13")); break;
        case 3:  text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Displaying:"), F("Static color"), F(""), F("03/13")); break;
        case 4:  text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Displaying:"), F("Rainbow"), F("fade"), F("04/13")); break;
        case 5:  text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Displaying:"), F("Random"), F("burst"), F("05/13")); break;
        case 6:  text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Displaying:"), F("Rainbow"), F("static"), F("06/13")); break;
        case 7:  text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Displaying:"), F("Rainbow"), F("wave"), F("07/13")); break;
        case 8:  text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Displaying:"), F("Random"), F("color blink"), F("08/13")); break;
        case 9:  text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Displaying:"), F("Short hue"), F(""), F("09/13")); break;
        case 10: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Displaying:"), F("Hue"), F(""), F("10/13")); break;
        case 11: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Displaying:"), F("Long hue"), F(""), F("11/13")); break;
        case 12: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Displaying:"), F("Sound responsive"), F("(Rainbow wave)"), F("12/13")); break;
        case 13: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Displaying:"), F("Sound responsive"), F("(Static color)"), F("13/13")); break;
        }
        change = false;
    }

    else if (change == true & mode == 1) {
        switch (settings) {
        case 1: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("> Brightness"), F("Saturation"), F("RGB"), F("01/10")); break;
        case 2: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Brightness"), F("> Saturation"), F("RGB"), F("02/10")); break;
        case 3: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Saturation"), F("> RGB"), F("HUE start point"), F("03/10")); break;
        case 4: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("RGB"), F("> HUE start point"), F("Bounce hue point"), F("04/10")); break;
        case 5: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("HUE start point"), F("> Bounce hue point"), F("Blink delay"), F("05/10")); break;
        case 6: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Bounce hue point"), F("> Blink delay"), F("Bounce delay"), F("06/10")); break;
        case 7: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Blink delay"), F("> Bounce delay"), F("Fade delay"), F("07/10")); break;
        case 8: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Bounce delay"), F("> Fade delay"), F("Burst delay"), F("08/10")); break;
        case 9: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Fade delay"), F("> Burst delay"), F("Wave delay"), F("09/10")); break;
        case 10: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Fade delay"), F("Burst delay"), F("> Wave delay"), F("10/10")); break;
        }
        change = false;
    }

    else if (change == true & mode == 2) {
        switch (settings) {
        case 1: text2(F("> Brightness"), ledbrightness_read, F("/255"), F("01/10")); break;
        case 2: text2(F("> Saturation"), ledsaturation_read, F("/255"), F("02/10")); break;
        case 3: text2(F(""), setred, F(""), F("")); break;
        case 4: text2(F("> HUE start point"), ledhue_read, F("/255"), F("04/10")); break;
        case 5: text2(F("> Bounce hue point"), bouncehue_read, F("/255"), F("05/10")); break;
        case 6: text2(F("> Blink delay"), blinkdelay_read, F("/1250"), F("06/10")); break;
        case 7: text2(F("> Bounce delay"), bouncedelay_read, F("/1250"), F("07/10")); break;
        case 8: text2(F("> Fade delay"), fadedelay_read, F("/1250"), F("08/10")); break;
        case 9: text2(F("> Burst delay"), burstdelay_read, F("/1250"), F("09/10")); break;
        case 10: text2(F("> Wave delay"), wavedelay_read, F("/1250"), F("10/10")); break;
        }
        change = false;
    }

        else if (change == true & mode == 3) {
        switch (color) {
        case 1: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("> Red"), F("Green"), F("Blue"), F("01/03")); break;
        case 2: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Red"), F("> Green"), F("Blue"), F("02/03")); break;
        case 3: text(humidity_read, prct, pressure_read, F(" hPa"), degree, temp_read, F("Red"), F("Green"), F("> Blue"), F("03/03")); break;

        }
        change = false;
        }
            else if (change == true & mode == 4) {
        switch (color) {
        case 1: text2(F("> Red"), setred_read, F("/255"), F("01/03")); break;
        case 2: text2(F("> Green"), setgreen_read, F("/255"), F("02/03")); break;
        case 3: text2(F("> Blue"), setblue_read, F("/255"), F("03/03")); break;
        }
        }
        change = false;
    }


void loop() {
  float sensor_volt;
  float exp_in;
  float exp_out;
  float ppm;
  float RS_gas; // Get value of RS in a GAS
  float ratio; // Get ratio RS_GAS/RS_air
  float R0 = 0.32;
  int sensorValue = analogRead(IO4);
  sensor_volt=(float)sensorValue/4096*5.0;
  RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL
  
  /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
  ratio = RS_gas/R0;  // ratio = RS/R0 
  /*-----------------------------------------------------------------------*/
  exp_in = -1.75*(ratio-6.12);
  exp_out = exp(exp_in);
  ppm = exp_out/11.33;
  Serial.print("sensor_volt = ");
  Serial.println(sensor_volt);
  Serial.print("RS_ratio = ");
  Serial.println(RS_gas);
  Serial.print("Rs/R0 = ");
  Serial.println(ratio);
  Serial.print(ppm);
  Serial.println(" ppm");
  Serial.print("\n\n");

  delay(1000);
// END TEST




db = analogRead(DB_READ);
co = analogRead(CO_READ);
Serial.println(co);
 //   delay(100);
if ((buttonStateDown == pressed || buttonStateEnter == pressed || buttonStateLeft == pressed || buttonStateRight == pressed || buttonStateSettings == pressed || buttonStateUp == pressed)) {
sensor_loop();

}

    // BUTTON SETUP
    buttonStateLeft = digitalRead(BUTTON_LEFT);
    buttonStateRight = digitalRead(BUTTON_RIGHT);
    buttonStateSettings = digitalRead(BUTTON_SETTINGS);
    buttonStateUp = digitalRead(BUTTON_UP);
    buttonStateDown = digitalRead(BUTTON_DOWN);
    buttonStateEnter = digitalRead(BUTTON_ENTER);
    ledbrightness_read = ledbrightness;
    ledsaturation_read = ledsaturation;
    setred_read = setred;
    setgreen_read = setgreen;
    setblue_read = setblue;
    ledhue_read = ledhue;
    bouncehue_read = bouncehue;
    blinkdelay_read = blinkdelay;
    bouncedelay_read = bouncedelay;
    fadedelay_read = fadedelay;
    burstdelay_read = burstdelay;
    wavedelay_read = wavedelay;
    
    
    // TEXT DISPLAY
    display_generator();

    // BUTTON LEFT
    if (buttonStateLeft == pressed) {
        button_left();
        button_left_br();
        button_left_rgb();
        while (digitalRead(BUTTON_LEFT) == pressed) {
        }
    }

    // BUTTON RIGHT
    if (buttonStateRight == pressed) {
        button_right();
        button_right_br();
        button_right_rgb();
        while (digitalRead(BUTTON_RIGHT) == pressed) {
        }
    }
        // BUTTON SETTINGS
    if (buttonStateSettings == pressed) {
        button_settings();
        while (digitalRead(BUTTON_SETTINGS) == pressed) {
        }
    }

    // BUTTON UP
    if (buttonStateUp == pressed) {
        button_up();
        button_up_color();
        while (digitalRead(BUTTON_UP) == pressed) {
        }
    }

    // BUTTON DOWN
    if (buttonStateDown == pressed) {
        button_down();
        button_down_color();
        while (digitalRead(BUTTON_DOWN) == pressed) {
        }
    }

    // BUTTON DOWN
    if (buttonStateEnter == pressed) {
        button_enter();
        while (digitalRead(BUTTON_ENTER) == pressed) {
        }
    }


    // LED EFFECT
    if (mode == 0) {
    switch (ledMode) {
    case 255: break;
    case 1: one_color_blink(setred, setgreen, setblue);  break;
    case 2: color_bounce(); break;
    case 3: static_color(setred, setgreen, setblue); break;
    case 4: rainbow_fade(); break;
    case 5: random_burst(); break;
    case 6: rainbow_static(); break;
    case 7: rainbow_wave(); break;
    case 8: random_color_blink(setred, setgreen, setblue); break;
    case 9: short_hue_gradient(); break;
    case 10: hue_gradient(); break;
    case 11: long_hue_gradient(); break;
    case 12: react_sound_r_wave(); break;
    case 13: react_sound_st_color(); break;

    }
    }
}


