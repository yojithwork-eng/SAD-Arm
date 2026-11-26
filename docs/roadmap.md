# What's next

## One servo
- [x] Read FlySky CH1 on Arduino A0.
- [x] Move MG996R Servo 1 using D8 (about 60–120°).
- [x] Fix the missing buck OUT− → Arduino GND connection.
- [ ] Add the actual working sketch and video.
- [x] Incremental control passed four bench checks (reported Nov 25). Releasing the stick holds the servo angle.
- [ ] Save the exact sketch flashed during that test and measure the buck under load.

## Full arm
- [x] Servo 2 on D9 works alongside Servo 1 on D8 using FlySky PPM (signal D2).
- [ ] Solder wires onto LM2596 buck #3 and #4: IN+, IN−, OUT+, OUT−. Battery/USB unplugged while soldering.
- [ ] Inspect and insulate the joints, verify input polarity and set both outputs to around 5.0V with a meter **before attaching servos**.
- [ ] Hook up Servo 3 on D10 and Servo 4 on D11, each with its own buck supply and Arduino common ground. Test them one at a time.
- [ ] Check the buck output voltage while servos move; don't send servo power/return current through the breadboard.
- [ ] Measure buck output while the servos move.
- [ ] Work out the brackets, joint limits and whether the motors have enough torque.

## Treads
- [ ] Identify the yellow motors' rated voltage and stall current.
- [ ] Check L298N jumper setup and driver limits.
- [ ] Test both motors with the robot lifted off the ground.
- [ ] Add steering and smoother acceleration.

## Put it together
- [ ] Finish the fused, insulated battery wiring.
- [ ] Set up buck #5 for Arduino + receiver power without USB backfeeding.
- [ ] Decide whether to stick with PWM or switch to i-BUS.
- [ ] Add drive/arm mode switching and radio-loss handling.
- [ ] Add a low-battery cutoff/warning and a way to shut power off quickly.

## Demo
- [ ] Get the arm and treads working together.
- [ ] Record a real demo and write up what worked (and what didn't).
- [ ] Share the results after the team agrees.
