# FW_Test_SantiagoCadena_20251101.zip
## Firmware Test - Powerhouse 
On this project, the STM32 board was used. Firstlly, the bootloader was loaded on this board, then it was programmed with the Arduino IDE based on C++ code. 
The firmware, written in C++, is an approach of simulating a smart home designed to maintain a specific reference temperature and quality-air standards. It uses a DHT11 sensor for humidity and temperature readings, an air-quaility sensor (MQ135)  and a photoresistor for measuring ambient light in case it's needed. These sensors provide real-time feedback to the system's actuators: Mainly a powered fan for cooling, and as adds white LEDs for illumination, and a buzzer for listening the alarm.  The core idea of the project is to have different sensors measuring constantly the conditions, with this various options for the user: automatic, alert mode, routine and stopping mode, these for activate the different actuators, and all of this activated with an interruption ISR using a button. 

This approach mirrors real-world imperfections, ensuring the control algorithm remains effective even when the system is perturbed or operates in an open-loop configuration. By incorporating these constants into the equations for the controlled variables, the PI controller dynamically compensates for these modeled inaccuracies. The final result is a stable system that actively corrects for disturbances, achieving a static operating point where the internal environment remains consistently regulated.

A single button was implemented as a system interrupt to halt the entire control process. Depending on the number of pushs of the button, the user will choose an option of the menu, and hence the interruption will be will be launched on the system, giving an output on the Arduino console. 
------ ------- -------- ------------ ------------- ------- ------ ---------- ---------- ------------- ---------- ---------- ------ ----
### Notes: 
- During the simulation, it's not visible the changes taken part because the time is not envolved. It's not visible how the led turns on when darkness comes and the Fan turns on when the heat comes. However I will post a video with a real prototype as seen in the picture. 

- The simulation is found here: https://www.tinkercad.com/things/ic2dglbDgPd/editel?returnTo=%2Fdashboard&sharecode=0zq3XsQe0SSdgSE0Qm9M9Cq1sQz4DY5TgFKvq8320io

- [ESQUEMATIC.png](https://postimg.cc/PLx9rkvK)

- Project's PDF: https://www.overleaf.com/project/69057ca40d29b8df711bec20 where the the logic is explained.
