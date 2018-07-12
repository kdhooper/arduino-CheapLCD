# CheapLCD Shield

A convenience library for using the SainSmart LCD Keypad Shield V1.0 and compatible shields.

This library extends the LiquidCrystal library, automatically handles pin setup for LCD, backlight, and buttons, and provides an interface to the backlight and buttons.

This library should be compatible with LCD Keypad shields from:

Manufacturer | Model                          | Tested
-------------|--------------------------------|-------
SainSmart    | LCD Keypad Shield V1.0         | &check;
DFRobot      | DFR0009 LCD Shield for Arduino |
HiLetgo      | LCD1602 I/O exp. LCD Keypad Shield for Arduino |
RobotDyne    | LCD keypad Shield, 1602 BLUE LCD display |


## Usage:

Call `begin()` or `begin(bool backlightOnNow, uint8_t backlightLevel)` in your sketch `setup()` function.

After that, use `backlightOn()` and `backlightOff()` to turn the backlight on and off, and `backlightLevel()` to adjust the brightness (0-255 value).
`readButton()` may be used to detect button presses on this shield.

Otherwise, use this exactly the same as the [standard LiquidCrystal class](https://www.arduino.cc/en/Reference/LiquidCrystal).

## Functions

Note: Always call `begin();` or `begin(backlightOnNow, backlightLevel);` before using this library!

---

`begin();`

Initialize LCD Keypad Shield with backlight on full.

---

`begin(backlightOnNow, backlightLevel);`

Initialize LCD Keypad Shield. User specifies whether to turn the backlight on immediately with `backlightOnNow` (`true` or `false`) and the backlight brightness level setting (0-255).

If `backlightOnNow` parameter is specified as `false`, use `backlightOn();` later to turn it on when desired.

---

`backlightOn();`

Turns the backlight on.

---

`backlightOff();`

Turns the backlight off.

---

`backlightLevel(level);`

Sets backlight to a specified brightness value, where `level` is a whole number from 0-255. Can be used at any time after `begin()` or `begin(..)`. Only sets backlight brightness, and will not turn the backlight on or off.

Note: If the backlight is on and `backlightLevel(0);` is called, the display will go dark and can be restored by calling `backlightLevel(x);` where `x` is greater than zero. Calling `backlightLevel(0);` is not recommended due to the confusion it may cause (unless you have a good reason).

---

`CLCD_Button_t button = readButton();`

Reads button array and returns which button was pressed (or none)

*Warning: The hardware cannot tell when multiple buttons are pressed due to the way the buttons are multiplexed on a single analog pin!*

Returns an enum indicating which button is being pressed (or none)

Returns one of:
- BTN_RIGHT
- BTN_UP
- BTN_DOWN
- BTN_LEFT
- BTN_SELECT
- BTN_NONE

## Other Documentation

LCD Keypad pin assignments:

Arduino Pin | LCD Keypad Shield Usage
------------|--------------------------------
A0          | Multiplexed button pin
D4          | LCD DB4
D5          | LCD DB5
D6          | LCD DB6
D7          | LCD DB7
D8          | LCD RS
D9          | LCD E (Enable)
D10         | Backlight Control

The schematic is located in the extras directory and is duplicated as a convenience. I do not own it.
