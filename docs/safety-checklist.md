# Electrical, LiPo and mechanism safety checklist

**This is a pre-power checklist, not a declaration that the assembled robot is safe.**

- [ ] Disconnect LiPo before soldering, rearranging wiring or plugging connectors
- [ ] Use main LiPo discharge connector; never use the JST-XH balance lead for servo/drive current
- [ ] Install correctly sized inline fuse near battery positive terminal
- [ ] Check battery polarity, every regulator IN+/IN− and OUT+/OUT−
- [ ] Verify wire cross-section, connector ratings, insulation and strain relief for expected current
- [ ] Separate positive and negative branches; no exposed conductive ends or stray wire strands
- [ ] Set/measure servo buck outputs (initial 5.0V) **before connecting servos**
- [ ] Check output voltage during motion, not just unloaded
- [ ] Common grounds connected; do not join separate buck positive outputs
- [ ] No high-current wiring through solderless breadboard, Uno headers or signal ground jumpers
- [ ] Arduino external 5V cannot backfeed USB: arrange safe isolation
- [ ] Understand L298N regulator-enable and PWM enable jumpers
- [ ] Verify yellow motor voltage rating and stall current before direct LiPo feed
- [ ] Test servos without horns/linkages and motors with treads clear of surfaces initially
- [ ] Implement radio-loss stop and battery undervoltage plan before mobile operation
- [ ] Verify 2S-compatible balance charging; charge attended on suitable nonflammable surface

**Caution:** An LM2596 advertised 3A rating does not ensure 3A continuous in an assembled module. A 2S pack can sag below the regulator headroom required. Do not test by deliberately shorting the pack or stalling actuators.
