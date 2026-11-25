# Wiring notes

The one-servo setup below **worked**. The full robot pinout is what we're planning, not something we've tested end to end.

## Working one-servo test

| Wire | Goes to |
|---|---|
| FlySky receiver CH1 signal | Arduino A0 |
| Receiver power (test setup) | USB-powered Arduino 5V + GND |
| Servo 1 orange signal | Arduino D8 |
| Servo red | Buck #1 OUT+ |
| Servo brown/black | Buck #1 OUT− |
| **Buck #1 OUT−** | **Arduino GND** |

That last ground connection was what we missed at first. Arduino was calculating angles but the servo didn't move until we added it. The Uno was on USB and the MG996R used its own buck.

## Pins planned for the whole robot

| Arduino pin | Part |
|---|---|
| D0/RX | FlySky i-BUS signal (not tested, clashes with USB uploads) |
| D2 | L298N IN1 |
| D3 | L298N IN2 |
| D4 | L298N IN3 |
| D5 | L298N ENA, motor PWM |
| D6 | L298N ENB, motor PWM |
| D7 | L298N IN4 |
| D8 | Servo 1 |
| D9 | Servo 2 |
| D10 | Servo 3 |
| D11 | Servo 4 |

The receiver PWM wire on A0 is what actually works right now. That's different from the final i-BUS idea.

## Battery power plan

The 7.4V LiPo feeds an appropriately fused positive/negative distribution harness. Four separate LM2596 bucks feed four servos, initially set to 5.0V. Buck #5 is meant to feed 5.0V to the Uno and receiver. The L298N gets battery power separately once the motor ratings have been checked.

All grounds need to be common, but **don't tie the bucks' positive outputs together**. Buck #5 also needs safe USB power isolation before we connect it to the Uno. We still need to verify motor ratings, L298N jumper setup and buck behavior under load.
