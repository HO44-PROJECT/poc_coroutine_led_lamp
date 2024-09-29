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

#ifndef __COR_ON_OFF_H__
#define __COR_ON_OFF_H__

#include <AceRoutine.h>
using namespace ace_routine;

#define POV_MICROS 10000U               // us. The maximum time between two effects during which the eye will not detect any change
#define LIGHT_UP_CHANGE_TIME_MS 2000U   // ms. The time given to light up
#define TURN_OFF_CHANGE_TIME_MS 300U    // ms. The time given to turn off

typedef void (*TRIGGER_PIN)();          // Function pointer type

/// @brief This class inherits COROUTINE capabilies with POV effects to light up and turn off LEDs using a LAMP effect
class Coroutine_Led_Lamp_Fx : public Coroutine
{

public:

    TRIGGER_PIN light_it_up, turn_it_down;    // pointers to functions that actually do the work (ie pinMode calls)

    unsigned int light_up_duration = LIGHT_UP_CHANGE_TIME_MS;   // ms. Total duration of the lighting effect
    unsigned int turn_off_duration = TURN_OFF_CHANGE_TIME_MS;   // ms. Total duration of the turn off effect

    unsigned int light_up_start_delay = 0, light_up_end_delay = 0;  // ms. delays before and after light up
    unsigned int turn_off_start_delay = 0, turn_off_end_delay = 0;  // ms. delays before and after turn off

private:

    // private counters.
    // See the docs: A Coroutine is stackless and therefore cannot preserve local stack variables across multiple calls.
    //               Often the class member variables or function static variables are reasonable substitutes.
    unsigned int _i, _delay;

    // Given the total time to light up and the time for a POV effect, compute the number of iterations required to finish the job
    unsigned int _iterations;

    // Within each iteration, the delay varies by a value in micro-seconds
    unsigned int _base_delay_micros;

    // actions to do (on -> off if switch_on else off -> on)
    TRIGGER_PIN _from, _to;

    // Kind of operation in progress or operation done
    bool _lighting_up = false;

    // Operation has started
    bool _started = false;

public:
    void start(bool light_up);                  // start the effect. Used to trigger COROUTINE

    // Helpers
    void switch_on()  { start(true); }          // light up
    void switch_off() { start(false); }         // turn off
    void reverse()    { start(!_lighting_up); } // reverse switching

    bool ended() { return !_started; }          // Effect has finished

    int runCoroutine() override;
};

#endif // __COR_ON_OFF_H__