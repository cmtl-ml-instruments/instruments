# Instrument worksheet

**Minimum Viable Prototype deadline: Friday 13 November.**  
[Decision Points](#8-decision-points)  
[The Timeline](#9-the-timeline)  
[Who Does What](#10-who-does-what)  

---

## 1. The name

One name. Not a project title — a name, the way a cello is called a cello.

## 2. What it is

One sentence. All three of your names underneath it.

We want to create an interactive flexible rope instrument paired with control gloves for both continuous and discrete input, respectively.

## 3. Picking it up

**Someone who has never seen it walks in. What happens in the first ten seconds,
before anyone explains anything?**

*Worth thinking about: what they notice before they touch anything · what its shape
tells them to do, and whether that's what you want them to do · the first thing
they touch, press, tilt or move · what tells them they caused the sound and not the
machine.*

- The device has a handle, incentivizing them to pick it up
- The instrument has many joints that it can rotate on, and it immediately begins to rotate upon being picked up (possibly it makes sound)
- The gloves and device can be color coded to imply togetherness. A shared case can be used for this too.

## 4. The first ten minutes with the instrument

**Once they've worked out the first thing, what keeps them there?**

*Worth thinking about: what they try second, now that the first thing taught them
something · the one thing you'd have to say out loud for them to get it, and
whether you could design that away instead · what makes them keep going instead of
handing it back to you.*

- The second thing they might try is swinging the rope around to play with it, and that should immediately connect to music.
- The thing that might not be immediately apparent is how to use the gloves with the rope instrument. We have in mind that the gloves can trigger notes on commands or else the performer might need to stop spinning the instrument to create silence, which is less fun.
- The instrument is easy to start, but hard to master, which keeps the user going.

## 5. The setting

**Where is this instrument played, and who else is there?**

*Worth thinking about: stage, club, dive bar, gallery, bedroom, bike path,
classroom · who else is in the room, and how far away · whether the player stands,
sits, walks, dances.*
The player should have plenty of space to swing the instrument around them.
- On-Stage
  - Needs to be capable of producing loud enough sound
- Outside
  - Needs to be

For the prototype, connecting to a computer over wifi for external processing will be easiest.

## 6. What it does that another instrument can't

- How many other instruments use rotation to create music? If the air channnel through spinning is used as a resonator, it would create novel acoustic effects. The instrument is like a string instrument, but in an unconventional way.
- Attaching a speaker to the spinning part of the instrument would create a novel acoustic phenomenon that might be worth exploring. However, an external speaker would be easier to implement.

**Which existing instrument is yours beating, and what can yours do that it can't?**

*Name a specific one — a keyboard, a phone, a guitar pedal, a MIDI controller, a
knob, SenSynth, anything.*

- The Lethelium was a bike-wheel themed instrument at the last Guthman competition. We are beating it in the aspect of rotating the instrument changes the sound.
- The Air Guitar is a gestural instrument that mimics the basic motions of playing a guitar. Our instrument would be more original, both in the interface, and its sound.
  - If we use the unique mechanics of the instrument as synthesis parameters, it would theoretically be a uniquely identifiable sound.

> Ours can ________________, and that one can't.

## 7. Where iris fits

**Which part of your instrument is too complicated to write down as a rule?**

*Try it: pick one place where the player's movement changes the sound, and write
that rule in plain numbers — "tilt it 30 degrees, the pitch goes up one note." If
you can, write it by hand. If you can't, that's where iris goes: instead of the
rule you write down two examples — hold it one way and what it should sound like,
hold it another way and what that should sound like.*

- An instrument that can rotate on myriad joints behaves like a multipendulum, the mechanics of which are extremely non-linear. This makes ML ideal for the parameter mapping.
  -   Fill in the details here of some parameter mappings.
  -   Speed of Rotation - accelerometer and gyroscope at different points in instrument
  -   Types of rotational gestures
  -   Physical Position of Instrument relative to gloves
  -   Hand gestures. - gestures on different gloves.

- We could use the gloves for note onsets, or for the notes themselves, or for synthesis tied to individual parts of the instrument.

  -   
- We can also use ML to allow the performer to switch hands in performance (control hand and spinner hand). We want to unify interesting spinning gestures with interesting music.

---

## 8. Decision Points
- Denote the 6 degrees of freedom accelerometer/gyroscopes as _6dofs_
**Physical Design**
- length of the chain: 30 inches based on a good holding height. Not super long.
- Joints: Building a true multipendulum might be out of scope given the 360 degree rotating joints. We will go forward with the chain link design and see if it is flexible enough.
- Sensors
  - right now we have 2-3 6dofs.
  - we're gonna start with 2-3 spaced 10 inches apart. The multiplexer has to be used after 2.
  - Prep the ml for a short radius, middle radius, and long radius.  

**Sound**  
- Sparkly, String Bending
can use speed of rotation to control granular density.
an electric guitar type
or moving a lot through the air - wood winds.
I could use the frequency spectrum of it as a start
or we could use physical modelling


**Parameter Mapping**  
Grain Cloud Parameters (controlled by instrument)
- Grain Duration (seconds\grain): Time that each grain plays for
- Grain Density (grains/second): Number of grains generated per second
- Bandwidth (Hz): Pitches are randomly chosen in an interval of this width
  - Not sure whether to quantize this process yet. 
- Pitch (Hz):  Center frequency of the band

How Grain Duration, Density, and Bandwidth, Affect the Sound
|Duration|Density|Bandwidth|Sound|
|--------|--------|--------|----|
|  long  |  high  |  broad | wall of sound |
|  long  |  high  | narrow | sustained formant[^1] |
|  long  |  low   |  broad | chords/sustained melody |
|  long  |  low   | narrow | simple sustained note |
|  short |  high  |  broad | staccato noise |
|  short |  high  | narrow | sparse formant |
|  short |  low   |  broad | staccato melody |
|  short |  low   | narrow | simple staccato note |

[^1]: A formant is a clear pitch with nice spectra. 

- How each gestural motion should affect the sound (Tentative)
  - Map _angular_ acceleration to the bandwidth. That makes stable rotation pitched and erratic rotation noisy
    - TODO: calculate this from gyroscope measurements
  - Map angular velocity to either pitch or grain density.
    - Spinning faster either makes the texture denser or makes the pitch higher
  - Map position of the handle relative to some calibration to pitch.
    - TODO: Buy absolute orientation compass and put it near the handle, (or inside)
  - Map _linear_ velocity or acceleration of the handle to grain duration. That hopefully makes whip motions produce sharper sounds
  - Map position of the handle relative to the glove to spatial effects like reverb.
  - Note these motions are coupled. The gloves let you uncouple them.
  
- Role of the gloves: 5 buttons
  - 1: Control Note/on
  - 2-5: Hold Duration, Density, Pitch, and Bandwidth, respectively[^2] (button order undecided)
    - When you press them, the value would remain fixed regardless of the motion. When you let go, the value would ramp to its current value 

[^2]: Credit to Hayden Sebastian for this idea

- Physical modelling synthesis parameters may become relevant later too.
- The randomness of the other per-grain parameters is not fully decided.

## 9. The timeline

Work backwards from the 13th.
- 1 goal and stretch goal per 4 weeks leading up to prototype. Figure this out by monday.

| Date | What exists by the end of that week | A test of it that could fail |
|---|---|---|
| Oct 9 (today) | Determine/Finalize what direction we are taking the project in. | We don't come to a consensus on what we're building |
| Oct 16 | We compile all of the needed resources: gyroscopes, accelerometers, and magnetic sensors. Everyone starts learning in their role. Finish CAD Design V1 | Something posted to the instrument folder |
| Oct 23 | Finish CAD design V2 and begin attaching hardware devices to the physical product. Have an ML patch that runs without bugs. Have a starter synthesis patch | ML runs without bugs. Functioning with sole gyroscopes or V1 prototype. |
| Oct 30 | We have something physical to work with and test. Update the synthesis patch. |Get sound |
| Nov 6 | (tentative) We wire the instrument. Starting the IRIS patch | Get numbers from accel/gyro produced by instrument. |
| Nov 13 | **Minimum viable prototype.** The physical instrument successfully connects to the ML and synthesis mapping | Triggering notes on command. Tests of other parameters |
|**Nov 20**|**a stranger can pick it up and play it** Extra: case, color coding |Test: Doesn't work |

## 10. Who does what

Every person, every week, something specific — code, soldering, CAD, enclosure,
sound design, testing, writing.

| Person | Credit hours | What they own | This week | Next week |
|---|---|---|---|---|
| Caleb | 1 | Hardware and Physical Design | Update CAD Design to V2 and account for sensor location (every 10/15 inches) and length of design (30 inches) Print something | Have design printed out and attach sensors to determined locations |
| Sam | 2 |Sound synthesis-ML connection. | Then modify my existing granular synthesis patch from sampling synthesis to something more intrinsic (physical modelling). Adjustments for Grain Duration, Density, Bandwidth, and macro pitch. The cloud generator should be primed to connect to the ML. | Go in depth with IRIS and connect the ML patch to the granular.|
| Talal | 2 | ML and Programming | Work with a glove prototype (mechanical keys) and simple example chain prototype as inputs for the model. Solder stemma connections for accelerometer/gyroscope. | Interface with IRIS, getting a proper connection and data flow from sensors, getting a proper connection for the glove keys. Further understand IRIS's part within the workflow. |


