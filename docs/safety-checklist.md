# Before plugging in the battery

Keeping this checklist here because it's way too easy to miss one wire.

- [ ] Unplug the LiPo before soldering or moving connections.
- [ ] Use the main Deans battery leads, not the white balance plug, for powering the robot.
- [ ] Have a correctly sized fuse close to battery positive.
- [ ] Check + and − on the battery, each buck input and each buck output.
- [ ] No exposed copper, stray strands or loose wires. Secure the connectors.
- [ ] Wire gauge and connector current ratings actually match the load.
- [ ] Set the servo bucks to 5.0V initially and **measure them before plugging servos in**.
- [ ] Measure again while servos are moving, not just with nothing connected.
- [ ] Buck OUT− and Arduino GND connected. All grounds common.
- [ ] **Don't connect the positive outputs of different bucks together.**
- [ ] No servo or motor power through the breadboard or Arduino.
- [ ] Work out the Arduino external 5V/USB isolation before using buck #5.
- [ ] Check the L298N jumpers and the yellow motors' actual ratings.
- [ ] Test servos without arm links and treads with the robot off the ground.
- [ ] Have a plan for remote signal loss, low battery and emergency power-off.
- [ ] Verify the 2S balance charger. Charge attended on a suitable nonflammable surface.

The LM2596 boards saying “3A” doesn't mean they can supply 3A continuously in our setup. Also, they're step-down only, so the 6–5V output may not stay regulated as the 2S battery gets low. Never intentionally short the battery or stall a servo to test it.
