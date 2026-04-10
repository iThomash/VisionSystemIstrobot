from picamera2 import Picamera2, Preview
import serial
import subprocess
import time
import os
import json
import cv2
import numpy as np
from PIL import Image

kernel = np.ones((5,5), np.uint8)

os.environ["LIBCAMERA_LOG_LEVEL"] = "ERROR"
picam2 = Picamera2()
picam2.start_preview(Preview.NULL)
picam2.start()
z = 0
time_sum = 0
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
        try:
                query = json.loads(x)
        except Exception as e:
                print("MAIN LOOP ERROR:", e)
                continue
        print(query)
        if "action" in query and query["action"] == 1:
                z += 1
                t1 = time.time()
                # output_file = f"zdjecie.jpg"
                # picam2.capture_file(output_file)
                time.sleep(0.37)
                img = picam2.capture_array()
                imsave = Image.fromarray(img)
                rgb_im = imsave.convert('RGB')
                rgb_im.save(f"./zdjecia/zdjecie{z}.jpg")
                h = round(0.9 * img.shape[0])
                img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
                img_arr_cut = img_gray[round(0.1 * img.shape[0]) : round(0.8 * img.shape[0]), 0 : img.shape[1]]
                ret, img_thres = cv2.threshold(img_arr_cut, 139, 255, cv2.THRESH_BINARY)
                img_morph = cv2.morphologyEx(img_thres, cv2.MORPH_CLOSE, kernel)
                s1 = [0] * img_morph.shape[1]
                s2 = [0] * img_morph.shape[0]
                # print(img_morph.shape)
                for i in range(img_morph.shape[0]):
                        c = img_morph[i] < 11
                        s2[i] = np.sum(c)
                        for j in range(img_morph.shape[1]):
                                if img_morph[i][j] < 11:
                                        s1[j]+=1
                sum1=0
                sum2=0
                for i in range(len(s1)):
                        if (s1[i]>=101):
                                sum1+=1
                for i in range(len(s2)):
                        if (s2[i]>=101):
                                sum2+=1
                t2 = time.time()
                if sum1/len(s1)>=0.6 and sum2/len(s2) >=0.6:
                        s = f"{{\"result\": \"enemy\", \"x_fill\": {round(sum1/len(s1), 2)}, \"y_fill\": {round(sum2/len(s2), 2)}}}"
                        ser.write(bytes(s, encoding='utf-8'))
                        print("{\"result\": \"enemy\"}")
                elif sum1/len(s1)>=0.19 and sum2/len(s2) >=0.19:
                        s = f"{{\"result\": \"can\", \"x_fill\": {round(sum1/len(s1), 2)}, \"y_fill\": {round(sum2/len(s2), 2)}}}"
                        print(s)
                        ser.write(bytes(s, encoding='utf-8'))
                        print("{\"result\": \"can\"}")
                else:
                        s = f"{{\"result\": \"None\", \"x_fill\": {round(sum1/len(s1), 2)}, \"y_fill\": {round(sum2/len(s2), 2)}}}"
                        ser.write(bytes(s, encoding='utf-8'))
                        print("{\"result\": \"None\"}")
                time_sum += (t2-t1) 

                print(f"Czas sumaryczny: {time_sum} \tIlosc: {z}")
                # print(f"Zdjecie: {round(sum2/len(s2), 2)}\t Czas: {t2-t1}")
