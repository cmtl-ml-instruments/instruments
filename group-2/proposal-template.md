# Project proposal

One per group, in your group's folder as `proposal.md`. A page is plenty.

This is what the rest of the semester answers to. When you're stuck on what to
build next, come back here.

---

## What we're building

We are building a handheld instrument that the user can move around in space to control synth parameters or pitch.

The device will track its position using an accelerometer and a gyroscope. Specific positions from those sensors will be mapped to synth parameters. The mappings will be defined using an ML algorithm so that the user can smoothly transition from one position to another, and the synth parameters will gradually change with its position.

All of the synthesis will happen within the device. We will use the AMY library for our synthesis.
We want to give the option to connect to a MIDI keyboard so that you can play notes on the synth with one hand while controlling its parameters on the other.
The audio would output from a USB cable into a computer as an input, if we add a MIDI keyboard, it would ideally connect
wirelessly.

## Our research question

What assignment of movements (rotationals and linear) to sound parameters like pitch, volume and octave create the most user friendly experience for handheld instruments.
## What already exists

SenSynth: A mobile app that allows for synth control using the phone's accelerometer and gyroscope. Doesn't use ML for mapping, only one synth at a time.

IMPSY: An ML framework to map inputs to synth or audio controls. Not a standalone instrument, just a tool that one can use to design or "upgrade" existing instruments.

What ours does differently: We will use ML to do our parameter mappings which opens up much more complex mapping abilities. Also, since AMY lets you run more than one synth at a time, we could map positions to synth parameters to allow for smooth transition between complex sounds, and map certain gestures to drum samples, FX, etc.

## How we'll build and test it
Rough outline:
Get AMY outputting clean audio to computer
- We know it works if we hear audio output

Stream accelerometer and gyroscope data to the ESP32
- We know it works if can read the input on the screen using a simple graphic interface

Connect accelerometer and gyroscope to ML model, along with AMY synth parameters
- We know it works if we have the ability to design very simple models that demonstrate that the technology works reliably before we start making more complex models

Build an interface so that the user can save models
- We know it works if we can successfully save and load models on the ESP

Allow the user to be able to train models that work across multiple synths
- Again, we will test very basic models to see if our implementation works before testing complex models

Allow the ability to take in a bluetooth MIDI keyboard input
- We know it works if we can play MIDI notes on the internal AMY synth

Design a case for the ESP
- Will do whenever we get to a stopping point this semester

## What we're starting from

ESP32-S3 from Espressif, AMY Synth library, provided Accelerometer and Gyroscope, ML resources

## Who's doing what

Connor: In the short term, exploring the AMY library, getting audio form AMY to output from the ESP32 to a computer. In the long term, goals could include; adding ML implementation to control synth parameters, helping with CAD work, helping design a GUI.

Aidan: In the short term, researching gyroscopes and accelerometers to find what is compatable with our boards. In the long term, I plan to map the data outputted by the ML model onto the UI. I also would like to lead the CAD design to create an ergonomic structure that protects the electronics.

Mohan: In the short term, developing the embedded hardware proof-of-concept by interfacing the accelerometer and gyroscope with the ESP32 and writing the C firmware to visualize real-time sensor data on the display. In the long term, leading the integration of the machine learning to classify gestural movements and bridging that inference data to the AMY audio engine.

## What could sink this

I am most worried about the compatability of the sensors with the ML models we pull from online. We need to pay careful attention to the format in which we will receieve data from the gyroscope and accelerometer before we buy them so that it is possible to map them to the ML model.

Additionally, hardware and library driver incompatibilities could bottleneck development. We need to allocate extra time for writing custom hardware definitions or adapting official manufacturer libraries to ensure the display, ML inference, and audio synthesis can all run simultaneously without crashing the microcontroller.
