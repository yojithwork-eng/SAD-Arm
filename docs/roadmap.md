# SAD engineering roadmap

## Milestone 1 — One wireless servo
- [x] FlySky PWM receiver tested and Arduino receives CH1 on A0
- [x] MG996R Servo 1 follows stick using D8, approximately 60–120°
- [x] Resolve missing common ground between buck OUT− and Uno GND
- [ ] Preserve exact working firmware, voltage readings and demo video
- [ ] Test **Option B incremental hold-position control** on unloaded servo

## Milestone 2 — Four-servo arm
- [ ] Test servos 2–4 individually (signals D9, D10, D11)
- [ ] Measure buck regulation during realistic motion/current
- [ ] Validate bracket fits, mechanical range and joint torque

## Milestone 3 — Two-tread drive
- [ ] Identify motor rated voltages, no-load and stall currents
- [ ] Verify L298N current and logic jumper configuration
- [ ] Drive each motor with treads safely lifted
- [ ] Program throttle, steering, acceleration limiting

## Milestone 4 — Integrated operation
- [ ] Complete fused battery distribution, wiring and mechanical mounting
- [ ] Verify fifth buck/Uno/receiver power and USB isolation
- [ ] Select safe receiver connection scheme (PWM vs i-BUS)
- [ ] Implement drive/arm switching and failure handling
- [ ] Implement LiPo protection, radio-loss failsafe and emergency power-off

## Milestone 5 — Demonstration
- [ ] Capture physical arm and drive test footage
- [ ] Document performance, remaining risks and team contributions
- [ ] Approve external publication and publish project progress
