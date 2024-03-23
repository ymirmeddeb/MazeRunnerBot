# MazeRunnerBot

## Abstract
The MazeRunnerBot project is a robotic application designed to autonomously navigate through mazes. Utilizing a combination of sensor inputs and programmed logic, the robot detects and maneuvers around obstacles, aiming for the most efficient path to the exit. A more detailed description of the robot's functionnality is in the MazeRunnerBot_report.pdf file present in this repository.

## Introduction
As part of the Computer Engineering curriculum at the National University of Singapore, this project challenges students to apply principles of robotics, computer vision, and algorithmic problem-solving in a practical, hands-on manner.

## Hardware
The robot is built using the following components:
- Mainboard: Arduino Uno
- Motors: 2x DC Motors with wheels
- Sensors: Ultrasonic distance sensor, line-following sensors
- Power: 6V battery pack

## Software
The software controlling the MazeRunnerBot is written in C++ for Arduino. The main features include obstacle detection, path planning, and motor control. The source code is provided in the `Mbot_Code.ino` file within this repository.

## Algorithm Overview
The MazeRunnerBot uses a simple yet effective algorithm to navigate mazes:
- Forward motion until an obstacle is detected.
- When an obstacle is encountered, the colour sensor under the robot detects the colour.
- A decision-making process based on the sensor readings is put in motion.

## Challenges & Solutions
Throughout the project, we faced challenges such as sensor noise and motor power inconsistencies. These were mitigated through calibration procedures and software filters, enhancing the robot's reliability.

## Conclusion
The MazeRunnerBot successfully met the project's objectives by demonstrating its ability to navigate mazes without human intervention.

## Acknowledgements
Special thanks to our project supervisor and the NUS College of Design and Engineering for providing resources and support.

For a detailed setup, refer to the Wiki section of this repository.

## Contribution Guidelines
We welcome contributions to the MazeRunnerBot project! If you have suggestions or improvements, please open an issue or submit a pull request.

## Pictures of the robot

![2024-03-23 16 04 03](https://github.com/ymirmeddeb/MazeRunnerBot/assets/74667654/fbf5975c-077f-41e2-b887-d2259ee97d02)

![2024-03-23 16 03 59](https://github.com/ymirmeddeb/MazeRunnerBot/assets/74667654/8d925482-481d-42df-bd40-bfaab9c4b6ab)

![2024-03-23 16 03 49](https://github.com/ymirmeddeb/MazeRunnerBot/assets/74667654/bedf7055-c81f-4e68-be8a-285e8ad61bf2)

![2024-03-23 16 03 54](https://github.com/ymirmeddeb/MazeRunnerBot/assets/74667654/b8bf87aa-1032-40df-a672-349aa97880c8)

![2024-03-23 16 04 08](https://github.com/ymirmeddeb/MazeRunnerBot/assets/74667654/ce1d0247-8395-4b77-bd3c-9618cd71f9de)

![2024-03-23 16 04 13](https://github.com/ymirmeddeb/MazeRunnerBot/assets/74667654/d6409a6f-5b1b-4f85-a8d9-e9734dccdf20)

![2024-03-23 16 03 40](https://github.com/ymirmeddeb/MazeRunnerBot/assets/74667654/df9841d1-6484-41e2-a1fb-d3ae99b0687d)
