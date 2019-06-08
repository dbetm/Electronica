from picamera import PiCamera
from time import sleep

camera = PiCamera()

# resolución
camera.resolution = (2592, 1944)
camera.framerate = 15
camera.start_preview()
sleep(5)
camera.capture('home/pi/Desktop/max.png')
camera.stop_preview()
