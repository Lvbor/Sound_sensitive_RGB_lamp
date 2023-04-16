#include <Arduino.h>


// INITIAL VALUES
#define NUM_LEDS 60
#define COLOR_TYPE_LED GRB
#define LED_STRIP WS2812B
#define BRIGHTNESS 255
#define SATURATION 255
#define HUE 0
#define OP_VOLTAGE 5 // V
#define MAX_CURRENT 500 // mA
#define SAFETY_DELAY 500
#define BLINK_DELAY 300
#define BOUNCE_DELAY 30
#define FADE_DELAY 15
#define BURST_DELAY 50
#define WAVE_DELAY 25
#define RED 255
#define GREEN 255
#define BLUE 255
#define HUE_START 170
#define BOUNCE_HUE 70

// BUTTON
#define DATA_PIN_LED IO16
#define BUTTON_LEFT IO17
#define BUTTON_RIGHT IO27
#define BUTTON_UP IO14
#define BUTTON_DOWN IO12
#define BUTTON_SETTINGS IO26
#define BUTTON_ENTER IO25
#define DB_READ IO2
#define CO_READ IO4

// EEPROM SETUP
#define EEPROM_INIT 14
#define FIRST_BOOT_E 0

// BUTTON 
boolean buttonStateLeft = digitalRead(BUTTON_LEFT);
boolean buttonStateRight = digitalRead(BUTTON_RIGHT);
boolean buttonStateSettings = digitalRead(BUTTON_SETTINGS);
boolean buttonStateUp = digitalRead(BUTTON_UP);
boolean buttonStateDown = digitalRead(BUTTON_DOWN);
boolean buttonStateEnter = digitalRead(BUTTON_ENTER);
boolean change = false;
boolean pressed = true;

// LED 
byte ledchanger = 0;
byte ledMode = 0;
boolean shift = true;
byte ledhue = HUE;

// RGB SETTINGS
byte setred = RED;
byte setgreen = GREEN;
byte setblue = BLUE;

// SETTINGS
byte settings = 1;
byte ledsaturation = SATURATION;
byte ledbrightness = BRIGHTNESS;
byte startgradient = HUE_START;
byte bouncehue = BOUNCE_HUE;
int blinkdelay = BLINK_DELAY;
int bouncedelay = BOUNCE_DELAY;
int fadedelay = FADE_DELAY;
int burstdelay = BURST_DELAY;
int wavedelay = WAVE_DELAY;
int mode = 0;
byte ledbrightness_read = ledbrightness;
byte ledsaturation_read = ledsaturation;
byte setred_read = setred;
byte setgreen_read = setgreen;
byte setblue_read = setblue;
byte ledhue_read = ledhue;
byte color = 1;
byte bouncehue_read = bouncehue;
int blinkdelay_read = blinkdelay;
int bouncedelay_read = bouncedelay;
int fadedelay_read = fadedelay;
int burstdelay_read = burstdelay;
int wavedelay_read = wavedelay;
int db = digitalRead(DB_READ);
byte bootstate = FIRST_BOOT_E;
byte reactdelay = 0;
byte reacthue = 0;
int react_stabilizer = 0;
int co = 0;
float temp = 0;
int temp_read = 0;
float pressure = 0;
int pressure_read = 0;
float altitude_read = 0;
char degree = 247;
float p_calc = 0;
float p_calc2 = 0;
int humidity_read = 0; 
char prct = 37;

// TIME
byte hh = 0;
byte mm = 0;
byte ss = 0;
byte dd = 0;
byte mth = 0;
int yr = 0;

// GIFS
byte loading = 0;