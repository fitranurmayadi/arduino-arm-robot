#include <Servo.h>
//#include <SoftwareSerial.h>

//SoftwareSerial serial(7, 8); //rx, tx
Servo engsel, lengan_atas, lengan_bawah, tangan, jari;

#define in1 6 //dir left
#define in2 5 //pwm left

#define in3 4 //dir right
#define in4 3 //pwm right

int motorSpeedA = 0;
int motorSpeedB = 0;

void setup() {
  Serial.begin(9600);
  //serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  engsel.attach(A0);
  lengan_atas.attach(A1);
  lengan_bawah.attach(A2);
  tangan.attach(A3);
  jari.attach(A4);
  normal();
}

void normal() {
  engsel.write(85);
  lengan_atas.write(110);
  lengan_bawah.write(100);
  tangan.write(90);
  jari.write(0);
  delay(1000);
}

//arah , arah, pwm, pwm
//maju      1   1   128 128
//mundur    0   0   128 128
//turnLeft  1   0   128 128
//turnRight 0   1   128 128
//stop      0 0 0 0

void motor(int dirRight, int dirLeft, int pwmRight, int pwmLeft) {
  digitalWrite(in1, dirLeft);
  analogWrite(in2, pwmLeft);

  digitalWrite(in3, dirRight);
  analogWrite(in4, pwmRight);
}

void loop() {
  //A:B:C:D:E:DIRA:DIRB:PWMA:PWMB
  String A, B, C, inputString = ""; // string to hold input
  if (Serial.available() > 0) {
    //Serial.println("ada data");
    while (Serial.available() > 0) {
      inputString = Serial.readStringUntil('\n');
      //Serial.print(inputString);
      delay(2);
    }
    //Serial.println();
    A = getValue(inputString, ':', 0);
    B = getValue(inputString, ':', 1);
    C = getValue(inputString, ':', 2);
    //Serial.print(A);Serial.print(":");Serial.print(B);Serial.print(":");Serial.println(C);
    if (A == "P") {
      if (B == "G") { //grab
        jari.write(160);
        delay(50);
      }
      else if (B == "R") { //rilis
        jari.write(0);
        delay(50);
      }
      else if (B == "F") { //maju
        motor(1, 1, 0, 0);
      }
      else if (B == "B") { //mundur
        motor(0, 0, 255, 255);
      }
      else if (B == "S"){ //stop
        motor(0,0,0,0);
      }
    }
    else if (A == "M") {
      
      int z = B.toInt();
      int x = C.toInt();
      x = abs(x - 180);
      lengan_bawah.write(x);
      //lengan_atas.write(x);
      z = abs(z - 180);
      engsel.write(z);
    }
  }
}

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
