//Distance sensors
#define SHARP_FORWARD_LB 39
#define SHARP_FORWARD_MB 41
#define SHARP_RIGHT_LB 43
#define SHARP_RIGHT_MB 45
#define SHARP_LEFT_LB 47
#define SHARP_LEFT_MB 49
#define HCSR_FORWARD_LB 48
#define HCSR_FORWARD_MB 46
#define HCSR_RIGHT_LB 44
#define HCSR_RIGHT_MB 42
#define HCSR_LEFT_LB 40
#define HCSR_LEFT_MB 38

void setup() {
// initialize serial communication at 9600 bits per second:
Serial.begin(9600);
}

// Functions to read distance sensor values
int readSharp1() {
  return digitalRead(SHARP_LEFT_MB) * 2 + digitalRead(SHARP_LEFT_LB) * 1;
}
int readSharp2() {
  return digitalRead(SHARP_FORWARD_MB) * 2 + digitalRead(SHARP_FORWARD_LB) * 1;
}
int readSharp3() {
  return digitalRead(SHARP_RIGHT_MB) * 2 + digitalRead(SHARP_RIGHT_LB) * 1;
}
int ultra1, ultra2, ultra3 = 0;
int readUltra1() {
  return digitalRead(HCSR_LEFT_MB) * 2 + digitalRead(HCSR_LEFT_LB) * 1;
}
int readUltra2() {
  return digitalRead(HCSR_FORWARD_MB) * 2 + digitalRead(HCSR_FORWARD_LB) * 1;
}
int readUltra3() {
  return digitalRead(HCSR_RIGHT_MB) * 2 + digitalRead(HCSR_RIGHT_LB) * 1;
}

// the loop routine runs over and over again forever:
void loop() {
    Serial.print("{\"Sharp_1\": ");
    Serial.print(readSharp1());  
    Serial.print(", ");
    Serial.print("\"Sharp_2\": ");
    Serial.print(readSharp2());  
    Serial.print(", ");
    Serial.print("\"Sharp_3\": ");
    Serial.print(readSharp3()); 
    Serial.print(", ");
    Serial.print("\"Ultra_1\": ");
    Serial.print(readUltra1());
    Serial.print(", ");
    Serial.print("\"Ultra_2\": ");
    Serial.print(readUltra2());
    Serial.print(", ");
    Serial.print("\"Ultra_3\": ");
    Serial.print(readUltra3());  
    Serial.print("}\n");
    delay(200);
}
// for (int i = 0; i <= 15; i++) {

//   // read the input on analog pin 0:
//   int sensorValue = analogRead(i);
//   // print out the value you read:
//   Serial.print(i);
//   Serial.print("=");
//   Serial.print(sensorValue);
//   Serial.print(", ");
//   }
//   delay(1000); // delay in between reads for stability
// Serial.println(" ");
// }