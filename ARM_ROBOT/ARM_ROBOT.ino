#include <Servo.h>
Servo engsel, lengan_atas, lengan_bawah, tangan, jari;

void setup() {
  Serial.begin(115200);
  engsel.attach(A0);
  lengan_atas.attach(A1);
  lengan_bawah.attach(A2);
  tangan.attach(A3);
  jari.attach(A4);
  normal();
}

void normal() {
  engsel.write(80);
  lengan_atas.write(105);
  lengan_bawah.write(110);
  tangan.write(90);
  jari.write(0);
  delay(1000);
}

void loop() {
  String event, data0, data1, inputString = "";    // string to hold input
  if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      inputString = Serial.readStringUntil('\n');
      delay(20);
    }
  }
  event = getValue(inputString, ':', 0);
  data0 = getValue(inputString, ':', 1);
  data1 = getValue(inputString, ':', 2);
  if (event == "P") {
    if (data0 == "G") {
      jari.write(160);
      delay(100);
    }
    else if (data0 == "R") {
      jari.write(0);
      delay(100);
    }
    else if (data0 == "T") {
      int pos = tangan.read();
      if(pos<=120 && pos>=60){
        tangan.write(pos-30);
      }
      else{
        tangan.write(60);
      }
      delay(100);
    }
    else if (data0 == "N") {
      int pos = tangan.read();
      if(pos<=120 && pos>=60){
        tangan.write(pos+30);
      }     
      else{
        tangan.write(120);
      }
    }

  }
  else if (event == "M") {
    int z = data0.toInt();
    int x = data1.toInt();
    x = abs(x - 180);
    lengan_bawah.write(x);
    //lengan_atas.write(x);
    z = abs(z - 180);
    engsel.write(z);
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
