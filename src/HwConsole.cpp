#ifndef UNIT_TEST

#include "HwConsole.h"
#include "Game.h"
#include "Actor.h"

// Lots of magic numbers ahead!
// Static is needed sometimes so we don't deallocate things after returning.
Keypad HwConsole::InitKeypad() {
    const byte rows = 4;
    const byte cols = 3;

    static char keys[rows][cols] = {
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'},
        {'*','0','#'}
    };

    static byte rowPins[rows] = { 10, 5, 6, 8 };
    static byte colPins[cols] = { 9, 11, 7 };

    return Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
}

Adafruit_TLC5947 HwConsole::InitTLC5947() {
    return Adafruit_TLC5947(tlcQty, tlcClock, tlcData, tlcLatch);
}

LiquidCrystal_I2C HwConsole::InitLCD() {
    // Not sure what these magic numbers mean, but they work.
    return LiquidCrystal_I2C(lcdAddr,2,1,0,4,5,6,7);
}

// Sets the power LED.
void HwConsole::powerLed(uint8_t val) {
    digitalWrite(pwrLed, val);
}

void HwConsole::resetLights() {
    int lights = tlcQty * 24;       // 24 lights per board

    for (int i = 0; i < lights; i++) {
        tlc.setPWM(i,0);
    }
}

void HwConsole::clearLights() {
    resetLights();
    tlc.write();
}

void HwConsole::updateLeds(Game *game) {

    // Only update if something has changed.

    if (game->dirty == false) {
        return;
    }

    // Reset our light state...
    resetLights();

    // Display our actor locations.
    for (actors_t::iterator i = game->actors.begin(); i != game->actors.end(); ++i) {
        led_t led = game->map.map[ (*i)->room ]->led;

        if (led >= 0) {
            tlc.setPWM(led,4095);
        }
    }

    // TODO: Display door locks
    
    tlc.write();

    // Game state has now been displayed to user and is no longer dirty.
    game->dirty = false;
}

void HwConsole::updateKeypad() {
    char key = keypad.getKey();

    if (key == NO_KEY) {
        return;
    }

    if (key == '*') {
        // Reset key
        playerInput = "";
    }
    else if (key == '#') {
        // TODO: Process key string
    }
    else {
        playerInput += key;
    }

    Serial.print("Player input is: ");
    Serial.println(playerInput.c_str());

}

#endif // UNIT_TEST
