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

void HwConsole::disableLights() {
    digitalWrite(tlcOE,HIGH);
}

void HwConsole::enableLights() {
    digitalWrite(tlcOE,LOW);
}

void HwConsole::updateConsole(Game *game) {
    if (game->dirty == false) {
        return;
    }

    updateLeds(game);
    updateLCDs(game);

    // Game state has now been displayed to user and is no longer dirty.
    game->dirty = false;
}

void HwConsole::updateLCDs(Game *game) {
    if (game->state == WAIT_PUZZLE) {
        displayLcd("Enter code...");
    } 
    else if (game->state == WAIT_CODE) {
        displayLcd("Enter door...");
    } 
    else if (game->state == DISPLAY_MSG) {
        displayLcd(game->displayMsg);
    }
    else {
        // Uh oh, something is wrong.
        displayLcd("Someone set us","up the bomb");
    }
}

void HwConsole::updateLeds(Game *game) {

    // Reset our light state...
    resetLights();

    // Display our actor locations.
    for (actors_t::iterator i = game->actors.begin(); i != game->actors.end(); ++i) {
        led_t led = game->map.map[ (*i)->room ]->led;

        if (led >= 0) {
            tlc.setPWM(led,4095);
        }
    }

    for (
        locks_t::iterator i = game->map.locks.locks.begin();
        i != game->map.locks.locks.end();
        ++i
    ) {
        led_t led = game->map.getPortalLed(i->first);
        if (led >= 0) {
            tlc.setPWM(led,4095);
        }
    }
    
    tlc.write();
}

void HwConsole::updateKeypad(game_state_t state, std::string *out) {

    assert(out != NULL);

    // If we're displaying a message, then disable the keypad.
    if (state == DISPLAY_MSG) {
        return;
    }

    char key = keypad.getKey();

    if (key == NO_KEY) {
        return;
    }

    if (key == '*') {
        // Reset key
        playerInput = "";
    }
    else if (key == '#') {
        *out = playerInput; // Return code to game
        playerInput = "";
    }
    else {
        playerInput += key;
    }

    displayLcdCode(playerInput.c_str());

    // Serial.print("Player input is: ");
    // Serial.println(playerInput.c_str());

    return;
}

// TODO: Actually use the target (we will have multiple LCDs)
void HwConsole::displayLcd(const char *line1, const char *line2, byte target) {
    lcd.clear();
    lcd.home();
    lcd.print(line1);
    if (line2 != NULL) {
        lcd.setCursor(0,1);
        lcd.print(line2);
    }
}

void HwConsole::displayLcd(const std::string line1, const std::string line2, byte target) {
    displayLcd(line1.c_str(), line2.c_str());
}

void HwConsole::displayLcd(strpair_t msg, byte target) {
    displayLcd(msg.first, msg.second, target);
}

// Displays a code on the second line of the LCD, leaving the first unchanged.
void HwConsole::displayLcdCode(const char *code) {
    lcd.setCursor(0,1); // Second line.
    lcd.print("               ");   // Ugly, but clears the line.
    lcd.setCursor(0,1);
    lcd.print(code);
}

#endif // UNIT_TEST
