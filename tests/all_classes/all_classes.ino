#include <small_timer.hpp>

// base classes:
csTimer                      t1;  // csTimer32bit_12day
csTimerShort                 t2;  // csTimer16bit_16sec
csTimerExt                   t10; // csTimerExt32bit_12day
csTimerShortExt              t11; // csTimerExt16bit_16sec

csTimerDef<1000>             t3;
csTimerShortDef<1000>        t4;

// extended classes:
csTimer8bit_64ms             timer8bit_64ms           ;   // - max 64 ms.
csTimer8bit_128ms_J4ms_Flag  timer8bit_128ms_J4ms_Flag;              // - max 128 ms. div 4. jitter - 4 ms! And support user flag.
csTimer8bit_64sec_J256ms     timer8bit_64sec_J256ms   ;           // - max 64 second. div 256. jitter - 0.25 second! Recomended minimal - 10 second.  Size - 1 byte.
csTimer8bit_1sec_J8ms        timer8bit_1sec_J8ms      ;        // - max 1 second. div 8. jitter - 8 ms. Size - 1 byte.
csTimer16bit_16sec           timer16bit_16sec         ;     // (csTimerShort) - max 16 second.
csTimer16bit_16sec_Flag      timer16bit_16sec_Flag    ;          // - max 8 second. And support user flag.
csTimer16bit_16min_J64ms     timer16bit_16min_J64ms   ;           // - max 16 min. div 64. jitter - 64 ms
csTimer16bit_4hour_J1sec     timer16bit_4hour_J1sec   ;           // - max 279 min (4,5 hour). div 1024. jitter - 1 second.
csTimer32bit_12day           timer32bit_12day         ;     // (csTimer) - max 12,4 day.
csTimer32bit_6day_Flag       timer32bit_6day_Flag     ;         // - max 6 day. And support user flag.
csTimerExt32bit_12day        timerExt32bit_12day      ;        // (csTimerExt) - big timer, max length - 12 day. Size - 4 byte. External time source.
csTimerExt16bit_16sec        timerExt16bit_16sec      ;        // (csTimerShortExt) - short time, max length - 16 second. Size - 2 byte. External time source.

tpTimerSetDefault<csTimer8bit_64ms, 1000>      t14;

void setup() {
  t3.start();
  t4.start();
  t14.start();

  timer8bit_64ms.start(10);
  timer8bit_128ms_J4ms_Flag.start(10);
  timer8bit_64sec_J256ms.start(10);
  timer8bit_1sec_J8ms.start(10);
  timer16bit_16sec.start(1000);
  timer16bit_16sec_Flag.start(1000);
  timer16bit_16min_J64ms.start(1000);
  timer16bit_4hour_J1sec.start(1000);
  timer32bit_12day.start(1000);
  timer32bit_6day_Flag.start(1000);

  timerExt32bit_12day.start(1000, millis());
  timerExt16bit_16sec.start(1000, millis());

}

void loop() {
  t3.run();
  t4.run();
  t14.run();

  timer8bit_64ms.run();
  timer8bit_128ms_J4ms_Flag.run();
  timer8bit_64sec_J256ms.run();
  timer8bit_1sec_J8ms.run();
  timer16bit_16sec.run();
  timer16bit_16sec_Flag.run();
  timer16bit_16min_J64ms.run();
  timer16bit_4hour_J1sec.run();
  timer32bit_12day.run();
  timer32bit_6day_Flag.run();

  timerExt32bit_12day.run(millis());
  timerExt16bit_16sec.run(millis());
}

