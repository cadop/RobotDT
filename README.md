#RobotDT 
## Overview 
## We are working on organizing and uploding all files and instructions!!

This project involves integrates a physical robot into omniverse using arduino sketches, python scripting and a scene setup in omniverse.
The directory structure of the project is as follows:


- `README.md`
- `behavior_script.py`
- `robot_fritzing.png`
- `Fusion360/`
  - `Arm ASM and Shovel.zip`
  - `Demo Flour Bucket.f3d`
- `URDF.zip`
- `Scene/`
  - `USD file`
  - `Collected_assets/`
- `robot_fritzing.png` (Wiring Diagram of Setup)
  
## Directory Structure

### Root Directory
- **readme.md**: This file.
- **behavior_script.py**: Behavoir Script that provides the scene with Joint Position Updates.

### Arduino Directory
- **arduino_data_send/.ino file**: The Arduino sketch file. Ensure to fill in your WiFi details and password.

### Scene Directory
- **Scene/USD file**: The main scene file for simulations.
- **Scene/Collected_assets/**: Directory for storing all the assets collected for the scene.

### URDF.zip Directory
- **URDF\Fusion Description\meshes**: Collision Meshes of Robot Arm.
- **URDF\Fusion Description\urdf**: URDF file of the Robot Arm.



