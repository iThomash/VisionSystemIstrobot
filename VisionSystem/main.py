from picamera2 import Picamera2, Preview
import serial
import subprocess
import time
import os
import json
import cv2
import numpy as np

kernel = np.ones((5,5), np.uint8)

os.environ["LIBCAMERA_LOG_LEVEL"] = "ERROR"
picam2 = Picamera2()
picam2.start_preview(Preview.NULL)
picam2.start()

ser = serial.Serial(
        # Serial Port to read the data from
        port='/dev/ttyAMA0',
 
        #Rate at which the information is shared to the communication channel
        baudrate = 9600,
   
        #Applying Parity Checking (none in this case)
        parity=serial.PARITY_NONE,
 
       # Pattern of Bits to be read
        stopbits=serial.STOPBITS_ONE,
     
        # Total number of bits to be read
        bytesize=serial.EIGHTBITS,
 
        # Number of serial commands to accept before timing out
        timeout=0.05
)

while 1:
        x=ser.readline()
        if x==b'':
                continue
        query = json.loads(x)
        if query["action"] == 1:
                t1 = time.time()
                img = picam2.capture_array()
                # img_blurred = cv2.medianBlur(img, (5,5))
                
                img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
                ret, img_thres = cv2.threshold(img_gray, 160, 255, cv2.THRESH_BINARY)
                img_morph = cv2.morphologyEx(img_thres, cv2.MORPH_CLOSE, kernel)
                s1 = [0] * img_morph.shape[1]
                s2 = [0] * img_morph.shape[0]
                # print(img_morph.shape)
                for i in range(img_morph.shape[0]):
                        c = img_morph[i] < 50
                        s2[i] = np.sum(c)
                        for j in range(img_morph.shape[1]):
                                if img_morph[i][j] < 50:
                                        s1[j]+=1
                sum1=0
                sum2=0
                for i in range(len(s1)):
                        if (s1[i]>=100):
                                sum1+=1
                for i in range(len(s2)):
                        if (s2[i]>=100):
                                sum2+=1
                t2 = time.time()

                print(f"Zdjecie: {round(sum1/len(s1), 2)}\t Czas: {t2-t1}")
                print(f"Zdjecie: {round(sum2/len(s2), 2)}\t Czas: {t2-t1}")
