# Railway HO project - Signals - POV lamp effect prototype using Arduino digital output in co-working mode

This code demonstrates how to apply a "lamp" effect on any LED using digital output in co-working mode (ie multi-threading emulation)

## The Goal

As part of my model train project, I want to build DB railway signals from era III.

In order to limit the number of wires on signals up to 10 LEDs, I wanted to build my own system based on charlieplexing, drawing inspiration from the Viessmann multiplex and a simplified PCB, controlled by Arduino with incandescent lamp effects.

The goal of this proof of concept is to be able to emulate threads to control several signals to which an effect involving delays is applied.

## The effect

Based on POV, it gives the human eye the impression of a fading effect. By changing the switching on and off of an LED very quickly and varying the delays, it is possible to give the impression of gradual switching on or off as seen on a filament lamp.

## Thread emulation

Arduino has no threads. I tried https://github.com/adamb314/ThreadHandler with no success. I had to make loops and this library didn't give me the period value I needed.

Finally I turned towards a search for a yield type operation like in Python: [AceRoutine](https://github.com/bxparks/AceRoutine)

## Nota Bene

- CoRoutines from AceRoutine are designed to be statically allocated as per the documentation. In order to trigger it, I used a private boolean flag and a call to COROUTINE_AWAIT
- A Coroutine is stackless and therefore cannot preserve local stack variables across multiple calls as per the documentation. So I used class variables as suggested (_iterations and _base_delay_micros)

## Bill of materials

An arduino. I'm using a nano
2 LEDs with their resistor

An IDE. I'm using vscode + platform.io.
See https://www.youtube.com/watch?v=PYSy_PLjytQ excellent guide to setup platform.io

AceRoutine excellent implementation of the ProtoThreads by Brian Park
https://github.com/bxparks/AceRoutine
Installation is done through platform.io library manager

# References

## Source code

https://github.com/HO44-PROJECT/coroutine_led_lamp.git

## Setup

Connect two LEDs using a resistor in series to two digital PINs. I use pin 4 and 5 in the demo.

Upload the sample code.

# Demo

TODO
