# Design decisions

| Decision | Rationale | Status |
|---|---|---|
| Four arm servos rather than five | Use existing five LM2596 converters: four arm supplies + one logic supply | Selected |
| Dedicated buck per MG996R | Avoid sending servo current through Uno/breadboard | Selected; load performance to verify |
| Fifth LM2596 supplies Uno + receiver | Separate logic supply | Planned; USB power isolation required |
| FlySky receiver CH1 PWM to Uno A0 | Simple test and serial debugging without D0/RX conflict | **Tested successfully** |
| Receiver i-BUS SERVO to Uno D0/RX | Fewer channel wires in final build | Planned, not tested |
| Servo signals D8, D9, D10, D11 | Dedicated outputs on Uno | D8 tested, rest planned |
| L298N control ENA D5, IN1 D2, IN2 D3, IN3 D4, IN4 D7, ENB D6 | Reserve PWM for speed | Planned, motors not validated |
| **Option B incremental control** | Release joystick → joint holds last commanded position | Chosen; code not yet physically verified |
| Lever connectors / insulated fused distribution | Avoid high-current breadboard supply | Bench parts seen; final protection unverified |
| Private GitHub development repository | Team review before public claims or sharing | Adopted |

Record changes, tests and reasons here; do not silently overwrite old design decisions.
