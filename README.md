# Praca Inżynierska - Fuzja sensoryczna monitorowania otoczenia robota mobilnego

Repozytorium to jest cześcią pracy inżynierskiej ,,Fuzja sensoryczna monitorowania otoczenia robota mobilnego". Praca w całości była wykonywana przez Tomasza Bachorskiego i Kamila Barana. W skład repozytorium wchodzą zarówno pliki wykorzystywane przez robota jak i pliki testowe.

1) IRIS_MEGA_test_czujnikow
  Program służący do wykonania pomiarów i wypisania przeliczonych danych w konsoli UART. Jest to program testowy do czujników ultradźwiękowych, Sharp oraz odbiciowych.

2) IRIS_NANO
  Finalny program wykorzystywany w mikrokontrolerze Arduino Nano. Mikrokontroler ten jest odpowiedzialny za sczytywanie pomiarów na odpowiednich czujnikach, przeliczanie ich i wystawanie na odpowiednie piny. 

3) IRIS_robot
  Program wykorzystywany przez mikrokontroler Arduino Mega 2560. Zbiera on informacje z Arduino Nano oraz systemu wizyjnego na Raspberry Pi, przetwarza te dane, podejmuje decyzje oraz wysyła sygnały na elementy wykonawcze.

4) VisionSystem
  Katalog ten zawiera programy wykorzystywane na mikrokomputerze Raspberry Pi 5. Katalog zawiera następujące pliki:
  - test.py - Plik ten jest wykorzystywany do prostego sprawdzenia czy podłączona kamera działa prawidłowo. Pozwala na sprawdzenie robionych zdjęć. 
  - ImageProcessor.py - Plik ten nie jest wykorzystywany w ostatecznym programie, ale służył on jako plik zapasowy do przechwytywania zdjęcia do zmiennej w programie.
  - AnalyseImage.py - Plik, który można uruchomić na jednostce stacjonarnej, w którym to dokonywano testów i dobierano progi dla poszczególnych funkcji. Przetwarza on zdjęcia w folderze nazywającym się ,,zdjecia". 
  - main.py - Główny plik programu, który jest wykorzystywany podczas jazdy robota. Po otrzymaniu komendy poprzez komunikację UART, wyzwala zdjęcie, przetwarza i odpowiada tym samym kanałem informacyjnym.  
