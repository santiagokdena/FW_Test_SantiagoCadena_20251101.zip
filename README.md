# FW_Test_SantiagoCadena_20251101.zip
## Firmware Test - Powerhouse 

The firmware, written in C++, models an environmental control system for a plant, designed to maintain a specific reference temperature and brightness. It utilizes a DHT11 sensor for humidity and temperature readings and a photoresistor for measuring ambient light. These sensors provide real-time feedback to the system's actuators—a transistor-powered fan for cooling and a white LED for illumination. The core idea driving the code is the implementation of a Proportional-Integral (PI) control loop for both variables. This feedback mechanism continuously calculates the error, which is the difference between the measured value and the desired setpoint. The proportional term provides an immediate, corrective response proportional to the current error, while the integral term accounts for the accumulation of past errors, systematically eliminating any persistent offset. Through iterative calculations over time, this combined action drives the total error toward zero, forcing the plant's environment to converge on and maintain the desired heat and brightness levels, regardless of external conditions.

To ensure robustness, the plant is modeled as a linear system with intentional distortion, introducing simulated noise and a constant signal gain or offset. This approach mirrors real-world imperfections, ensuring the control algorithm remains effective even when the system is perturbed or operates in an open-loop configuration. By incorporating these constants into the equations for the controlled variables, the PI controller dynamically compensates for these modeled inaccuracies. The final result is a stable system that actively corrects for disturbances, achieving a static operating point where the internal environment remains consistently regulated.

A single button was implemented as a system interrupt to halt the entire control process. This allows the feedback loop to be observed in an open-loop state. Future iterations could expand this functionality, allowing multiple button presses to individually suspend subsystems or to accelerate the process by introducing a derivative constant, though this would require significant additional modeling effort. 
------ ------- -------- ------------ ------------- ------- ------ ---------- ---------- ------------- ---------- ---------- ------ ----
### Notes: 
During the simulation, it's not visible the changes taken part because the time is not envolved and

 
