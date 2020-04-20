#include <small_timer.hpp>

csTimer tBlink;
bool ledState;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  tBlink.start(1000);
}

void loop() {
  if (tBlink.run()) {
    tBlink.start(1000);

    ledState = ! ledState;
    digitalWrite(LED_BUILTIN, ledState);
  }
}





/*
Other correct variant:

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  tBlink.startOnce(1000);
  if (tBlink.run()) {
    ledState = ! ledState;
    digitalWrite(LED_BUILTIN, ledState);
  }
}
*/
