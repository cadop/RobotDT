from omni.kit.scripting import BehaviorScript
import socket 
from pxr import  Gf
import numpy as np
import math  
import carb 

class Puppet2(BehaviorScript): 
    def on_init(self):
        # carb.log_warn("start warning")
        print(f"{__class__.__name__}.on_init()->{self.prim_path}")

        # Set up the server address and port
        UDP_IP = "your_IP"
        UDP_PORT = 8881

        # Create a UDP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((UDP_IP, UDP_PORT))
        self.sock.setblocking(0)

        # carb.log_warn("Waiting for data...")

    def on_destroy(self):
        print(f"{__class__.__name__}.on_destroy()->{self.prim_path}")
        self.sock = None
        rot = [0, 0, 0]
        self.prim.GetAttribute('xformOp:rotateXYZ').Set(Gf.Vec3d(rot))

    def on_play(self): 
        print(f"{__class__.__name__}.on_play()->{self.prim_path}")
        # Set up the server address and port
        UDP_IP = "your_IP"
        UDP_PORT = 8881

        # Create a UDP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((UDP_IP, UDP_PORT))
        self.sock.setblocking(0)

        # Time interval between sensor readings in seconds
        self.dt = 0.02

    def on_pause(self):
        print(f"{__class__.__name__}.on_pause()->{self.prim_path}")

    def on_stop(self):
        print(f"{__class__.__name__}.on_stop()->{self.prim_path}")
        self.on_destroy()

    def on_update(self, current_time: float, delta_time: float):
        self.get_data()

    def get_data(self):
        # # Receive data from the Arduino
        data = self.clear_socket_buffer()
        if data is None: return 
        # Decode the data and split it into Pitch and Roll
        data = data.decode()
        # carb.log_info(data)
        

        # Get potentiometer values and fsr reading
        # pot_1, pot_2, pot_3, pot_4 = data.split(",")
        pot_1, pot_2, pot_3, pot_4, fsrReading = data.split(",")

        pot_1 = (360 * float(pot_1)/1024)
        pot_2 = (360 * float(pot_2)/1024)
        pot_3 = (360 * float(pot_3)/1024)
        pot_4 = -(360 * float(pot_4)/1024)

        # Get the prims of each joint
        base_prim = self.stage.GetPrimAtPath("/DigiTwin/Base_1/Revolute10")
        shoulder_prim = self.stage.GetPrimAtPath("/DigiTwin/R1_1/Revolute11")
        elbow_prim = self.stage.GetPrimAtPath("/DigiTwin/Link1_1/Revolute12")
        wrist_prim = self.stage.GetPrimAtPath("/DigiTwin/Link2_1/Revolute13")

        cylinder_prim = self.stage.GetPrimAtPath("/physicsScene/Cylinder")


        # Set the joint attribute position 
        attr = "drive:angular:physics:targetPosition"
        base_prim.GetAttribute(attr).Set(float(pot_1))
        shoulder_prim.GetAttribute(attr).Set(float(pot_2))
        elbow_prim.GetAttribute(attr).Set(float(pot_3))
        wrist_prim.GetAttribute(attr).Set(float(pot_4))

        # FSR mapping
        fsrValue = float(fsrReading)
        if fsrValue < 100:
            scale_factor = 0.1
        elif fsrValue > 300:
            scale_factor = 1.0
        else:
            scale_factor = 0.1 + (fsrValue - 100) * (0.9 / 200)  # Linear map from 100 to 300

        # Apply scale
        cylinder_prim.GetAttribute('xformOp:scale').Set(Gf.Vec3f(scale_factor, scale_factor, scale_factor))

    def clear_socket_buffer(self):
        # Function to clear the socket's buffer
        latest_data = None
        while True:
            try:
                # Try to read data from the socket in a non-blocking way
                latest_data, addr = self.sock.recvfrom(1024)
            except BlockingIOError:
                # No more data to read (buffer is empty)
                return latest_data
