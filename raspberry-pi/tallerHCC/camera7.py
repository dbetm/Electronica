from picamera import PiCamera, Color
from time import sleep

camera = PiCamera()

camera.start_preview()
camera.annotate_background = Color('green')
camera.annotate_foreground = Color('black')
camera.annotate_text = "Hola mundo"

sleep(5)

camera.stop_preview()
