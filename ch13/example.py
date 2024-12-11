import RPi.GPIO as GPIO
import time

LED = 32
Switch_input = 29
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(LED, GPIO.OUT)
GPIO.setup(Switch_input, GPIO.IN, pull_up_down=GPIO.PUD_UP)

while True:
    if(GPIO.input(Switch_input)):
        GPIO.output(LED,GPIO.LOW)
    else:
        GPIO.output(LED,GPIO.HIGH)
        
time.sleep(3)