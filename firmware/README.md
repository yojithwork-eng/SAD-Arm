# Firmware status

The exact original tested Arduino IDE sketch for wireless servo position control has **not** been supplied as a source file. The team's test confirmed CH1 PWM receiver signal at A0 and servo signal on D8, but example files below are not substitutes for the original sketch.

- examples/pwm_channel_monitor: reconstructed diagnostic example, **not verified original**.
- examples/incremental_servo1_draft: proposed Option B hold-position controller, **not physically tested**.

Wire Servo 1 orange to D8; power red/brown from an independent buck set initially near 5V; **buck OUT-minus must connect to Uno GND**. Receiver CH1 S goes to Uno A0; for the bench test receiver is powered by the USB-powered Uno. All power wiring must be fused, inspected, and insulated. Do not connect servo power to Uno 5V.

Next: save exact verified code, pin mapping, output measurements and demo. Then test Option B unloaded.
