#ifndef UNIT_TEST

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Adafruit_TLC5947.h>

#include "Game.h"
#include "Actor.h"
#include "Map.h"
#include "LockEvent.h"

#ifdef ROOMSERVICE
// Only loaded for production game
#include "RoomService.h"
typedef RoomService game_t;
#else
typedef Game game_t;
#endif

#include "MsgEvent.h"

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
const int latch = 14;
const int clock = 15;
const int data = 16;
Adafruit_TLC5947 tlc = Adafruit_TLC5947(qty, clock, data, latch);

void consolePrint(const char *string) {
    Serial.print(string);
}

game_t game;

void clearLights() {
    const int lights = 47;

    for (int i = 0; i <= lights; i++) {
        tlc.setPWM(i,0);
    }
    tlc.write();
}

void testLights() {
    Serial.print("LED testing mode activated.\n");
    Serial.print("Press 1 to light a new LED, 2 to reset, 9 to start game.\n");

    // clearLights();

    int led = 0;

    while (true) {
        if (Serial.available() > 0) {
            int byte = Serial.read();

            if (byte == '1') {
                Serial.print("Lighting light ");
                Serial.print(led);
                Serial.print("\n");
                tlc.setPWM(led,4095);
                led++;
                tlc.write();
            }
            else if (byte == '2') {
                clearLights();
                led = 1;
            }
            else if (byte == '9') {
                return;
            }
        }
    }
}

void setup() {
    // Turn on the power LED, to show we're running.
    pinMode(Pwr_Led, OUTPUT);
    digitalWrite(Pwr_Led, HIGH);

    // Serial setup
    Serial.begin(9600);

    // Init TLC
    Serial.print("Initialising TLC\n");
    tlc.begin();

    Serial.print("Waiting for human\n");
    delay(2000);

    testLights();

    /*

    // activate LCD module
    lcd.begin (16,2); // for 16 x 2 LCD module
    lcd.setBacklightPin(3,POSITIVE);
    lcd.setBacklight(HIGH);

    lcd.home(); // set cursor to 0,0
    lcd.print("Stay A While"); 
    lcd.setCursor (0,1);        // go to start of 2nd line
    lcd.print("Stay... FOREVER");

    */

    clearLights();

    Serial.print("Starting game soon");

    for (int i = 0; i < 2; i++) {
        digitalWrite(Pwr_Led, LOW);
        delay(1000);
        digitalWrite(Pwr_Led, HIGH);
        delay(1000);
        Serial.print(".");
    }

    Serial.print("\nStarting game....\n");

    delay(1000);

    game.start(consolePrint, millis());

    // This locks a door so Shia can't get through it.
    game.events.scheduleEvent(millis() + 5000, new LockEvent ("0702","12345"));
}

// Can almost certainly use a proper string library for this.
char code[MAX_CODE_LENGTH+1] = "\0";
int code_pos = 0;

void updateLeds(Game *game) {
    clearLights();
    
    for (actors_t::iterator i = game->actors.begin(); i != game->actors.end(); ++i) {
        led_t led = game->map.map[ (*i)->room ]->led;

        if (led >= 0) {
            tlc.setPWM(led,4095);
        }
    }
    tlc.write();

}

void loop() {

    // Aww yis, running a game!
    game.tick(consolePrint, millis());

    // Running LEDs algorithm:
    // - Clear the entire array of LEDs.
    // - For each actor, find the room they're in, and set that LED to high.
    // - For each lock, find the door it corresponds to, and set LED to high.
    // - Write the LEDs to the hardware.

    updateLeds(&game);

    // Keypad

    char key = keypad.getKey();

    if (key != NO_KEY) {
        // code[code_pos++] = key;
        Serial.print("Got key: ");
        Serial.println(key);
    }

    /*

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

    */
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
