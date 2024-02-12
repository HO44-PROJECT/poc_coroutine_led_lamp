//
// Railway HO project - Signals - POV lamp effect prototype using Arduino in co-working mode (ie thread emulation)
// https://github.com/HO44-PROJECT/coroutine_led_lamp.git
//
// This code demonstrates how to apply a "lamp" effect on any LED using digital output in co-working mode
// Based on POV, it gives the human eye the impression of a fading effect
// This effect is applied in cooperative mode which means fast-switching to emulate threads using AceRoutine excellent library
//
// see README.md for hardware, configuration, references and explanations
//

#include <Arduino.h>
#include "coroutine_led_lamp_fx.h"

#define GREEN_PIN 4 // Replace this with the proper pin number
#define RED_PIN   5 // Replace this with the proper pin number

Coroutine_Led_Lamp_Fx green, red;

void setup()
{
  pinMode(GREEN_PIN, OUTPUT);
  green.light_it_up  = [](){ digitalWrite(GREEN_PIN, HIGH); };
  green.turn_it_down = [](){ digitalWrite(GREEN_PIN, LOW);  };
  green.light_up_end_delay = 2000; // demo delay
  green.setName("green led");

  pinMode(RED_PIN, OUTPUT);
  red.light_it_up  = [](){ digitalWrite(RED_PIN, HIGH); };
  red.turn_it_down = [](){ digitalWrite(RED_PIN, LOW);  };
  red.light_up_end_delay = 2000;  // demo delay
  red.setName("red led");

  // Very first states
  green.switch_on();

  // See https://github.com/bxparks/AceRoutine/tree/develop/examples/HelloScheduler
  CoroutineScheduler::setup();
}

void loop()
{
  CoroutineScheduler::loop();

  if (green.ended() && red.ended()) {
    green.reverse();
    red.reverse();
  }

}
