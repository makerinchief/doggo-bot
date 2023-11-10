/*
  DoggoBot Control
  Justin C Kirk

  Makerinchief 
  www.makerinchief.com
  info@makerinchief.com

  Please read README.md for details

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
