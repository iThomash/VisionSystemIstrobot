#define SHARP_PROSTO A5
#define SHARP_PRAWY A7
#define SHARP_LEWY A6
#define TRIG 3
#define ECHO_PROSTO 2
#define ECHO_PRAWY 5
#define ECHO_LEWY 4

#define SHARP_PROSTO_LB 12
#define SHARP_PROSTO_MB 11
#define SHARP_PRAWY_LB 10
#define SHARP_PRAWY_MB 9
#define SHARP_LEWY_LB 8
#define SHARP_LEWY_MB 7
#define HCSR_PROSTO_LB 6
#define HCSR_PROSTO_MB A4
#define HCSR_PRAWY_LB A3
#define HCSR_PRAWY_MB A2
#define HCSR_LEWY_LB A0
#define HCSR_LEWY_MB A1

int odczyt_SHARP_PROSTO[3] = {0,0,0};
int odczyt_SHARP_PRAWY[3] = {0,0,0};
int odczyt_SHARP_LEWY[3] = {0,0,0};

int ODCZYT_HCSR_PROSTO[3] = {0,0,0};
int ODCZYT_HCSR_PRAWY[3] = {0,0,0};
int ODCZYT_HCSR_LEWY[3] = {0,0,0};

#define SHARP_GRANICA_MAX 40
#define SHARP_GRANICA_SRE 80
#define SHARP_GRANICA_MIN 130

#define HCSR_GRANICA_MAX 50
#define HCSR_GRANICA_SRE 40
#define HCSR_GRANICA_MIN 25

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO_PROSTO, INPUT);
  pinMode(ECHO_PRAWY, INPUT);
  pinMode(ECHO_LEWY, INPUT);

  pinMode(SHARP_PROSTO_LB, OUTPUT);
  pinMode(SHARP_PROSTO_MB, OUTPUT);
  pinMode(SHARP_PRAWY_LB, OUTPUT);
  pinMode(SHARP_PRAWY_MB, OUTPUT);
  pinMode(SHARP_LEWY_LB, OUTPUT);
  pinMode(SHARP_LEWY_MB, OUTPUT);
  pinMode(HCSR_PROSTO_LB, OUTPUT);
  pinMode(HCSR_PROSTO_MB, OUTPUT);
  pinMode(HCSR_PRAWY_LB, OUTPUT);
  pinMode(HCSR_PRAWY_MB, OUTPUT);
  pinMode(HCSR_LEWY_LB, OUTPUT);
  pinMode(HCSR_LEWY_MB, OUTPUT);

  delay(100);
}

unsigned long start1, czas1=0, dystans1; bool czy_start_1 = false; bool juz_obliczono_1 = false;
unsigned long start2, czas2=0, dystans2; bool czy_start_2 = false; bool juz_obliczono_2 = false;
unsigned long start3, czas3=0, dystans3; bool czy_start_3 = false; bool juz_obliczono_3 = false;
unsigned long now;
int wynik_SHARP_PROSTO;
int wynik_SHARP_PRAWY;
int wynik_SHARP_LEWY; 
int wynik_HCSR_PROSTO;
int wynik_HCSR_PRAWY; 
int wynik_HCSR_LEWY;

void loop() {
  for (int i=2; i>=1; i--) {
    odczyt_SHARP_PROSTO[i] = odczyt_SHARP_PROSTO[i-1];
    odczyt_SHARP_PRAWY[i] = odczyt_SHARP_PRAWY[i-1];
    odczyt_SHARP_LEWY[i] = odczyt_SHARP_LEWY[i-1];

    ODCZYT_HCSR_PROSTO[i] = ODCZYT_HCSR_PROSTO[i-1];
    ODCZYT_HCSR_PRAWY[i] = ODCZYT_HCSR_PRAWY[i-1];
    ODCZYT_HCSR_LEWY[i] = ODCZYT_HCSR_LEWY[i-1];
  }

  odczyt_SHARP_PROSTO[0] = analogRead(SHARP_PROSTO);
  delay(1);
  odczyt_SHARP_PRAWY[0] = analogRead(SHARP_PRAWY);
  delay(1);
  odczyt_SHARP_LEWY[0] = analogRead(SHARP_LEWY);
  delay(1);

  czy_start_1 = false;
  czy_start_2 = false;
  czy_start_3 = false;
  juz_obliczono_1 = false;
  juz_obliczono_2 = false;
  juz_obliczono_3 = false;
  czas1 = 0;
  czas2 = 0;
  czas3 = 0;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  bool stan_start_PROSTO = digitalRead(ECHO_PROSTO);
  bool stan_start_PRAWY = digitalRead(ECHO_PRAWY);
  bool stan_start_LEWY = digitalRead(ECHO_LEWY);

  now = micros();

  while (micros() - now <= 63000) {
        if (!czy_start_1 && digitalRead(ECHO_PROSTO)!=stan_start_PROSTO) {start1 = micros(); czy_start_1=true;}
        if (!czy_start_2 && digitalRead(ECHO_PRAWY)!=stan_start_PRAWY) {start2 = micros(); czy_start_2=true;}
        if (!czy_start_3 && digitalRead(ECHO_LEWY)!=stan_start_LEWY) {start3 = micros(); czy_start_3=true;}

        if (czy_start_1 && digitalRead(ECHO_PROSTO)==stan_start_PROSTO && !juz_obliczono_1) {czas1=micros()-start1; juz_obliczono_1=true;}
        if (czy_start_2 && digitalRead(ECHO_PRAWY)==stan_start_PRAWY && !juz_obliczono_2) {czas2=micros()-start2; juz_obliczono_2=true;}
        if (czy_start_3 && digitalRead(ECHO_LEWY)==stan_start_LEWY && !juz_obliczono_3) {czas3=micros()-start3; juz_obliczono_3=true;}
  }

  if (!juz_obliczono_1) dystans1 = 400; else dystans1 = czas1/58;
  if (!juz_obliczono_2) dystans2 = 400; else dystans2 = czas2/58;
  if (!juz_obliczono_3) dystans3 = 400; else dystans3 = czas3/58;

  ODCZYT_HCSR_PRAWY[0] = dystans2;
  ODCZYT_HCSR_PROSTO[0] = dystans1;
  ODCZYT_HCSR_LEWY[0] = dystans3;

  wynik_SHARP_PROSTO = (odczyt_SHARP_PROSTO[0]+odczyt_SHARP_PROSTO[1]+odczyt_SHARP_PROSTO[2])/3;
  wynik_SHARP_PRAWY = (odczyt_SHARP_PRAWY[0]+odczyt_SHARP_PRAWY[1]+odczyt_SHARP_PRAWY[2])/3;
  wynik_SHARP_LEWY = (odczyt_SHARP_LEWY[0]+odczyt_SHARP_LEWY[1]+odczyt_SHARP_LEWY[2])/3;
  wynik_HCSR_PROSTO = (ODCZYT_HCSR_PROSTO[0]+ODCZYT_HCSR_PROSTO[1]+ODCZYT_HCSR_PROSTO[2])/3;
  wynik_HCSR_PRAWY = (ODCZYT_HCSR_PRAWY[0]+ODCZYT_HCSR_PRAWY[1]+ODCZYT_HCSR_PRAWY[2])/3;
  wynik_HCSR_LEWY = (ODCZYT_HCSR_LEWY[0]+ODCZYT_HCSR_LEWY[1]+ODCZYT_HCSR_LEWY[2])/3;

  if (wynik_SHARP_PROSTO<=SHARP_GRANICA_MAX)                                                { digitalWrite(SHARP_PROSTO_LB, LOW); digitalWrite(SHARP_PROSTO_MB, LOW); }
  else if (wynik_SHARP_PROSTO>SHARP_GRANICA_MAX && wynik_SHARP_PROSTO<=SHARP_GRANICA_SRE)   { digitalWrite(SHARP_PROSTO_LB, HIGH); digitalWrite(SHARP_PROSTO_MB, LOW); }
  else if (wynik_SHARP_PROSTO>SHARP_GRANICA_SRE && wynik_SHARP_PROSTO<=SHARP_GRANICA_MIN)   { digitalWrite(SHARP_PROSTO_LB, LOW); digitalWrite(SHARP_PROSTO_MB, HIGH); }
  else { digitalWrite(SHARP_PROSTO_LB, HIGH); digitalWrite(SHARP_PROSTO_MB, HIGH); }

  if (wynik_SHARP_PRAWY<=SHARP_GRANICA_MAX)                                               { digitalWrite(SHARP_PRAWY_LB, LOW); digitalWrite(SHARP_PRAWY_MB, LOW); }
  else if (wynik_SHARP_PRAWY>SHARP_GRANICA_MAX && wynik_SHARP_PRAWY<=SHARP_GRANICA_SRE)   { digitalWrite(SHARP_PRAWY_LB, HIGH); digitalWrite(SHARP_PRAWY_MB, LOW); }
  else if (wynik_SHARP_PRAWY>SHARP_GRANICA_SRE && wynik_SHARP_PRAWY<=SHARP_GRANICA_MIN)   { digitalWrite(SHARP_PRAWY_LB, LOW); digitalWrite(SHARP_PRAWY_MB, HIGH); }
  else { digitalWrite(SHARP_PRAWY_LB, HIGH); digitalWrite(SHARP_PRAWY_MB, HIGH); }

  if (wynik_SHARP_LEWY<=SHARP_GRANICA_MAX)                                              { digitalWrite(SHARP_LEWY_LB, LOW); digitalWrite(SHARP_LEWY_MB, LOW); }
  else if (wynik_SHARP_LEWY>SHARP_GRANICA_MAX && wynik_SHARP_LEWY<=SHARP_GRANICA_SRE)   { digitalWrite(SHARP_LEWY_LB, HIGH); digitalWrite(SHARP_LEWY_MB, LOW); }
  else if (wynik_SHARP_LEWY>SHARP_GRANICA_SRE && wynik_SHARP_LEWY<=SHARP_GRANICA_MIN)   { digitalWrite(SHARP_LEWY_LB, LOW); digitalWrite(SHARP_LEWY_MB, HIGH); }
  else { digitalWrite(SHARP_LEWY_LB, HIGH); digitalWrite(SHARP_LEWY_MB, HIGH); }

  if (wynik_HCSR_PROSTO>=HCSR_GRANICA_MAX)                                              { digitalWrite(HCSR_PROSTO_LB, LOW); digitalWrite(HCSR_PROSTO_MB, LOW);}
  else if (wynik_HCSR_PROSTO<HCSR_GRANICA_MAX && wynik_HCSR_PROSTO>=HCSR_GRANICA_SRE)   { digitalWrite(HCSR_PROSTO_LB, HIGH); digitalWrite(HCSR_PROSTO_MB, LOW);}
  else if (wynik_HCSR_PROSTO<HCSR_GRANICA_SRE && wynik_HCSR_PROSTO>=HCSR_GRANICA_MIN)   { digitalWrite(HCSR_PROSTO_LB, LOW); digitalWrite(HCSR_PROSTO_MB, HIGH);}
  else { digitalWrite(HCSR_PROSTO_LB, HIGH); digitalWrite(HCSR_PROSTO_MB, HIGH);}

  if (wynik_HCSR_PRAWY>=HCSR_GRANICA_MAX)                                             { digitalWrite(HCSR_PRAWY_LB, LOW); digitalWrite(HCSR_PRAWY_MB, LOW);}
  else if (wynik_HCSR_PRAWY<HCSR_GRANICA_MAX && wynik_HCSR_PRAWY>=HCSR_GRANICA_SRE)   { digitalWrite(HCSR_PRAWY_LB, HIGH); digitalWrite(HCSR_PRAWY_MB, LOW);}
  else if (wynik_HCSR_PRAWY<HCSR_GRANICA_SRE && wynik_HCSR_PRAWY>=HCSR_GRANICA_MIN)   { digitalWrite(HCSR_PRAWY_LB, LOW); digitalWrite(HCSR_PRAWY_MB, HIGH);}
  else { digitalWrite(HCSR_PRAWY_LB, HIGH); digitalWrite(HCSR_PRAWY_MB, HIGH);}

  if (wynik_HCSR_LEWY>=HCSR_GRANICA_MAX)                                            { digitalWrite(HCSR_LEWY_LB, LOW); digitalWrite(HCSR_LEWY_MB, LOW);}
  else if (wynik_HCSR_LEWY<HCSR_GRANICA_MAX && wynik_HCSR_LEWY>=HCSR_GRANICA_SRE)   { digitalWrite(HCSR_LEWY_LB, HIGH); digitalWrite(HCSR_LEWY_MB, LOW);}
  else if (wynik_HCSR_LEWY<HCSR_GRANICA_SRE && wynik_HCSR_LEWY>=HCSR_GRANICA_MIN)   { digitalWrite(HCSR_LEWY_LB, LOW); digitalWrite(HCSR_LEWY_MB, HIGH);}
  else { digitalWrite(HCSR_LEWY_LB, HIGH); digitalWrite(HCSR_LEWY_MB, HIGH);}
}
