# Arduino code

We're using an Uno, FlySky receiver and MG996R servos.

- [CH1 receiver test](examples/pwm_channel_monitor/pwm_channel_monitor.ino): reads FlySky CH1 on **A0**, prints values to Serial Monitor at **115200**. This is a recreated example, not the exact file we used on the bench.
- [Incremental servo draft](examples/incremental_servo1_draft/incremental_servo1_draft.ino): a one-servo Option B test.
- [Two-servo PPM sketch](examples/ppm_two_servos_draft/ppm_two_servos_draft.ino): CH1/CH2 over **one PPM signal wire on D2**, Servo 1 on D8 and Servo 2 on D9. Both servos worked on the bench, but the *exact final sketch and faster interval values* still need saving.

For the receiver-only test, power the receiver from the USB-powered Uno's 5V/GND, with CH1 signal on A0. Leave motor and servo power disconnected.

For a servo test, the servo gets its power from its own regulated buck (initially 5.0V), not the Arduino. **Buck OUT− must also go to Arduino GND** or the servo signal won't work. Make sure the LiPo wiring is fused and safe before powering anything.

We still need to save the *actual* working joystick-to-servo code from Arduino IDE here.
