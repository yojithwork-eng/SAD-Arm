# What's next

## One servo
- [x] Read FlySky CH1 on Arduino A0.
- [x] Move MG996R Servo 1 using D8 (about 60–120°).
- [x] Fix the missing buck OUT− → Arduino GND connection.
- [ ] Add the actual working sketch and video.
- [x] Incremental control passed four bench checks (reported Nov 25). Releasing the stick holds the servo angle.
- [ ] Save the exact sketch flashed during that test and measure the buck under load.

## Full arm
- [ ] Connect Servo 2, 3 and 4 (D9, D10, D11), one at a time.
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
