# Test plan

Only physical evidence establishes pass/fail. Disconnect power before changing connections.

## Verified by team report (2026-11-25)
- [x] Blink uploaded to Uno after removing i-BUS data wire from D0/RX.
- [x] FlySky receiver CH1 PWM on A0 changes approximately 1000–2000 us with joystick.
- [x] MG996R Servo 1 physically moved on D8 across commanded ~60–120 degrees after connecting buck OUT-minus to Arduino GND.

## Not verified yet
- [ ] Save exact working Arduino IDE sketch and a short demonstration video.
- [ ] Record buck output voltage no-load and while servo moves; check buck and wires for heating.
- [ ] With horn removed, test incremental control: stick deflected moves servo, center holds position.
- [ ] Validate servo 2–4 individually, each separate buck and common ground.
- [ ] Verify yellow motor rated voltage, stall current and L298N regulator jumper.
- [ ] Test each tread lifted off ground.
- [ ] Validate fuse, power distribution, LiPo cutoff and USB/external 5V isolation.
- [ ] Test mode switching, loss-of-radio failsafe and full mechanical integration.

Log date, software commit, specific wiring, measured values, errors and evidence for each test.
