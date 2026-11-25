# First LinkedIn update (draft, not posted)

We've started working on Smol Arm Dynamics (SAD), a little tracked robot with a four-servo arm on top.

This week we got the first MG996R servo moving from a FlySky controller through an Arduino Uno.

It took us longer than expected because the Arduino was reading the joystick and printing the right angles, but the servo wouldn't move at all. We eventually found the issue: we hadn't connected the buck converter's ground to the Arduino ground.

One wire later, it worked.

Next we're trying to make the servo stay at its last position when we release the joystick, then we'll work on the other joints and the treads.

We'll post the progress here as we go.

#Robotics #Arduino #Mechatronics

Before posting: add a real video and check with the team.
