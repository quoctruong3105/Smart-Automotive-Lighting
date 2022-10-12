# Smart-Automotive-Lighting
+ This is a self-study project to improve C programming skills and AVR microcontroller knowledge.
+ Tools: Proteus, Codevision
+ Tasks: Simulate circuit diagram on Proteus, build code in Codevision and load hex file to AVR microcontroller, test system and debug,...
+ Knowledge used in this project:
  - Microcontroller: Timer0(fastPWM), ADC, registers declare. 
  - C language: loop, if-else structure.
+ Working principle:
  - Controlling the rotation of the lights according to the steering angle: The system uses the motor to control the rotation of the headlights depending on the steering angle.
  - Automatic high beam control: each side of the light will be divided into 5 light clusters, when there is light on any light cluster (recognized by the photoresistor), it means that there is a vehicle on the opposite side and is under impact. By that light cluster, the system will turn the light cluster from high beam to low beam to avoid blinding the driver in the opposite direction.
Description video: https://www.youtube.com/watch?v=0qViXObqLnw
