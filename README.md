# FW_Test_SantiagoCadena_20251101.zip
## Firmware Test - Powerhouse 

The firmware, written in C++, is an approach of simulating a smart home designed to maintain a specific reference temperature and quality-air standards. It uses a DHT11 sensor for humidity and temperature readings, an air-quaility sensor (MQ135)  and a photoresistor for measuring ambient light in case it's needed. These sensors provide real-time feedback to the system's actuators: Mainly a powered fan for cooling, and as adds white LEDs for illumination, and a buzzer for listening the alarm.  The core idea of the project is to have different sensors measuring constantly the conditions, with this various options for the user: automatic, use a control PID, manual adjusting, and routine mode for activating the actuators depending on the time. 


A Proportional-Integral (PI) control loop for both variables is going to be the mechanism that continuously calculates the error, which is the difference between the measured value and the desired setpoint. The proportional term provides an immediate, corrective response proportional to the current error, while the integral term accounts for the accumulation of past errors, systematically eliminating any persistent offset. Through iterative calculations over time, this combined action drives the total error toward zero, forcing the plant's environment to converge on and maintain the desired heat and brightness levels, regardless of external conditions. To ensure robustness, the plant is modeled as a linear system with intentional distortion, introducing simulated noise and a constant signal gain or offset. This approach mirrors real-world imperfections, ensuring the control algorithm remains effective even when the system is perturbed or operates in an open-loop configuration. By incorporating these constants into the equations for the controlled variables, the PI controller dynamically compensates for these modeled inaccuracies. The final result is a stable system that actively corrects for disturbances, achieving a static operating point where the internal environment remains consistently regulated.

Finaly a single button was implemented as a system interrupt to halt the entire control process. Depending on the number of pushs of the button, the user will choose an option of the menu described before, also if the button is pushed for a while, all the processes will be stopped, and an event will be throwd, or a general interruption will be launched
------ ------- -------- ------------ ------------- ------- ------ ---------- ---------- ------------- ---------- ---------- ------ ----


### Notes: 
- During the simulation, it's not visible the changes taken part because the time is not envolved. It's not visible how the led turns on when darkness comes and the Fan turns on when the heat comes. However I will post a video with a real prototype as seen in the picture. 

- The simulation is found here: https://www.tinkercad.com/things/ic2dglbDgPd/editel?returnTo=%2Fdashboard&sharecode=0zq3XsQe0SSdgSE0Qm9M9Cq1sQz4DY5TgFKvq8320io

- [ESQUEMATIC.png](https://postimg.cc/PLx9rkvK)

- Project's PDF: https://www.overleaf.com/project/69057ca40d29b8df711bec20 where the the logic is explained.
