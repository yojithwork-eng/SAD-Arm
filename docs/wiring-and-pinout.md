# Wiring and pin assignments

**Scope:** Current bench-test wiring is verified by team report. Final integrated wiring remains a plan and is **not** a validated complete circuit schematic.

## Verified: FlySky CH1 to first servo
| Connection | Endpoint |
|---|---|
| FS-iA10B CH1 PWM S | Arduino A0 |
| FS-iA10B power, test only | USB-powered Uno 5V and GND |
| Arduino D8 | MG996R Servo 1 orange/yellow signal |
| LM2596 #1 OUT+ | MG996R Servo 1 red |
| LM2596 #1 OUT− | MG996R Servo 1 brown/black |
| **LM2596 #1 OUT−** | **Arduino GND (critical common reference)** |

Uno was powered from laptop USB for this bench test; servo was separately powered by its buck. No servo current should pass through Uno/breadboard.

## Planned final Uno pin map
| Pin | Function |
|---|---|
| D0/RX | FS-iA10B i-BUS SERVO data — **untested**; conflicts with USB serial during uploads |
| D2 | L298N IN1 |
| D3 | L298N IN2 |
| D4 | L298N IN3 |
| D5 | L298N ENA (PWM; remove ENA jumper) |
| D6 | L298N ENB (PWM; remove ENB jumper) |
| D7 | L298N IN4 |
| D8 | MG996R Servo 1 |
| D9 | MG996R Servo 2 |
| D10 | MG996R Servo 3 |
| D11 | MG996R Servo 4 |

FlySky's working **PWM CH1 via A0** and planned **i-BUS via D0** are different interfaces: do not describe i-BUS as already validated.

## Power branches — planned
- 7.4V nominal 2S LiPo main discharge leads → properly sized inline fuse → insulated distribution harness.
- LiPo battery inputs supply LM2596 #1–#4 independently (one per servo; initial **5.0V** output each), LM2596 #5 (**5.0V** for Uno and receiver), plus the L298N motor supply (subject to motor rating verification).
- **All grounds common**; never tie separate bucks' positive outputs together.
- LM2596 #5 feeding Uno 5V needs a safe USB power-isolation strategy before use.
- L298N onboard 5V regulator-enable jumper and motor rated voltage/current still need verification.
- LiPo voltage decreases during discharge; buck-only LM2596 modules may lose regulation headroom. Do not assume 3A continuous output.
