# Why we're doing it this way

Just keeping track so we don't forget why the wiring changed.

- **4 servos, 5 buck converters:** one converter per MG996R, plus a fifth planned for the Arduino and receiver. We have one spare servo.
- **Servo power stays separate:** don't run MG996R current through the Arduino or breadboard. We still need to check whether each LM2596 can handle the real load.
- **FlySky CH1 → A0 for now:** this works. We tried i-BUS on D0/RX but it got in the way of USB uploads; we haven't decoded i-BUS successfully yet.
- **Servo signal pins:** D8, D9, D10, D11. Only D8 has been tested.
- **L298N pins:** ENA D5, IN1 D2, IN2 D3, IN3 D4, IN4 D7, ENB D6. Still need to test both tread motors and check motor ratings.
- **Option B for the arm:** push the joystick to rotate a joint, let go to keep the angle. Chosen, **not tested yet**.
- **Battery wiring:** fused/insulated 7.4V distribution to five bucks + L298N. We have lever connectors, but haven't verified the finished harness or fuse size.
- **Arduino power:** fifth buck would supply 5V logic. Need to sort out USB backfeeding first.

For the first servo test we powered the Uno and receiver by USB and the servo from a separate LM2596. Buck **OUT− must connect to Uno GND** or the signal won't have a common reference.
