/** @file CheapLCD.h
 *  @brief A convenience library for using the SainSmart LCD Keypad Shield V1.0 and similar
 *
 *  The CheapLCD is a subclass of the LiquidCrystal library, so the user
 *  can use this class instead of the LiquidCrystal object transparently.
 *
 *  This library automatically sets up the required LCD, backlight, and button
 *  pins so that the LCD Keypad Shield should work right out of the box.
 *
 *  @author    Daniel Hooper
 *  @copyright Copyright Daniel Hooper 2018
 *  @date      2018
 *  @license   LGPL. See LICENSE file.
 *
 *  @bug No known bugs.
 */

#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>

#define CLCD_KBD_PIN  A0   ///< A0

#define CLCD_DB4_PIN  4   ///< D4
#define CLCD_DB5_PIN  5   ///< D5
#define CLCD_DB6_PIN  6   ///< D6
#define CLCD_DB7_PIN  7   ///< D7

#define CLCD_RS_PIN   8   ///< D8
#define CLCD_E_PIN    9   ///< D9

#define CLCD_BACKLIGHT_PIN  10  ///< D10

/**
 * This enum is used to identify which button of the
 * LCD Keypad Shield was pressed.
 */
typedef enum {
  BTN_NONE = 0,
  BTN_RIGHT,
  BTN_UP,
  BTN_DOWN,
  BTN_LEFT,
  BTN_SELECT
} CLCD_Button_t;

/**
 * A class to control the LCD Keypad Shield.
 *
 * This class extends LiquidCrystal and hides implementation details of this
 * shield so that it's not necessary to know the connection and hardware
 * details of this shield to use it.
 *
 * Usage:
 * Call begin() or begin(bool backlightOnNow, uint8_t backlightLevel) in your
 * sketch setup() function.
 * After that, use backlightOn() and backlightOff() to turn the backlight on
 * and off, and backlightLevel() to adjust the brightness.
 * readButton() may be used to detect button presses on this shield.
 * Otherwise, use this exactly the same as the standard LiquidCrystal class.
 */
class CheapLCD : public LiquidCrystal {

private:

  uint8_t mBacklightLevel;
  bool    mBacklightOn;

  void setupPins(void) {
    digitalWrite(CLCD_BACKLIGHT_PIN, LOW);
    pinMode(CLCD_BACKLIGHT_PIN, OUTPUT);
    pinMode(CLCD_KBD_PIN, INPUT);
  }

  void setBacklight(void) {
    if (mBacklightOn) analogWrite(CLCD_BACKLIGHT_PIN, mBacklightLevel);
    else              digitalWrite(CLCD_BACKLIGHT_PIN, LOW);
  }

public:

  CheapLCD(void) : LiquidCrystal( CLCD_RS_PIN,
                                      CLCD_E_PIN,
                                      CLCD_DB4_PIN,
                                      CLCD_DB5_PIN,
                                      CLCD_DB6_PIN,
                                      CLCD_DB7_PIN) { }

  /**
   * Initialize LCD Keypad Shield with backlight on full
   */
  void begin(void)             {begin(true, 255);}

  /**
   * Initialize LCD Keypad Shield
   *
   * If backlightOn parameter is specified as 'false', use backlightOn() or
   * backlightBrightness() later to turn it on when desired.
   * @param backlightOnNow true to immeidately enable backlight.
   * @param backlightLevel A value 0-255 that sets backlight brightness.
   */
  void begin(bool backlightOnNow, uint8_t backlightLevel) {
    mBacklightLevel = backlightLevel;
    if (backlightOnNow) mBacklightOn = true;
    else                mBacklightOn = false;
    setupPins();
    setBacklight();
    LiquidCrystal::begin(16,2);
  }

  /** Turns the backlight on */
  void backlightOn (void)      { mBacklightOn = true; setBacklight();  }
  /** Turns the backlight off */
  void backlightOff(void)      { mBacklightOn = false; setBacklight(); }

  /**
   * Sets backlight to a specified brightness value. Does not affect backlight
   * on/off state.
   * @param level Desired brightness, 0-255
   */
  void backlightLevel(uint8_t level) { mBacklightLevel = level; }

  /**
   * Sets backlight to a specified brightness value. Does not affect backlight
   * on/off state.
   *
   * This funciton signature keeps the compiler from complaining about bad casts from literals.
   * @param level Desired brightness, 0-255
   */
  void backlightLevel(int level) {
    if (level > 255)    level = 255;
    else if (level < 0) level = 0;
    backlightLevel(uint8_t(level));
  }

  /**
   * Reads button array and returns which button was pressed (or none)
   * @warning    The hardware cannot tell when multiple buttons are pressed.
   * @return     Which button is being pressed (or none)
   */
  CLCD_Button_t readButton(void) {

    uint16_t adcValue = analogRead(CLCD_KBD_PIN);

    if      (adcValue < 75)    return BTN_RIGHT;
    else if (adcValue < 250)   return BTN_UP;
    else if (adcValue < 400)   return BTN_DOWN;
    else if (adcValue < 600)   return BTN_LEFT;
    else if (adcValue < 900)   return BTN_SELECT;
    else                       return BTN_NONE;
  }

};
