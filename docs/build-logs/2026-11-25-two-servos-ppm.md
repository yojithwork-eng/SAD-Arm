# Nov 25, 2026 — two servos with FlySky PPM

Got Servo 1 and Servo 2 responding independently from the FlySky remote.

## Setup
- FS-i6X and FS-iA10B receiver switched to **PPM output**.
- Only three receiver wires: PPM/CH1 signal to Uno **D2**, receiver + to USB-powered Uno **5V**, receiver − to Uno **GND**.
- Servo signals: **D8** (Servo 1), **D9** (Servo 2).
- Each MG996R gets power from its own LM2596 buck, with each buck's OUT− connected to Arduino GND.
- Arduino on USB for this bench test, servos on separate external supplies.

## What happened
At first the PPMReader sketch only printed 1500 values. We eventually fixed the receiver's output setting, and CH1/CH2 started updating as the joystick moved. CH3 stayed near center because it wasn't being moved.

We then ran a two-servo incremental-control sketch. Both servos now work as expected, and we sped up the motion by shortening the step interval. The user confirmed both servos are working properly.

## Still to check
- Save the **exact** final code and speed settings uploaded to the Uno (the GitHub PPM sketch is still a draft).
- Measure both buck outputs while the servos are moving, check heating, and confirm battery fuse/insulation.
- Check what happens when the transmitter disconnects. The current library may return stale channel values, which isn't a proper failsafe.
- PPM is using **D2**, but D2 was originally reserved for L298N IN1. We'll remap that when the drive motors are added.

## Next
Servo 3 signal to D10, its own buck (initially 5.0V, checked before servo connection), and a careful unloaded test. Keep the two working servo circuits untouched.
