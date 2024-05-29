#RobotDT
## Overview
This project involves integrates a physical robot into omniverse using arduino sketches, python scripting and a scene setup in omniverse.
The directory structure of the project is as follows:

- `readme.md`
- `behavior_script.py`
- `arduino/`
  - `RobotArmPotSender.ino` file (put blank password and wifi info!)
- `Scene/`
  - `USD file`
  - `Collected_assets/`
- `Robot/`
  - `robot_fritzing.png` (Wiring Diagram of Setup)
  - `Fusion_360.f3d`
  - `Demo Flour Bucket.f3d` 
  - `Arm ASM and Shovel.zip` (Assembly with Joint limitations and Shovel)
  - `URDF/`
    - `meshes/`
    - `.urdf`

## Directory Structure

### Root Directory
- **readme.md**: This file.
- **behavior_script.py**: Behavoir Script that provides the scene with Joint Position Updates.

### Arduino Directory
- **RobotArmPotSender/.ino file**: The Arduino sketch file. Ensure to fill in your WiFi details and password.

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
