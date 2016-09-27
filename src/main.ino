#ifndef UNIT_TEST

#include <Wire.h>

#include "Game.h"
#include "Actor.h"
#include "Map.h"
#include "LockEvent.h"

#include "HwConsole.h"

#ifdef ROOMSERVICE
// Only loaded for production game
#include "RoomService.h"
typedef RoomService game_t;
#else
typedef Game game_t;
#endif

#include "MsgEvent.h"

#define MAX_CODE_LENGTH 16

void consolePrint(const char *string) {
    Serial.print(string);
}

game_t game;
HwConsole hw;

void testLights() {
    Serial.print("LED testing mode activated.\n");
    Serial.print("Press 1 to light a new LED, 2 to reset, 9 to start game.\n");

    hw.clearLights();

    int led = 0;

    while (true) {
        if (Serial.available() > 0) {
            int byte = Serial.read();

            if (byte == '1') {
                Serial.print("Lighting light ");
                Serial.print(led);
                Serial.print("\n");
                hw.tlc.setPWM(led,4095);
                led++;
                hw.tlc.write();
            }
            else if (byte == '2') {
                hw.clearLights();
                led = 0;
            }
            else if (byte == '9') {
                return;
            }
        }
    }
}

void setup() {
    // Our hw object has already done most init for us. :)

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

    Serial.print("Starting game soon");

    for (int i = 0; i < 2; i++) {
        hw.powerLed(LOW);
        delay(1000);
        hw.powerLed(HIGH);
        delay(1000);
        Serial.print(".");
    }

    Serial.print("\nStarting game....\n");

    delay(1000);

    game.start(consolePrint, millis());

    // This locks a door so Shia can't get through it.
    game.events.scheduleEvent(millis() + 5000, new LockEvent ("0702","12345"));
}

void loop() {

    // Aww yis, running a game!
    game.tick(consolePrint, millis());

    // Running LEDs algorithm:
    // - Clear the entire array of LEDs.
    // - For each actor, find the room they're in, and set that LED to high.
    // - For each lock, find the door it corresponds to, and set LED to high.
    // - Write the LEDs to the hardware.

    hw.updateLeds(&game);

    // Keypad

    std::string *input = hw.updateKeypad();

    // Process player input.
    if (input != NULL) {
        Serial.print("Processing: ");
        Serial.print(input->c_str());
        delete input;
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

#endif
