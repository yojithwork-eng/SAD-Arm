# System architecture

## Control path
```mermaid
flowchart LR
 TX[FlySky FS-i6X] -. radio .-> RX[FS-iA10B]
 RX -->|CH1 PWM to Uno A0 verified| UNO[Arduino Uno]
 RX -.->|i-BUS SERVO to Uno D0/RX planned| UNO
 UNO -->|D8–D11| ARM[4 MG996R servos]
 UNO -->|D2–D7| L[L298N]
 L --> LM[Left tread motor]
 L --> RM[Right tread motor]
```

## Power path
```mermaid
flowchart TD
 BAT[7.4V nominal 2S LiPo] --> F[Deans adapter + correctly sized fuse]
 F --> P[Positive power distribution]
 BAT --> N[Negative power distribution]
 P --> B1[Buck 1 servo 1]
 P --> B2[Buck 2 servo 2]
 P --> B3[Buck 3 servo 3]
 P --> B4[Buck 4 servo 4]
 P --> B5[Buck 5 Uno and receiver]
 P --> L[L298N motor supply]
 N --> B1 & B2 & B3 & B4 & B5 & L
 B1 --> S1[Servo 1]
 B2 --> S2[Servo 2]
 B3 --> S3[Servo 3]
 B4 --> S4[Servo 4]
 B5 --> U[Arduino + FlySky]
 L --> M[Two tread motors]
```

**Architecture illustration only**, not verified connection-by-connection. Each servo receives both OUT+ and OUT− from its respective buck and a separate signal from Uno. All signal grounds share the battery-negative reference. Regulated positive outputs are not paralleled.

## Operating modes (future)
- **Drive:** differential motion of two treads, arm maintains its commanded positions.
- **Arm:** motors disabled, joystick deflection commands incremental joint motion; centered stick holds last position.
- **Safety:** radio-signal-loss motor stop, motor disable when switching modes, travel limits, LiPo undervoltage protection.
