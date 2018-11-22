import pygame
import serial
from pygame.locals import *

pygame.init()
joysticks = []

try:
	ser = serial.Serial("/dev/ttyACM0") #Trying to connect to the arduino via ttyACM0
except:
	ser = serial.Serial("/dev/ttyACM1") #Trying to connect to the arduino via ttyACM1

print("serial initialized")

for joy in range(pygame.joystick.get_count()):
	joysticks.append(pygame.joystick.Joystick(joy))
	joysticks[joy].init()

print(str(pygame.joystick.get_count()) + " joysticks")

while True:
	for event in pygame.event.get():
		if event.type == JOYBUTTONDOWN:
			ser.write(b"l")
			print("Sending data")
