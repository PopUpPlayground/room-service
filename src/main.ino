#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

Keypad InitKeypad();

// 0x27 - I2C bus address

LiquidCrystal_I2C   lcd(0x27,2,1,0,4,5,6,7);
Keypad keypad = InitKeypad();

const int Pwr_Led = 13;

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
}

void loop() {
    char key = keypad.getKey();

    if (key != NO_KEY) {
        lcd.home();
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
