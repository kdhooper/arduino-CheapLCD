/** @file ButtonTest.ino
 *  @brief This example sketch tests the basic LCD, backlight, and button
 *  functionality of the CheapLCD library.
 *
 *  This sketch displays "Hello World!!!" on the LCD for 1 second, then displays
 *  the name of the button being pressed. The backlight is turned on while a
 *  a button is being pressed and turned off when all buttons are released.
 *
 *  @author    Daniel Hooper
 *  @copyright Copyright Daniel Hooper 2018
 *  @date      2018
 *  @license   LGPL. See LICENSE file.
 *
 *  @bug No known bugs.
 */

#include <CheapLCD.h>

CheapLCD lcd;

void setup() {
  // put your setup code here, to run once:
  lcd.begin();

  lcd.clear();
  lcd.write("Hello World!!!");
  delay(1000);
  lcd.backlightOff();
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:

  static CLCD_Button_t lastButton = BTN_NONE;

  CLCD_Button_t newReading = lcd.readButton();

  if (newReading != lastButton) {   // button changed
    lastButton = newReading;
    lcd.clear();

    if (newReading != BTN_NONE) {   // button was pressed
      switch(newReading) {
        case BTN_RIGHT:
          lcd.write("Right");
          break;
        case BTN_UP:
          lcd.write("Up");
          break;
        case BTN_DOWN:
          lcd.write("Down");
          break;
        case BTN_LEFT:
          lcd.write("Left");
          break;
        case BTN_SELECT:
          lcd.write("Select");
          break;
        default:
          lcd.write("ERROR");
          break;
      }

      lcd.backlightOn();

    }
    else {                        // button was released
      lcd.backlightOff();
      lcd.clear();
    }
  }
}
