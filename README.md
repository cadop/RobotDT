#RobotDT
## Overview
This project involves integrating various components including Python scripts, Arduino code, simulation scenes, and a robot design. The directory structure of the project is as follows:

- `readme.md`
- `python_script.py`
- `arduino/`
  - `.ino` file (put blank password and wifi info!)
  - `arduino_instructions.md`
- `Scene/`
  - `USD file`
  - `Collected_assets/`
- `Robot/`
  - `Fusion_360.f3d`
  - `URDF/`
    - `meshes/`
    - `.urdf`

## Directory Structure

### Root Directory
- **readme.md**: This file.
- **python_script.py**: Contains the main Python script for the project.

### Arduino Directory
- **arduino/.ino file**: The Arduino sketch file. Ensure to fill in your WiFi details and password.
- **arduino/arduino_instructions.md**: Detailed instructions for setting up and using the Arduino code.

### Scene Directory
- **Scene/USD file**: The main scene file for simulations.
- **Scene/Collected_assets/**: Directory for storing all the assets collected for the scene.

### Robot Directory
- **Robot/Fusion_360.f3d**: The Fusion 360 file for the robot design.
- **Robot/URDF/**: Contains the URDF files and meshes for the robot.
  - **Robot/URDF/meshes/**: Directory for storing mesh files.
  - **Robot/URDF/.urdf**: The URDF file for the robot.

## Instructions

### Python Script
1. Ensure Python is installed on your system.
2. Run the script using the following command:
   ```bash
   python python_script.py
