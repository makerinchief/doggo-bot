/*
  DoggoBot Control
  Justin C Kirk 2021

  info@makerinchief.com
  https://www.makerinchief.com/

  Doggo Bot Parts:

  1 x Arduino Nano
  1 x Nano Breakout Board
  1 x Half Size Breadboard
  4 x MG90 Micro Servo
*/

// Have the Doggo start by standing
char doggo_state = 's';

unsigned long current = 0;
unsigned long previous = 0;
long interval = 20;

void setup() {

  Serial.begin(115200);

  ServosInit();
  Stand();

  delay(500);

  Serial.println("Doggo Bot Ready!");
}

void loop() {

  // Make sure to select "No Line Ending" in the dropdown menu for your
  // Serial Monitor window!
  if (Serial.available() > 0) {
    char input = Serial.read();
    doggo_state = input;
  }

  current = millis();

  switch (doggo_state) {
    case 's':
      Stand();
      break;

    case 'f':
      WalkForward();
      break;
  }
}
