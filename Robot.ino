#include <Servo.h>
#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

#define RECV_PIN 2 // Define IR receiver pin

IRrecv irrecv(RECV_PIN);
decode_results results;

#define Trig A4
#define Echo A5

#define LeftPin   A0
#define MiddlePin A1
#define RightPin  A2

#define servoPin  3
#define BEEP      11

#define FORWARD    0xFF02FD
#define BACKWARD   0xFF9867
#define TURNLEFT   0xFFE01F
#define TURNRIGHT  0xFF906F
#define STOP       0xFFA857
#define Buzzer     0xFF7A85
#define Avo_Obs    0xFF18E7
#define TRACK      0xFF30CF

#define stop     0
#define forward  1
#define back     2
#define left     3
#define right    4

int MotSpeed1 = 200;
int MotSpeed2 = 200;

Servo myservo;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(2, 13, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  myservo.attach(servoPin);
  pinMode(BEEP, OUTPUT);
  pixels.begin();
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
}

void motor1(bool PinState1, bool PinState2) {
  digitalWrite(12, PinState1);
  digitalWrite(4, PinState2);
}

void motor2(bool PinState1, bool PinState2) {
  digitalWrite(7, PinState1);
  digitalWrite(8, PinState2);
}

void motor(int dir, int speed1, int speed2) {
  switch(dir) {
    case stop:
      motor1(0, 0);
      motor2(0, 0);
      pixels.clear();
      pixels.show();
      break;

    case forward: 
      motor1(speed1, 0);
      motor2(speed2, 0);
      break;

   case back:
  // Implement back motor logic here
  motor1(0, speed1);
  motor2(0, speed2);
  break;

case left:
  // Implement left motor logic here
  motor1(speed1, 0);
  motor2(0, speed2);
  break;

case right:
  // Implement right motor logic here
  motor1(0, speed1);
  motor2(speed2, 0);
  break;
  }
}

void IR() {
  if (irrecv.decode(&results)) {
    unsigned long res_val = results.value;

    Serial.print("res_val=");
    Serial.println(res_val, HEX);

    irrecv.resume();

    switch(res_val) {
      case FORWARD:
        motor(forward, MotSpeed1, MotSpeed2);
        break;

      case BACKWARD:
        motor(back, MotSpeed1, MotSpeed2);
        break;

      case TURNLEFT:
        motor(left, MotSpeed1, MotSpeed2);
        break;

      case TURNRIGHT:
        motor(right, MotSpeed1, MotSpeed2);
        break;

      case STOP:
        motor(stop, 0, 0);
        break;

      case Buzzer:
        digitalWrite(BEEP, HIGH); // Activează sunetul buzzer-ului
        break;

      case Avo_Obs:
        // Implementează logica pentru evitarea obstacolelor
        // Exemplu simplu: dacă distanța detectată este mai mică decât o anumită valoare, oprește mașina
        if (GetDistance() < 10) {
          motor(stop, 0, 0);
        }
        break;

      case TRACK:
        // Implementează logica pentru urmărirea liniei
        // Exemplu simplu: dacă senzorul de mijloc detectează o linie, continuă înainte, altfel oprește mașina
        if (analogRead(MiddlePin) > 500) {
          motor(forward, MotSpeed1, MotSpeed2);
        } else {
          motor(stop, 0, 0);
        }
        break;
    }
  }
}


float GetDistance() {
  float distance;

  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  distance = pulseIn(Echo, HIGH) / 58.00;

  return distance;
}

void bluetooth() {
  char serialData;

  if(Serial.available() > 0) {
    serialData = Serial.read();
    Serial.println(serialData);

    SetSpeed(serialData);

    switch (serialData) {
      case 'F':
        motor(forward, MotSpeed1, MotSpeed2);
        break;

      case 'B':
        motor(back, MotSpeed1, MotSpeed2);
        break;

      case 'L':
        motor(left, MotSpeed1, MotSpeed2);
        break;

      case 'R':
        motor(right, MotSpeed1, MotSpeed2);
        break;

      case 'O':
        // Activează urmărirea liniei
        // Implementează logica corespunzătoare pentru urmărirea liniei aici
        // Exemplu simplu: dacă senzorul de mijloc detectează o linie, continuă înainte, altfel oprește mașina
        if (analogRead(MiddlePin) > 500) {
          motor(forward, MotSpeed1, MotSpeed2);
        } else {
          motor(stop, 0, 0);
        }
        break;
    }
  }
}


void SetSpeed(char val) {
  if(val == '+') {
    if(MotSpeed1 < 255) {
      MotSpeed1 += 10;
      MotSpeed2 = MotSpeed1;
      if(MotSpeed1 > 255) {
        MotSpeed1 = 255;
        MotSpeed2 = 255;
      }
    }
    Serial.print("speed = ");
    Serial.println(MotSpeed1);
  }
  else if(val == '-') {
    if(MotSpeed1 > 0) {
      MotSpeed1 -= 10;
      MotSpeed2 = MotSpeed1;
      if(MotSpeed1 < 0) {
        MotSpeed1 = 0;
        MotSpeed2 = 0;
      }
    }
    Serial.print("speed = ");
    Serial.println(MotSpeed1);
  }
}

void PrintData() {
  static unsigned long PrintTime = 0;

  if (millis() - PrintTime >= 1000) {
    PrintTime = millis();
    Serial.print("left = ");
    Serial.println(analogRead(LeftPin));
    Serial.print("middle = ");
    Serial.println(analogRead(MiddlePin));
    Serial.print("right = ");
    Serial.println(analogRead(RightPin));
    // MeasurVoltage();
  }
}

void loop() {
  IR();
  bluetooth();
  PrintData();
}



