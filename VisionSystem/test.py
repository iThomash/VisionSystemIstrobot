#!/usr/bin/env python3
from picamera2 import Picamera2, Preview
import time
import os
# Utwórz instancję kamery
os.environ["LIBCAMERA_LOG_LEVEL"] = "ERROR"
picam2 = Picamera2()

# Jeśli masz środowisko graficzne, użyj podglądu QT (bez OpenGL)
# Jeśli jesteś przez SSH lub bez monitora — użyj Preview.NULL
picam2.start_preview(Preview.NULL)

# Uruchom kamerę
picam2.start()
output_file = "zdjecie.jpg"
picam2.capture_file(output_file)
#print(f"Zapisano zdjęcie: {output_file}")

# Zatrzymaj kamerę
picam2.stop_preview()
picam2.close()
#print("Podgląd zakończony.")
