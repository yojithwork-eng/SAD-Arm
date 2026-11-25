# Tests

Don't mark a test done just because the Serial Monitor prints something. We want to see the part actually work.

## Done (Nov 25, 2026)
- [x] Blink uploaded on Uno. Had to disconnect FlySky i-BUS from D0/RX to fix the upload errors.
- [x] FlySky CH1 on Uno A0 reads about 1000–2000 µs as the joystick moves.
- [x] MG996R on D8 moves when controlled by the joystick, around the commanded 60–120° range.
- [x] Fixed it by connecting buck OUT− to Uno GND.

## Still to test
- [ ] Save the exact `.ino` from Arduino IDE and a clip of the working servo.
- [ ] Measure 5V buck output at rest and while moving. Check heat.
- [ ] Try Option B with the horn off: hold the stick to move, center it to stay put.
- [ ] Test the other three servos with their own buck converters.
- [ ] Find the yellow motors' ratings and check the L298N jumper setup.
- [ ] Test both treads lifted off the floor.
- [ ] Verify fuse, battery connections, low-voltage protection and Uno power isolation.
- [ ] Test radio loss, drive/arm switching and the assembled robot.

When something fails, write down the exact wiring, voltage readings, code version and what happened.
