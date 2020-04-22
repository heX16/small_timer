# Small software timers for Arduino (and other MC)

Each timer instance takes 2 or 4 bytes. Not uses hardware timer and not uses interrupts. Timers have different accuracy modes. The count of timers is unlimited.

These timers are used for non-blocking delay for the Arduino.

# This file in other language
0) [Русская документация](README_RUS.md).

# Example:
````
csTimer myTimer;

void setup() {
  myTimer.start(1000);
}

void loop() {
  if (myTimer.run()) {
    println(F("Tick"));
    myTimer.start(1000);
  }
}

````

Example 2 - with default time:
````
csTimerDef<1000> myTimer;

void setup() {
  myTimer.start();
}

void loop() {
  if (myTimer.run()) {
    println(F("Tick"));
    myTimer.start();
  }
}

````

# Description

The timer can be in two states - started or stopped.
The timer at creation to be with the state is stopped.

To start the timer, you need to call the "**start**" function, and in the parameter specify the required operating time (in millisecond).
On each cycle (loop) must be called "**run**" function (for each timer instance).

If the "**run**" function returns a **True**,  then the timer has expired. If his time has not come yet - he will return **False**.

After working out, the timer goes into a stopped state. If the timer needs to be run again, must call "** start **" function again (see in examples).
If the timer is stopped, calling the "**run**" will always return **False**.

If you use this timers try not to use the "delay" function.
You cannot call the "** run **" twice in the same _instance_ timer in one scan - the second call will not work.
You must not "hide" the "**run**" function call in the condition (see in examples).

To achieve high accuracy, you must call the "**run**" method
for all timers as often as possible (1000 times per second is recomended minimum).
If your "loop" procedure does not contain slow and blocking functions,
then you don’t need to specifically worry about this -
the "loop" procedure is called quite often and quickly.

# Documentation

Timer classes:

1) **csTimer** - big timer, max length - 12 day. Size - 4 byte.

2) **csTimerShort** - short time, max length - 16 second. Size - 2 byte.

3) **csTimerDef** - analog csTimer but with default time support. Size - 4 byte.

4) **csTimerShortDef** - analog csTimerShort but with default time support. Size - 2 byte.

Functions in classes (for all classes):

**start** - Start timer. If the timer is already running, the timer restarts.

**startOnce** - Start timer. If the timer is already running then restarting does not occur.

**stop** - timer stop.

**enabled** - read the status of the timer. if started, returns True.

**run** - Main function. Must be called in every cycle. If the timer has worked, then True is returned once.

## Extended timers set and info

Additional 10 classes of timers with different accuracy and a minimum size of 1 byte.

Attention: only for professionals! Additional testing required.

[Extended timers set list](extended_info.md)

# More examples

[Examples of how to write code correctly](extended_info.md#Examples)

# Notes

These timers take into account ["millis overflow"](https://forum.arduino.cc/index.php?topic=68349.0) ([millis rollover](https://www.faludi.com/2007/12/18/arduino-millis-rollover-handling/) ) and process it correctly.

Using **csTimerDef** does not increase the size of the timer. **csTimer** and **csTimerDef** are indeed the same size. This is due to the fact that the default time is stored in code (FLASH) and not in RAM (SRAM).

# Technical details - how the "run" function works

`if (((TTimer) ((TTimer) (TIMER_GET_TIME / PrecDiv) - timer) & BitMask) <MaxValue) {...`

How it works?

Cleared entry: `if ((TIMER_GET_TIME - timer) <MaxValue) {...`

In a normal situation, the number becomes negative (if the timer has not yet reached the activation time). But an unsigned integer is used here, so overflow occurs. Overflow gives a large number. "Overflow numbers" are considered to be all that exceed half the possible range (this is similar to "signed int" at the binary level). To determine the overcrowded number, the constant "MaxValue" is used.

As soon as the number becomes less than “overflowed”, this means that the number is no longer negative, and this means that the timer has reached activation time.

Why am I not using regular numbers? - because in this project binary operations and bit masks are actively used, I need to completely control the binary system.

