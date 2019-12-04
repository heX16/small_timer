#include <small_timer.hpp>

//////////////// Константы ////////////////

constexpr auto pinLight = 5;
constexpr auto pinVent = 6;
//constexpr auto pinLightButton = 7; //todo: добавить поддержку кнопки и таймер антидребезга

constexpr auto cEnable = 1;
constexpr auto cDisable = 0;

constexpr auto cMinute = 1000L*60;

//////////////// Таймеры ////////////////

//NOTE: используется класс csTimerDef - в нем время работы таймера задается при обьявлении.

csTimerDef <60*cMinute * 24>  tLight; // Свет.
csTimerDef <60*cMinute * 8>   tLightWork; // Свет, время работы.
csTimerDef <60*cMinute * 1>   tVent; // Вент.
csTimerDef <30*cMinute>       tVentWork; // Вент, время работы.

//////////////// SETUP ////////////////

void setup() {
  Serial.begin(115200);
  pinMode(pinLight, OUTPUT);
  pinMode(pinVent, OUTPUT);

  // первичный запуск таймеров.
  // ускоренный запуск - после запуска контроллера таймеры отработают через секунду (затем будут работать в обычном режиме)
  tLight.start(1000);
  tVent.start(1000);
}

//////////////// LOOP ////////////////

void loop() {

  // пример работы по состоянию:
  // свет

  if (tLight.run()) {
    // запускаем таймер повторно
    tLight.start();
    // запускаем второй таймер - пока он активен свет будет включен
    tLightWork.start();
  }

  // обработка таймера (заметка: run нельзя вызывать дважды или наоборот не вызывать)
  if (tLightWork.run()) {
  }

  // обновляем свет - новое значение пишеться на каждом скане
  digitalWrite(pinLight, tLightWork.enabled());

  //todo: добавить поддержку включения света по кнопке

  ////////////////

  // пример работы по событию таймера:
  // вентилятор

  if (tVent.run()) {
    tVent.start();
    tVentWork.start();
    digitalWrite(pinVent, cEnable);
  }

  if (tVentWork.run()) {
    digitalWrite(pinVent, cDisable);
  }
}

