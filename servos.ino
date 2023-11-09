// TODO: Add timers to all functions which move servos.


#include <Servo.h>
Servo servo_a, servo_b, servo_c, servo_d;

int servo_a_pin = 3;
int servo_b_pin = 4;
int servo_c_pin = 5;
int servo_d_pin = 6;

unsigned long servo_current;
unsigned long servo_previous;
const int servo_interval = 30;

int forward_reset = 1;

int pos_a = 0;
int pos_b = 0;
int pos_c = 0;
int pos_d = 0;

int increment_a = 1;
int increment_b = 1;
int increment_c = 1;
int increment_d = 1;

//                 A    B    C    D
int pos_alpha[] = { 60, 120, 120, 60 };
int pos_beta[] = { 100, 80, 80, 100 };

void ServosInit() {
  servo_a.attach(servo_a_pin);
  servo_b.attach(servo_b_pin);
  servo_c.attach(servo_c_pin);
  servo_d.attach(servo_d_pin);
}

void UpdateServos() {
  servo_current = millis();
}

void WalkForward() {

  //Reset the legs
  if (forward_reset > 0) {

    pos_a = pos_alpha[0];
    pos_b = pos_beta[1];

    pos_c = pos_alpha[2];
    pos_d = pos_beta[3];

    servo_a.write(pos_a);
    servo_b.write(pos_b);
    servo_c.write(pos_c);
    servo_d.write(pos_d);

    delay(20);
    forward_reset -= 1;
  }

  servo_current = millis();

  if (servo_current - servo_previous > servo_interval) {
    servo_previous = servo_current;

    pos_a += increment_a;
    pos_b += increment_b;
    pos_c += increment_c;
    pos_d += increment_d;

    servo_a.write(pos_a);
    servo_b.write(pos_b);
    servo_c.write(pos_c);
    servo_d.write(pos_d);

    //Right Side Legs
    if ((pos_a < pos_alpha[0]) || (pos_a > pos_beta[0])) {
      increment_a = -increment_a;
    }

    if ((pos_d < pos_alpha[3]) || (pos_d > pos_beta[3])) {
      increment_d = -increment_d;
    }


    //Left Side Legs
    if ((pos_b > pos_alpha[1]) || (pos_b < pos_beta[1])) {
      increment_b = -increment_b;
    }

    if ((pos_c > pos_alpha[2]) || (pos_c < pos_beta[2])) {
      increment_c = -increment_c;
    }
  }
}


void Stand() {

  pos_a = 90;
  pos_b = 90;
  pos_c = 90;
  pos_d = 90;

  servo_a.write(pos_a);
  servo_b.write(pos_b);
  servo_c.write(pos_c);
  servo_d.write(pos_d);

  forward_reset = 1;
}

void ServoTest(int& start_pos, int pos_min, int pos_max) {

  for (start_pos = pos_min; start_pos < pos_max; start_pos++) {
    servo_a.write(start_pos);
    servo_b.write(start_pos);
    servo_c.write(start_pos);
    servo_d.write(start_pos);
    delay(15);
    if (start_pos == pos_min) {
      Serial.println("MIN");
    }
  }

  for (start_pos = pos_max; start_pos > pos_min; start_pos--) {
    servo_a.write(start_pos);
    servo_b.write(start_pos);
    servo_c.write(start_pos);
    servo_d.write(start_pos);
    delay(15);
    if (start_pos == pos_max) {
      Serial.println("MAX");
    }
  }
}


void MoveLegs(int a, int b, int c, int d) {

  pos_a = a;
  pos_b = b;
  pos_c = c;
  pos_d = d;

  servo_a.write(a);
  servo_b.write(b);
  servo_c.write(c);
  servo_d.write(d);
  delay(20);
}

void PrintPositions() {
  Serial.print("A: ");
  Serial.print(pos_a);
  Serial.print("\t");
  Serial.print("B: ");
  Serial.print(pos_b);
  Serial.print("\t");
  Serial.print("C: ");
  Serial.print(pos_c);
  Serial.print("\t");
  Serial.print("D: ");
  Serial.print(pos_d);
  Serial.print("\t");
  Serial.println();
}
