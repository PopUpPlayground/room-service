#ifndef UNIT_TEST

#include <Wire.h>

#include "Game.h"
#include "Actor.h"
#include "Map.h"

#include "HwConsole.h"

#ifdef ROOMSERVICE
// Only loaded for production game
#include "RoomService.h"
typedef RoomService game_t;
#else
typedef Game game_t;
#endif

#include "MsgEvent.h"

#define SPEED_MULTIPLY 1

game_t game;
HwConsole hw;

// From https://github.com/adafruit/SD/blob/master/utility/SdFatUtil.h

#define UNUSEDOK __attribute__((unused))

static UNUSEDOK int freeRam(void) {
  extern int  __bss_end;
  extern int* __brkval;
  int free_memory;
  if (reinterpret_cast<int>(__brkval) == 0) {
    // if no heap use from end of bss section
    free_memory = reinterpret_cast<int>(&free_memory)
                  - reinterpret_cast<int>(&__bss_end);
  } else {
    // use from top of stack to heap
    free_memory = reinterpret_cast<int>(&free_memory)
                  - reinterpret_cast<int>(__brkval);
  }
  return free_memory;
}

void consolePrint(const char *string) {
    // Serial.print("[ ");
    // Serial.print(freeRam());
    // Serial.print(" ]");
    Serial.print(string);

    // delay(10);
}

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

void waitStartGame() {
    hw.displayLcd("Press any key","to start.");

    while (true) {
        char key = hw.keypad.getKey();
        if (key != NO_KEY) {
            break;
        }
    }

    hw.displayLcd("Majordomo boot","please wait...");

    delay(90 * 1000);
}

millis_t ram_checkpoint;

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

    waitStartGame();

    Serial.print("\nStarting game....\n");
    Serial.print(game.map.errors.c_str());

    delay(2000);

    // The game assumes we begin with a clear LCD.
    hw.lcd.clear();

    game.start(consolePrint, millis()*SPEED_MULTIPLY);

    ram_checkpoint = millis();
}

void loop() {

    // Display RAM usage.
    
    /*
    if (millis() - ram_checkpoint > (10000/SPEED_MULTIPLY)) {
        Serial.print("Free RAM: ");
        Serial.print(freeRam());
        Serial.print("\n");
        ram_checkpoint = millis();
    }
    */

    // Aww yis, running a game!
    game.tick(consolePrint, millis()*SPEED_MULTIPLY);

    // Running LEDs algorithm:
    // - Clear the entire array of LEDs.
    // - For each actor, find the room they're in, and set that LED to high.
    // - For each lock, find the door it corresponds to, and set LED to high.
    // - Write the LEDs to the hardware.

    hw.updateConsole(&game);

    // Keypad

    std::string input;
    hw.updateKeypad(game.state, &input);

    // Process player input.
    if (! input.empty()) {
        game.processInput(consolePrint, &input);
    }
}

#endif
