# Build log — November 25, 2026 — First wireless MG996R

**Result:** Successful physical movement confirmed by team report.

## Objective
Use FlySky FS-i6X controls, FS-iA10B receiver, Arduino Uno and external servo power to command MG996R Servo 1.

## Wiring
- Receiver CH1 PWM S → Arduino A0; receiver powered from USB-powered Uno for bench test.
- Uno D8 → servo orange signal.
- LM2596 OUT+ → servo red; OUT− → servo brown/black.
- LM2596 OUT− → Arduino GND (missing initially).

## Procedure and findings
1. Paired FlySky transmitter/receiver. Earlier tested CH1–CH6 PWM output with small servo.
2. Uploaded Blink and servo sketches to Uno. Uploads initially failed when i-BUS signal was attached to D0/RX; disconnecting D0 fixed USB upload conflict.
3. Used receiver CH1 PWM on A0 and displayed input pulse lengths ~1000–2000 µs and corresponding target angles ~60–120°.
4. Servo initially **did not physically move**, even though Arduino calculations responded to joystick.
5. Diagnosed missing **common ground** between external buck and Uno. Connecting converter OUT− to Uno GND made servo respond normally.
6. In current position-based control, returning joystick to center returns servo toward ~90°.

## Engineering lesson
Signal values alone do not prove the actuator is receiving a valid reference or adequate power. Independent motor/servo supply negatives must share a signal reference with the controller. The high-current return stays on the servo's supply wiring rather than through the Arduino.

## What is NOT yet verified
- Exact test sketch committed as the original tested artifact.
- Output voltage measured while servo loaded; thermal and stall-current margin.
- Battery fuse and cutoff installation.
- Incremental control (Option B) operation.

## Next
Save the actual tested Arduino sketch, voltage readings and demo video. Then test incremental hold-position firmware with the horn/linkage removed.
