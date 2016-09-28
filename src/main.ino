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
    Serial.print("testing mode activated.\n");
    Serial.print("Press 1 to light a new LED, 2 to reset, 3 to stress, 4 to clear, 9 to start game.\n");

    hw.displayLcd("LED testing","Aww yis!");

    hw.tlc.begin();
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

                if (led >= 1) {
                    hw.tlc.setPWM(led-1,0);
                }

                led++;
                hw.tlc.write();
            }
            else if (byte == '2') {
                hw.clearLights();
                led = 0;
            }
            else if (byte == '3') {
                for (int i = 0; i < 5*24; i++) {
                    hw.tlc.setPWM(i,4095);
                }
                hw.tlc.write();
            }
            else if (byte == '4') {
                for (int i = 0; i < 5*24; i++) {
                    hw.tlc.setPWM(i,0);
                }
                hw.tlc.write();
            }
            else if (byte == '9') {
                hw.clearLights();
                return;
            }
        }
    }
}

void setup() {
    // Our hw object has already done most init for us. :)

    // testLights();

    Serial.print("Starting game soon");
    hw.displayLcd("Reticulating","splines...");

    // This is just giving the GM time to connect.
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

    hw.updateConsole(&game);

    // Keypad

    std::string *input = hw.updateKeypad(game.state);

    // Process player input.
    if (input != NULL) {
        game.processInput(input);
        delete input;
    }
}

#endif
