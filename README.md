# Smart Traffic Management System

## Description
The **Smart Traffic Management System** is designed to manage traffic at a four-lane junction using two Arduino Unos, ultrasonic sensors, servo motors, and I2C communication. This system dynamically adjusts traffic signals and operates toll gates based on real-time vehicle density to ensure efficient traffic flow and reduce congestion.

---

## Features
- Dynamic adjustment of traffic signals based on real-time vehicle density.
- Automated toll gate operation using servo motors.
- Ultrasonic sensors for detecting vehicle queues.
- Traffic lights with green, yellow, and red signals for lane-wise control.
- Energy-efficient operation using optimized signal timing.
- I2C communication between two Arduino Unos to manage the traffic system.

---

## Project Components
1. **Arduino Uno (x2)**: One for controlling the traffic signals (Master) and the other for controlling ultrasonic sensors and servo motors (Slave), communicating via I2C.  
2. **Ultrasonic Sensors (x4)**: Measure the distance and detect vehicle queues at each lane (controlled by the Slave).  
3. **Servo Motors (x4)**: Operate the toll gates for vehicle entry and exit (controlled by the Slave).  
4. **Traffic Lights (x4)**: LEDs indicating green (go), yellow (wait), and red (stop) signals for each lane (controlled by the Master).  
5. **Breadboard**: A platform to connect components without soldering.  
6. **Jumper Wires**: Used to connect components to the Arduino boards.  
7. **Power Supply**: Powers the Arduino Unos and other components.  

---

## Software Requirements
- **Arduino IDE**: The software used to write and upload code to the Arduino boards.  
  [Download Arduino IDE](https://www.arduino.cc/en/software)  

---

## Communication Protocol: I2C
The **I2C protocol** allows for communication between two Arduino Unos in this project. One Arduino Uno acts as the **Master** and controls the traffic signals, while the other acts as the **Slave** and controls the ultrasonic sensors and toll gates.

### How I2C Works in This Project
1. The **Master Arduino** reads data from the ultrasonic sensors to determine vehicle density and adjusts the traffic signals (green, yellow, red) accordingly.
2. The **Slave Arduino** controls the ultrasonic sensors for vehicle detection and operates the toll gates based on signals received from the Master.

### I2C Connections:
- **SDA (Data Line)**: Connect the SDA pin of both Arduino Unos (A4 on Arduino Uno).
- **SCL (Clock Line)**: Connect the SCL pin of both Arduino Unos (A5 on Arduino Uno).
- **VCC**: Connect the VCC pin of both Arduino Unos to a 5V supply.
- **GND**: Connect the GND pin of both Arduino Unos to ground.

---

## Arduino Code
The Arduino code is available in the `arduino_code` folder.  
You can open the files using the Arduino IDE and upload them to the Arduino Uno boards for execution.

- **Master Code**: `traffic_master.ino` (Controls traffic lights and sends data to the Slave)
- **Slave Code**: `traffic_slave.ino` (Controls ultrasonic sensors and servo motors)

---

## How to Use
1. **Assemble the hardware**:  
   - Connect the ultrasonic sensors to the **Slave Arduino** for real-time vehicle detection.  
   - Attach the servo motors to the **Slave Arduino** to operate the toll gates.  
   - Use I2C to connect the **Master** and **Slave** Arduino Unos.  
   - Connect LEDs to the **Master Arduino** for traffic signal control (green, yellow, red).  
   - Use jumper wires and breadboard to organize the connections.

2. **Upload the code**:  
   - Open the **Master** code in Arduino IDE and upload it to the **Master Arduino**.  
   - Open the **Slave** code in Arduino IDE and upload it to the **Slave Arduino**.

3. **Power the system**:  
   - Connect the power supply to both Arduino Unos and other components.

4. **Observe the system's operation**:  
   - The **Master Arduino** will adjust the traffic lights and send control signals to the **Slave Arduino** to manage toll gates.  
   - The **Slave Arduino** will control the ultrasonic sensors and operate the toll gates accordingly.

---

