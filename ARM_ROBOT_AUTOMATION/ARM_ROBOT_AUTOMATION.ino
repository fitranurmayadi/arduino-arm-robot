#include <Servo.h>
Servo engsel, lengan_atas, lengan_bawah, tangan, jari;

#define ok digitalRead(7)
#define ok1 digitalRead(8)

int pot_degree[] = {0, 0, 0, 0, 0};
int adcpinmap[] = {A0, A1, A2, A3, A4};
//int servo_degree[4];

int counter = 0;

int positionData[][20] = { // 20, 5
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90},
  {90, 90, 90, 90, 90}
};

void setup() {
  Serial.begin(115200);
  pinMode(7, INPUT);
  pinMode(8, INPUT);

  engsel.attach(2);
  delay(500);
  lengan_atas.attach(3);
  delay(500);
  lengan_bawah.attach(4);
  delay(500);
  tangan.attach(5);
  delay(500);
  jari.attach(10);
  delay(500);
  normal();
}

void normal() {
  pot_read();
  int z = engsel.read(); // engsel doing the action
  int y = 90;
  if (z < y) {
    for (int pos = z; pos <= y; pos++) {
      engsel.write(pos);
      delay(20);
    }
  }
  else if (z > y) {
    for (int pos = z; pos >= y; pos--) {
      engsel.write(pos);
      delay(20);
    }
  }
  z = lengan_atas.read(); // lengan_atas doing the action
  y = 90;
  if (z < y) {
    for (int pos = z; pos <= y; pos++) {
      lengan_atas.write(pos);
      delay(20);
    }
  }
  else if (z > y) {
    for (int pos = z; pos >= y; pos--) {
      lengan_atas.write(pos);
      delay(20);
    }
  }
  z = lengan_bawah.read();
  y = 90;
  if (z < y) {
    for (int pos = z; pos <= y; pos++) {
      lengan_bawah.write(pos);
      delay(20);
    }
  }
  else if (z > y) {
    for (int pos = z; pos >= y; pos--) {
      lengan_bawah.write(pos);
      delay(20);
    }
  }
  z = tangan.read();
  y = 90;
  if (z < y) {
    for (int pos = z; pos <= y; pos++) {
      tangan.write(pos);
      delay(20);
    }
  }
  else if (z > y) {
    for (int pos = z; pos >= y; pos--) {
      tangan.write(pos);
      delay(20);
    }
  }
  z = jari.read();
  y = 90;
  if (z < y) {
    for (int pos = z; pos <= y; pos++) {
      jari.write(pos);
      delay(20);
    }
  }
  else if (z > y) {
    for (int pos = z; pos >= y; pos--) {
      jari.write(pos);
      delay(20);
    }
  }
  Serial.print("SELESAI MENJALANKAN LANGKAH KE : ");

}

void pot_read() {
  for (int x = 0; x < 5; x++) {
    pot_degree[x] = analogRead(adcpinmap[x]);
    pot_degree[x] = map(pot_degree[x], 0, 1023, 0, 180);
    delay(1);
  }
}

void servo_write() {
  engsel.write(pot_degree[0]);
  lengan_atas.write(pot_degree[1]);
  lengan_bawah.write(pot_degree[2]);
  tangan.write(pot_degree[3]);
  jari.write(pot_degree[4]);
  delay(20);
}

void robot_auto() {
  for (int x = 0; x < 21; x++) {
    int z = engsel.read(); // engsel doing the action
    int y = positionData[0][x];
    if (z < y) {
      for (int pos = z; pos <= y; pos++) {
        engsel.write(pos);
        delay(20);
      }
    }
    else if (z > y) {
      for (int pos = z; pos >= y; pos--) {
        engsel.write(pos);
        delay(20);
      }
    }
    z = lengan_atas.read(); // lengan_atas doing the action
    y = positionData[1][x];
    if (z < y) {
      for (int pos = z; pos <= y; pos++) {
        lengan_atas.write(pos);
        delay(20);
      }
    }
    else if (z > y) {
      for (int pos = z; pos >= y; pos--) {
        lengan_atas.write(pos);
        delay(20);
      }
    }
    z = lengan_bawah.read();
    y = positionData[2][x];
    if (z < y) {
      for (int pos = z; pos <= y; pos++) {
        lengan_bawah.write(pos);
        delay(20);
      }
    }
    else if (z > y) {
      for (int pos = z; pos >= y; pos--) {
        lengan_bawah.write(pos);
        delay(20);
      }
    }
    z = tangan.read();
    y = positionData[3][x];
    if (z < y) {
      for (int pos = z; pos <= y; pos++) {
        tangan.write(pos);
        delay(20);
      }
    }
    else if (z > y) {
      for (int pos = z; pos >= y; pos--) {
        tangan.write(pos);
        delay(20);
      }
    }
    z = jari.read();
    y = positionData[4][x];
    if (z < y) {
      for (int pos = z; pos <= y; pos++) {
        jari.write(pos);
        delay(20);
      }
    }
    else if (z > y) {
      for (int pos = z; pos >= y; pos--) {
        jari.write(pos);
        delay(20);
      }
    }
    Serial.print("SELESAI MENJALANKAN LANGKAH KE : ");
    Serial.println(x);
  }

  Serial.println("SELESAI BOSS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
}

void loop() {
  pot_read();
  //servo_write();
  if (ok == LOW) {
    delay(1000);
    Serial.print(" MENULIS....");
    for (int x = 0; x < 4; x++) {
      positionData[x][counter] = pot_degree[x];
    }
    delay(1000);
    Serial.print("  LANGKAH [");
    Serial.print(counter);
    Serial.println("] SELESAI");
    counter++;
    if (counter == 20) {
      counter = 0;
    }
  }
  if (ok1 == LOW) {
    delay(1000);
    Serial.println("Menjalankan Program ROBOT");
    robot_auto();
  }
}
