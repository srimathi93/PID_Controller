# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

##Summary
This project deals with the implementation of a PID controller to control the steering angle of the car as oit loops around the track. The goal of the project is to ensure that the PID is implemented and tuned such that the car never leaves the track.

## Code Overview
The PID is implemented in the pid.cpp file. PID::Init initializes the Kp, Ki, Kd values and the p,i and d errors. The PID::UpdateError method calculates the error seperately from the cte provided in the main.cpp file from the simulator. The PID::TotalError calculates the total error using the gains and the errors. This is the steer value which is needed because ideally if the vehicle is at the center of the lane, the error will tend to 0.

## PID Coefficients Impact and Tuning

### P Coefficient: 
The proportional part of a PID tries to get the value close to 0 as quickly as possible. So in this scenario, the proportional part of the algorithm tries to steer the vehicle to the center of the lane as quickly as possible. Since it gets the value so quickly to the center, the steering overshoots and then the proportional portion tries to steer it back to the center and overshoots again. Because of this, the vehicle keeps oscillating around the center of the lane.

### I Coefficient: 
The integral part works on any possible bias in the system that can offset the error or cause the error to have a consistent offset from 0. In this scenario, since the vehicle is simulated, there exists no bias in the system. So this value is set to 0.

### D Coefficient: 
The diffrential part of the PID analyzes how quickly cte approaches 0 value  and slows down as it approaches 0. Hence it counteracts the proportional part as that overshoots the 0 value. 

I increased the proportional parts with small increments until after a point, the car kept osciallating around the center line. It eventually made the car leave the track as the oscillation kept increasing. To counteract this, I had to increase diffrention coefficient so that the oscillations reduce overtime and the drive is smooth. I did try to add the integral coefficients just to ensure that my hypothesis is accurate. Adding a non zero Ki value made the car very unstable and drive outside the lane. A couple more iterations helped made the drive smooth. I finally normalized the steering value between [-1,1] just to prevent any quick jerks.

I did try to implement twiddle as a seperate script but I had issues compiling it. I have downloaded the repo to work on it at a later time.

Here is the final video of the drive.

[./Mov1.mov](./Mov1.mov)





