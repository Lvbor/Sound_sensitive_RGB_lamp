#include <Arduino.h>
#include <EEPROM.h>

void button_setup() {
    pinMode(DATA_PIN_LED, OUTPUT);
    pinMode(DB_READ, INPUT);
    pinMode(BUTTON_DOWN, INPUT);
    pinMode(BUTTON_ENTER, INPUT);
    pinMode(BUTTON_LEFT, INPUT);
    pinMode(BUTTON_RIGHT, INPUT);
    pinMode(BUTTON_SETTINGS, INPUT);
    pinMode(BUTTON_UP, INPUT);
}

// BUTTONS

// BUTTON LEFT EFFECT
void button_left() {
    if (ledMode > 1 & mode == 0) {
        ledMode--;
        change = true;
    }
    else {
        ledMode = 13;
        change = true;
    }
}

// BUTTON SETTINGS EFFECT
void button_settings() {
    if (mode == 0) {
        settings_gif();
        mode++;
        change = true;
    }
    else if (mode == 1) {
		saved_gif();
        mode--;
        change = true;
    }
}

// BUTTON ENTER EFFECT
void button_enter() {
    if (mode == 1 & settings != 3) {
        mode++;
        change = true;
    }
    else if (mode == 2 & settings != 3) {
        mode--;
        switch (settings)
        {
        case 1: EEPROM.write(1, ledbrightness); break;
        case 2: EEPROM.write(2, ledsaturation); break;
        case 4: EEPROM.write(6, ledhue); break;
        case 5: EEPROM.write(7, bouncehue); break;
        case 6: EEPROM.write(8, blinkdelay/5); break;
        case 7: EEPROM.write(9, bouncedelay/5); break;
        case 8: EEPROM.write(10, fadedelay/5); break;
        case 9: EEPROM.write(11, burstdelay/5); break;
        case 10: EEPROM.write(12, wavedelay/5); break;
        }
        EEPROM.commit();
        change = true;
    }
    else if (mode == 1  & settings == 3){
            mode+=2;
            change = true;
        }
    else if (mode == 3  & settings == 3){
            mode+=1;
            change = true;
        }
    else if (mode == 4 & settings == 3) {
        mode-=3;
        EEPROM.write(3, setred); 
        EEPROM.write(4, setgreen); 
        EEPROM.write(5, setblue); 
        EEPROM.commit();
        change = true;
    }
}

// BUTTON RIGHT EFFECT
void button_right() {
    if (ledMode < 13 & mode == 0) {
        ledMode++;
        change = true;
    }
    else {
        ledMode = 1;
        change = true;
    }
}

// BUTTON DOWN EFFECT
void button_down() {
    if (settings > 1 & mode == 1) {
        settings--;
        change = true;
    }
    else if (settings == 1 & mode == 1) {
        settings = 11;
        change = true;
    }
}

// BUTTON UP EFFECT
void button_up() {
    if (settings < 11 & mode == 1) {
        change = true;
        settings++;
    }
    else if (settings == 11 & mode == 1) {
        settings = 1;
        change = true;
    }
}

// BUTTON DOWN EFFECT
void button_down_color() {
    if (color > 1 & mode == 4) {
        color--;
        change = true;
    }
    else {
        color = 3;
        change = true;
    }
}

// BUTTON UP EFFECT
void button_up_color() {
    if (color < 3 & mode == 4) {
        change = true;
        color++;
    }
    else {
        color = 1;
        change = true;
    }
}

// BUTTON LEFT SETTINGS
void button_left_br() {
    if (mode == 2) {
        switch (settings)
        {
        case 1: ledbrightness--; break;
        case 2: ledsaturation--; break; 
        case 4: ledhue--; break;
        case 5: bouncehue--; break;
        case 6: if (blinkdelay > 0) blinkdelay-=5; break;
        case 7: if (bouncedelay > 0) bouncedelay-=5; break;
        case 8: if (fadedelay > 0) fadedelay-=5; break;
        case 9: if (burstdelay > 0) burstdelay-=5; break;
        case 10: if (wavedelay > 0) wavedelay-=5; break;
        }
        change = true;
    }
}

// BUTTON RIGHT SETTINGS
void button_right_br() {
    if (mode == 2) {
        switch (settings)
        {
        case 1: ledbrightness++; break;
        case 2: ledsaturation++; break;
        case 4: ledhue++; break;
        case 5: bouncehue++; break;
        case 6: if (blinkdelay < 1250) blinkdelay+=5; break;
        case 7: if (bouncedelay < 1250) bouncedelay+=5; break;
        case 8: if (fadedelay < 1250) fadedelay+=5; break;
        case 9: if (burstdelay < 1250) burstdelay+=5; break;
        case 10: if (wavedelay < 1250) wavedelay+=5; break;
        }
        change = true;
    }
}

// BUTTON LEFT SETTINGS
void button_left_rgb() {
    if (mode == 4 & settings == 3) {
        switch (color)
        {
        case 1: setred--; break;
        case 2: setgreen--; break; 
        case 3: setblue--; break; 
        }
        change = true;
    }
}

// BUTTON RIGHT SETTINGS
void button_right_rgb() {
    if (mode == 4 & settings == 3) {
        switch (color)
        {
        case 1: setred++; break;
        case 2: setgreen++; break;
        case 3: setblue++; break;
        }
        change = true;
    }
}
