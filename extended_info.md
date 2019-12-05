
# Extended timers set

0) **csTimer8bit_64ms** - max 64 ms.

0) **csTimer8bit_128ms_J4ms_Flag** - max 128 ms. div 4. jitter - 4 ms! And support user flag.

0) **csTimer8bit_64sec_J256ms** - max 64 second. div 256. jitter - 0.25 second! Recomended minimal - 10 second.  Size - 1 byte.

0) **csTimer8bit_1sec_J8ms** - max 1 second. div 8. jitter - 8 ms. Size - 1 byte.

0) **csTimer16bit_16sec** - max 16 second.

0) **csTimer16bit_16sec_Flag** - max 8 second. And support user flag.

0) **csTimer16bit_16min_J64ms** - max 16 min. div 64. jitter - 64 ms

0) **csTimer16bit_4hour_J1sec** - max 279 min (4,5 hour). div 1024. jitter - 1 second.

0) **csTimer32bit_12day** - max 12,4 day.

0) **csTimer32bit_6day_Flag** - max 6 day. And support user flag.



# Extended functions

**getFlag** - Read user flag bit. If there is no flag support then False is always returned.
Some timer classes may contain a custom flag that the user use at his discretion.
(see: __csTimer32bit_6day_Flag__ and other extended classes).

**setFlag** - Write to user flag bit.


# Examples

bad code example and correct code example

----------------

Function **run** must run one time to one timer in loop.

````
    // BAD code:
    if (t.run()) {
      // code 1 ...
    };
    // ...
    if (t.run()) {
      // code 2 ...
    };
````

````
    // good code:
    bool t_ok = t.run();

    if (t_ok) {
      // code 1 ...
    };
    // ...
    if (t_ok) {
      // code 2 ...
    };
````

----------------

````
    // BAD code:
    if (xxx && t.run()) {
      // code ...
    };
````

````
    // good code:
    bool t_ok = t.run();
    if (xxx && t_ok) {
      // code ...
    };
````

----------------

````
    // BAD code:
    if (t1.run() && t2.run()) {
      // code ...
    };
````

````
    // BAD code:
    if (t1.run() || t2.run()) {
      // code ...
    };
````

````
    // good code:
    bool t1_ok = t1.run();
    bool t2_ok = t2.run();
    if (t1_ok || t2_ok) {
      // code 1 ...
    };
````

----------------

````
    // BAD code:
    x.run();
    delay(20000); // - not use blocking operation
    do_after_pause();
````

````
    // good code:
    x.run();
    pause20s.startOnce(20000);
    if (pause20s.run())
      { do_after_pause(); }
````

````
    // BAD code:
    x.run();
    c = Serial.read(); // - infinity wait char, is blocking operation
````

````
    // good code:
    x.run();
    if (Serial.aviable() > 0)
      c = Serial.read();
````

