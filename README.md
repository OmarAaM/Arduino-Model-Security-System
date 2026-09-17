# Arduino-Model-Security-System
My first Arduino project that wasn't a build to learn how to use components or following a tutorial. This project uses an ultrasonic sensor to detect nearby objects and activates a DC motor once an object is detected to basically blow away that object. Along with this the object is mapped via a 8x8 LED matrix system. A video demo is available in the releases, and the code is in the main files, labeled as project1.ino.

# Hardware/ Material List
This project required an Arduino Nano, an HCSR04 Sensor, a DC motor with a fan attachment along with the L293D motor driver, 2 Hitec Servos, 8x8 LED matrix, LM2596 buck converter, 100 and 10 microfarad capacitors, and a battery pack. This was just the hardware, but for the power supply I was required to buy a soldering kit to attach the buck converter to the battery pack along with a multimeter to test the voltage. Some extra purchases made were a HCSR04 servo mounter and mounting tape, along with this bigger breadboard. 

## Known Issues

- **Reset on battery power:** when running on the battery pack alone (not USB), the Nano resets as soon as the sensor detects an object instead of activating the fan or staying in place. Suspect this is due to the motor pulling current somehow, maybe another electrical noise issue, but I am still debugging and testing while researching for a new project.

## Planned Improvements

- Replace the pill-bottle HC-SR04 mount with a 3D-printed 4-pillar stand that has room for the DC motor underneath (now that I have TAMU's 3D printers available)
- Better cable management. Move to smaller-gauge jumper wires to reduce the wire-looseness issue.
- Resolve the battery-power reset bug above maybe this is due to the power supply, so I'll need to find a way to test it, possibly just a simple code from the Arduino Uno which will use an analog read, to make sure the power supply does not randomly stop powering the components. 


## What I Learned

**Mobility & the Nano:** I chose the Arduino Nano specifically to make this project portable, which meant learning how to work with the Nano instead of the Uno I used before.

**Electrical noise:** Bad sensor readings turned out to be caused by electrical noise, which I had to learn about from scratch. The fix was two things, placing capacitors throughout the circuit to handle the noise directly, and taking a median of multiple HC-SR04 readings to throw out noisy readings that still were caused despite capacitors.

**Timing matters:** Early on, moving the servo too fast would ruin the sensor reading, since the servo moved before the ultrasonic pulse had time to bounce back. My first fix was just a flat `delay(300)` before every servo move. But taking 7 readings per measurement (at up to 60ms each) already adds up to nearly half a second, so any other careless delays elsewhere in the code made the whole project too slow. I ended up keeping all delays scoped inside the reading function itself, rather than scattered through the code.

**Power delivery:** This was the biggest lesson. I assumed the power supply from my Arduino kit could handle everything, but it maxes out at around 700mA, but the full project draws close to 1.5A. That meant learning what a buck converter actually does, buying a battery pack to feed it, and soldering the battery pack to the buck converter and the buck converter to the two wires.
