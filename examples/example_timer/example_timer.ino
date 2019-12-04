#include <small_timer.hpp>

constexpr auto pinDbgLed = 13;

csTimer tProc1;
csTimer tProc2;
csTimer tCount;

constexpr auto cTimeProc1 = 1000L * 3; // - 3 sec
constexpr auto cTimeProc2 = 1000L * 10; // - 10 sec
// examples:
//   50 ms:   50
//   8 hour:  1000L * 60 * 60 * 8
//   12 day:  1000L * 60 * 60 * 24 * 12 (WARNING - 12 day is maximal pause interval)



uint32_t lifeCount = 0;

bool proc1enabled = false;

////-////-////-//// PROC 1 ////-////-////-////

void proc1() {
  Serial.println(F("proc1"));

  proc1enabled = ! proc1enabled;
  if (proc1enabled) {
    digitalWrite(pinDbgLed, 1);
  } else {
    digitalWrite(pinDbgLed, 0);
  }
}

////-////-////-//// PROC 2 ////-////-////-////

void proc2() {
  Serial.println(F("proc2"));
}

////-////-////-//// SETUP ////-////-////-////

void setup() {
  Serial.begin(115200);
  pinMode(pinDbgLed, OUTPUT);

  tProc1.start(cTimeProc1);
  tProc2.start(cTimeProc2);
  tCount.start(1000);
}

////-////-////-//// LOOP ////-////-////-////

void loop() {
  if (tProc1.run()) {
    tProc1.start(cTimeProc1);
    proc1();
  }

  if (tProc2.run()) {
    tProc1.start(cTimeProc2);
    proc2();
  }

  if (tCount.run()) {
    tCount.start(1000);
    lifeCount++;
    Serial.println(lifeCount);
  }
}

