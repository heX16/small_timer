# Small software timers for Arduino (and other MC)

Each timer instance takes 2 or 4 bytes. Not uses hardware timer and not uses interrupts. Timers have different accuracy modes. The count of timers is unlimited.

# This file in other language
0) [Русская документация](README_RUS.md).

## Example:
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

## Example 2 - with default time:
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

## Description

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


## Documentation

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

### Extended functions

**getFlag** - Read user flag bit. If there is no flag support then False is always returned.
Some timer classes may contain a custom flag that the user use at his discretion.

**setFlag** - Write to user flag bit.


