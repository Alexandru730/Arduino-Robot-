# Arduino Robot Control Project

## Description
This repository contains the code for controlling a robot using an Arduino board. The project incorporates various features such as IR remote control, Bluetooth control, obstacle avoidance, and line tracking. It is designed to be easily customizable and adaptable to different robot configurations.

## Features
- **IR Remote Control:** Enables control of the robot using an infrared remote control.
- **Bluetooth Control:** Allows the user to control the robot via Bluetooth from a smartphone or other devices.
- **Obstacle Avoidance:** Uses ultrasonic sensors to detect obstacles and navigate around them.
- **Line Tracking:** Implements line-following behavior using infrared sensors to follow a predefined path.
- **Speed Adjustment:** Allows dynamic adjustment of the robot's motor speed.

## Installation
1. Connect the required hardware components based on the provided wiring diagram.
2. Upload the Arduino sketch (`robot_control.ino`) to the Arduino board using the Arduino IDE.
3. Open the serial monitor to view debug messages and monitor the robot's behavior.
4. Control the robot using an IR remote control or establish a Bluetooth connection for remote control via a smartphone or other devices.

## Usage
1. Power on the robot and ensure all components are functioning correctly.
2. Use an IR remote control to send commands such as forward, backward, left, right, stop, etc.
3. Alternatively, establish a Bluetooth connection with the robot and send commands using a Bluetooth terminal app on your smartphone.
4. Experiment with different scenarios such as obstacle avoidance and line tracking to observe the robot's behavior.
5. Customize the code as needed to add new features or modify existing behaviors according to your requirements.

## Contributing
Contributions to this project are welcome! If you encounter issues, have suggestions for improvements, or want to add new features, feel free to open an issue or submit a pull request on GitHub.

## Contact
For inquiries, feedback, or support, please contact [alexandruraduica18@gmail.com](mailto:alexandruraduica18@gmail.com).

## Acknowledgments
- [Adafruit Industries](https://www.adafruit.com/) for their NeoPixel library.
- [Ken Shirriff](https://github.com/shirriff) for the IRremote library.
- [Mark Stanley](https://github.com/adafruit) for the Adafruit Motor Shield library.

## References
- [Arduino Official Website](https://www.arduino.cc/)
- [Adafruit Learning System](https://learn.adafruit.com/)
- [IRremote Library GitHub Repository](https://github.com/Arduino-IRremote/Arduino-IRremote)
- [Adafruit NeoPixel Library GitHub Repository](https://github.com/adafruit/Adafruit_NeoPixel)
