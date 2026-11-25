# How everything connects

This is the rough system layout, **not a final wiring diagram we can safely power up without checking**.

## Signals

```mermaid
flowchart LR
 TX[FlySky FS-i6X] -. radio .-> RX[FS-iA10B]
 RX -->|CH1 PWM to A0 works| UNO[Arduino Uno]
 RX -.->|i-BUS to D0/RX later| UNO
 UNO -->|D8–D11| ARM[4 MG996R servos]
 UNO -->|D2–D7| L[L298N]
 L --> LM[Left tread motor]
 L --> RM[Right tread motor]
```

## Power

```mermaid
flowchart TD
 BAT[7.4V 2S LiPo] --> F[Deans plug + correctly sized fuse]
 F --> P[Battery positive distribution]
 BAT --> N[Battery negative / common ground]
 P --> B1[Buck 1 / Servo 1]
 P --> B2[Buck 2 / Servo 2]
 P --> B3[Buck 3 / Servo 3]
 P --> B4[Buck 4 / Servo 4]
 P --> B5[Buck 5 / Uno + receiver]
 P --> L[L298N motor power]
 N --> B1 & B2 & B3 & B4 & B5 & L
 B1 --> S1[Servo 1]
 B2 --> S2[Servo 2]
 B3 --> S3[Servo 3]
 B4 --> S4[Servo 4]
 B5 --> U[Uno + receiver]
 L --> M[Two drive motors]
```

Each servo gets both + and − from **its own** buck, and the signal comes from the Uno. The Arduino needs a common ground with the bucks. Don't combine different bucks' positive outputs.

The plan is to have **drive mode** for the treads and **arm mode** for the four servos. In arm mode we want the joystick to move a joint and leave it where it is when released. That's still to be coded and tested. The finished code also needs to stop the drive motors if we lose radio contact.
