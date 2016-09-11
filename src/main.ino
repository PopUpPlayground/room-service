#ifndef UNIT_TEST

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Adafruit_TLC5947.h>

#include "EventQueue.h"

#define MAX_CODE_LENGTH 16

// Keypad Init

Keypad InitKeypad();

// 0x27 - I2C bus address

LiquidCrystal_I2C   lcd(0x27,2,1,0,4,5,6,7);
Keypad keypad = InitKeypad();

const int Pwr_Led = 13;

// TLC5947 init

// Number, clock, data, latch
const int qty = 2;
const int clock = 14;
const int data = 15;
const int latch = 13;
Adafruit_TLC5947 tlc = Adafruit_TLC5947(qty, clock, data, latch);

// Main event queue
EventQueue events;

void setup() {
    // Turn on the power LED, to show we're running.
    pinMode(Pwr_Led, OUTPUT);
    digitalWrite(Pwr_Led, HIGH);

    // activate LCD module
    lcd.begin (16,2); // for 16 x 2 LCD module
    lcd.setBacklightPin(3,POSITIVE);
    lcd.setBacklight(HIGH);

    lcd.home(); // set cursor to 0,0
    lcd.print("Stay A While"); 
    lcd.setCursor (0,1);        // go to start of 2nd line
    lcd.print("Stay... FOREVER");

    // Init TLC
    tlc.begin();

    // Light up first and last two LEDs.
    tlc.setPWM(0,4095);
    tlc.setPWM(1,4095);
    tlc.setPWM(46,4095);
    tlc.setPWM(47,4095);
    tlc.write();

    // Serial setup
    Serial.begin(9600);

}

// Can almost certainly use a proper string library for this.
char code[MAX_CODE_LENGTH+1] = "\0";
int code_pos = 0;

void consolePrint(const char *string) {
    Serial.print(string);
}

void loop() {

    // Aww yis, let's check our event queue for what's happening!
    events.runEvents(consolePrint, millis());

    // Demonstration that we can read serial,
    // as well as write it. <3
    if (Serial.available() > 0) {
        int byte = Serial.read();

        if (byte == '1') {
            tlc.setPWM(0,4095);
        }
        else {
            tlc.setPWM(0,0);
        }

        tlc.write();
    }

    char key = keypad.getKey();

    if (key != NO_KEY) {
        code[code_pos++] = key;
        Serial.print("Got key: ");
        Serial.println(key);
    }

    // Just some fun player interaction for now. :)
    if (code_pos >= MAX_CODE_LENGTH) {
        lcd.clear();
        lcd.print("Srsly?");
        memset(code, 0, sizeof(code));
        code_pos = 0;
    }
    else if (key == '*') {
        lcd.clear();
        lcd.print("Enter code:");
        lcd.setCursor(0,1);
        lcd.blink();
        memset(code, 0, sizeof(code));
        code_pos = 0;
    }
    else if (key == '#') {
        lcd.noBlink();
        lcd.clear();

        if (! strcmp(code, "1234#")) {
            lcd.print("Safe at last!");
            lcd.setCursor(0,1);

            // Turn off the danger lights.
            tlc.setPWM(0,0);
            tlc.setPWM(1,0);
            tlc.setPWM(46,0);
            tlc.setPWM(47,0);
            tlc.write();
            delay(1000); // NOT FOR PRODUCTION CODE!
            lcd.print("(Shia Labeouf)");

            // Danger lights!
            tlc.setPWM(0,4095);
            tlc.setPWM(1,4095);
            tlc.setPWM(46,4095);
            tlc.setPWM(47,4095);
            tlc.write();
        }
        else {
            lcd.print("You have been");
            lcd.setCursor(0,1);
            lcd.print("eaten by a grue.");
        }

        memset(code, 0, sizeof(code));
        code_pos = 0;
    }
    else if (key != NO_KEY) {
        lcd.print(key);
    }
}

// Keypad

const byte rows = 4;
const byte cols = 3;

char keys[rows][cols] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[rows] = { 10, 5, 6, 8 };
byte colPins[cols] = { 9, 11, 7 };

Keypad InitKeypad() {
    return Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
}

#endif
