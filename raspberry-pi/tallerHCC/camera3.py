from picamera import  PiCamera
from time import sleep

camera = PiCamera()

# alpha [0-255]
camera.start_preview(alpha = 200)
sleep(10)
camera.stop_preview()
