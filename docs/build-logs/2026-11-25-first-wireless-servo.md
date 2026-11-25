# Nov 25, 2026 — first servo working

Finally got an MG996R moving with the FlySky remote.

## Setup
- FS-i6X remote → FS-iA10B receiver, CH1 signal → Uno **A0**
- Uno **D8** → servo orange signal wire
- LM2596 **OUT+** → servo red; **OUT−** → servo brown/black
- LM2596 **OUT−** → Uno **GND** (the connection we originally missed)
- Uno powered by laptop USB, servo powered separately through the buck

## What happened
We could see the FlySky values changing (roughly 1000–2000 µs) and the Arduino was calculating angles around 60–120°, but the servo just sat there. We spent a while thinking the code was wrong.

Turns out the Arduino and buck converter didn't have a common ground. Added a wire from **buck OUT− to Arduino GND**, and the servo started following the stick.

Also hit upload errors when the FlySky i-BUS wire was on **D0/RX**. Unplugging that wire let us upload Blink and the test sketches again. For this working test we switched to the receiver's ordinary **CH1 PWM** signal on A0 instead of i-BUS.

Our first position-control sketch returned the servo near 90° when we let go of the stick. Later the same day, we tested incremental control (Option B) and reported that moving both ways, holding the angle at center, and smooth motion all worked. The exact code flashed for that test hasn't been saved here yet.

## Next time
- Save the *exact* working `.ino` (we haven't added it to GitHub yet).
- Record the voltage at the servo buck while it's moving, and save a demo video.
- Save the exact tested Option B sketch and record its travel limits/rate and radio-loss behavior.
- Check fuse, wiring insulation and buck heating before longer tests.
