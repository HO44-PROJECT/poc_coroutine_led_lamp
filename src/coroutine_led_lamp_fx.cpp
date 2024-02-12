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

#include "coroutine_led_lamp_fx.h"

/// @brief start the lamp effect as specified
/// @param light_up true to light up or false to turn off
void Coroutine_Led_Lamp_Fx::start(bool light_up)
{
    if (light_up == _lighting_up)
        // Nothing to do, already in the desired state
        return;

    _lighting_up = light_up;

    _started = true;
}

/// @brief internal coroutine worker. See https://github.com/bxparks/AceRoutine/blob/develop/examples/HelloManualCoroutine/HelloManualCoroutine.ino
/// @return don't know
int Coroutine_Led_Lamp_Fx::runCoroutine()
{
    COROUTINE_LOOP() {

        // wait for triggering
        COROUTINE_AWAIT(_started);

        // apply delay at startup
        COROUTINE_DELAY(_lighting_up ? light_up_start_delay : turn_off_start_delay);

        // actions to do (on -> off if switch_on else off -> on)
        _from = _lighting_up ? turn_it_down : light_it_up;
        _to   = _lighting_up ? light_it_up  : turn_it_down;

        // Given the total time to light up and the time for a POV effect, compute the number of iterations needed to complete the job
        _iterations = round(1000UL * (_lighting_up ? light_up_duration : turn_off_duration) / POV_MICROS);

        // Within each iteration, the delay varies by a value in micro-seconds
        _base_delay_micros = round(POV_MICROS / _iterations);

        // Loop over given iterations applying POV effect
        // For this to work in COROUTINE mode, every variable should be static or class properties
        for (_i = 0, _delay = 0; _i < _iterations; _i++, _delay += _base_delay_micros)
        {
            _from();
            COROUTINE_DELAY_MICROS(POV_MICROS - _delay);
            _to();
            COROUTINE_DELAY_MICROS(_delay);
        }

        // apply delay at ending
        COROUTINE_DELAY(_lighting_up ? light_up_end_delay : turn_off_end_delay);

        // Job done
        _started = false;
    }

};
