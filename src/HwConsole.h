#ifndef HWCONSOLE_H
#define HWCONSOLE_H

#ifndef UNIT_TEST

#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_TLC5947.h>
#include <string>

class Game;

class HwConsole {
    private:
        const byte tlcQty = 4;

        const byte pwrLed   = 13;
        const byte tlcLatch = 14;
        const byte tlcClock = 15;
        const byte tlcData  = 16;

        const byte lcdAddr = 0x27;

        std::string playerInput;

        Keypad InitKeypad();
        Adafruit_TLC5947 InitTLC5947();
        LiquidCrystal_I2C InitLCD();

    public:
        Keypad keypad;
        Adafruit_TLC5947 tlc;
        LiquidCrystal_I2C lcd;

        HwConsole()
            :playerInput(""), keypad(InitKeypad()), tlc(InitTLC5947()), lcd(InitLCD())
        {
            Serial.begin(9600);
            pinMode(pwrLed, OUTPUT);
            powerLed(HIGH);

            clearLights();
        }

        void resetLights();
        void clearLights();
        void powerLed(uint8_t);
        void updateLeds(Game *game);
        void updateKeypad();
};

#endif  // UNIT_TEST

#endif
