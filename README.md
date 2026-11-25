# SAD-Arm

We're building a small tracked robot with a 4-servo arm on top. The plan is to drive it around with a FlySky remote, move the arm, and eventually save a few automatic movements.

It's still early, but **two MG996R servos now work independently** from the FlySky remote using PPM and an Arduino Uno. The other two servos and tracks aren't hooked up yet.

## What we're using

Arduino Uno, FlySky FS-i6X + FS-iA10B, four MG996R servos, two DC gear motors, L298N motor driver, a 2S (7.4V) LiPo, and five LM2596 buck converters (four for servos, one planned for the Arduino and receiver).

## Trying the code

You'll need [Arduino IDE](https://www.arduino.cc/en/software/) and an Uno.

1. Plug in the Uno over USB and select **Arduino Uno** and its port.
2. For a **receiver-only** test, open [the CH1 reader](firmware/examples/pwm_channel_monitor/pwm_channel_monitor.ino). Connect FlySky receiver CH1 signal to **A0**, receiver 5V/GND to the USB-powered Uno. Leave the LiPo, servo and motor driver disconnected.
3. Upload it, open Serial Monitor at **115200**, and move the joystick. CH1 should change around 1000–2000 µs.

For the **servo test**, use the wiring in [wiring notes](docs/wiring-and-pinout.md): servo signal on **D8**, servo power from its own 5.0V buck, and **buck OUT− tied to Arduino GND**. The battery wiring has to be fused, insulated and checked with a meter first. Don't run servo power through the Uno or a breadboard.

We also got **incremental joystick control (Option B)** working on Servo 1: push the stick to move it, release to hold the angle. The [draft sketch](firmware/examples/incremental_servo1_draft/incremental_servo1_draft.ino) was our starting point, but we still need to save the exact `.ino` that was uploaded and tested.

## Where we're at

- [x] FlySky CH1 values show up on Arduino A0.
- [x] First servo moves about 60–120° from joystick input.
- [x] Found the problem when it wouldn't move: missing common ground.
- [ ] Save the exact working sketch and video.
- [x] Test incremental control: Servo 1 moves and holds when the stick is released (reported bench test).
- [x] Servo 2 on D9 works independently alongside Servo 1 with FlySky PPM on D2.
- [ ] Add and test Servo 3 on D10, then Servo 4 on D11.
- [ ] Get both treads working and put the whole robot together.

I've kept the [build log](docs/build-logs/2026-11-25-first-wireless-servo.md), [parts list](docs/hardware-inventory.md), [wiring notes](docs/wiring-and-pinout.md), and [to-do issues](../../issues) here so we can pick up where we left off.

This is a work in progress. Check the [power/safety notes](docs/safety-checklist.md) before connecting the LiPo.
