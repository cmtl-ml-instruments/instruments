# Project proposal

This is what the rest of the semester answers to. (Also the instrument worksheet)

---

## What we're building

We want to create an interactive flexible rope instrument paired with control gloves for both continuous and discrete input, respectively.


We want to build a networked instrument with 2+ controllers connected in a mesh network fashion, and utilize Machine Learning algorithms to discern actions taken between the devices in relation to each other. Simply, we want microcontrollers connecting to each other, and utilizing gestural actions (or other actions) to be inputs to a Machine Learning algorithm that would convert those inputs into sound. For example, taking the movements of two boxers boxing with each other via various sensor data and translating that into sound. 

We would like to take full advantage of the ML by mapping complex interactions of the microcontrollers to many synthesis parameters. Simultaneously, there still needs to be sound-action coupling with the synthesis, meaning each player can perceive the effect of their actions on the overall sound.


## Our research question

One sentence. Not "can we build it" — the answer is yes and you learn nothing.
Something that could come out either way, so building it teaches you something.

We'll work on these together in class, so a rough one is fine here.

1) What are the unique advantages of Machine Learning in terms of mapping physical movements to sound output.
2) How can the unique advantages of Maching Learning better map variable user expressions to produce distinct sounds when compared against movement based microcontroller systems that don't use machine learning to function.

## What already exists

Two or three things from your mood board. For each: what it does, and what
yours does differently.

Air Guitar: Uses TinyML to identify gestures, in this case guitar playing gestures, and produces guitar sounds based off of the users "strumming" movements and finger position.

What ours does differently: Ours will not use pre-existing sounds and will instead produce our own synthesized sounds. It won't be in the image of a guitar but instead free movemments.

## How we'll build and test it

Refer to the instrument worksheet for timeline

## What we're starting from

Board, sensors, sketches from the class repo, libraries — anything you're not
writing yourself. Then what you are writing yourselves.
ESP32-S3, ML resources,

## Who's doing what

Each person, what they own, and their credit hours. This can change later.

Caleb (1-Credit): Primary Focus on understanding the esp32 board and how to properly wire the systems that we'll need to use. Understanding what devices need to be used in order to track user movement and produce sound and how those will connect and work with the esp32. Hardware focused goals.

Sam (2-Credit, MT): Primary focus is creating the ML mapping and connecting it to the sound synthesis.

Talal (1-Credit, CS): Primary focus is ML. Interested in the music and circuitry as well.


## What could sink this

- Running out of time. - primary risk factor.
- ML Mapping could get tough
