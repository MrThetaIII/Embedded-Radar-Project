import serial
import time
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from math import radians, cos, sin

# Configuration
SERIAL_PORT = 'COM9'  # Replace with your serial port
BAUD_RATE = 9600
MAX_DISTANCE = 50
RADIUS = 200

# Initialize the angle_g global variable
angle_g = 0

# Initialize Serial Communication
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)

# Radar Visualization Setup
fig, ax = plt.subplots()
ax.set_xlim(-RADIUS, RADIUS)
ax.set_ylim(-RADIUS, RADIUS)
circle = plt.Circle((0, 0), RADIUS, color='black', fill='black', alpha=0.8)
ax.add_patch(circle)
line, = ax.plot([], [], color='green')
detected_objects = []

def update_line(angle):
    x = RADIUS * cos(radians(angle))
    y = RADIUS * sin(radians(angle))
    line.set_data([0, x], [0, y])

def update_objects():
    for obj in detected_objects:
        obj['lifetime'] -= 1
        if obj['lifetime'] <= 0:
            obj['marker'].remove()
            detected_objects.remove(obj)
        else:
            x = obj['distance'] * cos(radians(obj['angle']))
            y = obj['distance'] * sin(radians(obj['angle']))
            obj['marker'].set_data(x, y)

def animate(i):
    global angle_g  # Declare angle_g as global to modify it within this function
    if ser.in_waiting:
        data = ser.readline().decode('utf-8').strip()
        print(data)
        if data.startswith('angle:'):
            angle = int(data.split(':')[1])
            angle_g = angle
            update_line(angle)
        elif data.startswith('distance:'):
            distance = int(data.split(':')[1])
            x = distance * RADIUS / MAX_DISTANCE * cos(radians(angle_g))
            y = distance * RADIUS / MAX_DISTANCE * sin(radians(angle_g))
            marker, = ax.plot(x, y, 'ro')
            detected_objects.append({'angle': angle_g, 'distance': distance * RADIUS / MAX_DISTANCE, 'marker': marker, 'lifetime': 50})
    update_objects()

ani = animation.FuncAnimation(fig, animate, interval=100)
plt.show()
