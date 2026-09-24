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

One sentence. Not "can we build it" — the answer is yes and you learn nothing.
Something that could come out either way, so building it teaches you something.

We'll work on these together in class, so a rough one is fine here.

## What already exists

SenSynth: A mobile app that allows for synth control using the phone's accelerometer and gyroscope. Doesn't use ML for mapping, only one synth at a time.

What ours does differently: We will use ML to do our parameter mappings which opens up much more complex mapping abilities. Also, since AMY lets you run more than one synth at a time, we could map positions to synth parameters to allow for smooth transition between complex sounds, and map certain gestures to drum samples, FX, etc.

## How we'll build and test it

The stages you'll build in, and how you'll know each one worked. Who plays it
besides you, and what you'll watch for when they do.

## What we're starting from

ESP32-S3 from Espressif, AMY Synth library, provided Accelerometer and Gyroscope, ML resources

## Who's doing what

Connor: In the short term, exploring the AMY library, getting audio form AMY to output from the ESP32 to a computer. In the long term, goals could include; adding ML implementation to control synth parameters, helping with CAD work, helping design a GUI.

## What could sink this

Two or three honest risks — a part that might not arrive, something none of you
knows how to do yet. For each, what you'd do instead.
