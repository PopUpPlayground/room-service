#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// 0x27 - I2C bus address

LiquidCrystal_I2C   lcd(0x27,2,1,0,4,5,6,7);

const int Pwr_Led = 13;

void setup() {
    // Turn on the power LED, to show we're running.
    pinMode(Pwr_Led, OUTPUT);
    digitalWrite(Pwr_Led, HIGH);

    // activate LCD module
    lcd.begin (16,2); // for 16 x 2 LCD module
    lcd.setBacklightPin(3,POSITIVE);
    lcd.setBacklight(HIGH);
}

void loop() {
    lcd.home(); // set cursor to 0,0
    lcd.print("Stay A While"); 
    lcd.setCursor (0,1);        // go to start of 2nd line
    lcd.print("Stay... FOREVER");
}
