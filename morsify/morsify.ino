// Schematic:
// BUTTON ----- tin foil
//
// GND -------- tin foil
#define BUTTON 31

// Morse lookup table
String patterns[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
  "....", "..", ".---", "-.-", ".-..", "--", "-.",
  "---", ".--.", "--.-", ".-.", "...", "-", "..-",
  "...-", ".--", "-..-", "-.--", "--..",
  ".----", "..---", "...--", "....-", ".....",
  "-....", "--...", "---..", "----.", "-----",
  "----"};
char letters[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";

// Morse timings (for baud rate = 9600)
int dot_time = 4;  // max
int dash_time = 8;  // max
int read_time = 12;  // min
String pattern;

// Button state
int state = 0;

// Counters
int release_time = 0;
int press_time = 0;
int sleep = 50;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // Invert button state
  state = 1 - digitalRead(BUTTON);
  delay(sleep);

  // Button currently released
  if (state == 0) {
    // Reset press time after interpretting it
    if (press_time != 0) {
//       Serial.print("PRESSED: ");
//       Serial.println(press_time);
      if (press_time <= dot_time) {
        pattern.concat(".");
      }
      else if (press_time <= dash_time) {
        pattern.concat("-");
      }
      press_time = 0;
    }

    // Print character
    if (release_time >= read_time) {
      release_time = 0;
      keyPress();
      pattern = "";
    }
    release_time++;
  }
  
  // Button currently pressed
  else if (state == 1) {
    if (release_time != 0) {
//       Serial.print("RELEASED: ");
//       Serial.println(release_time);
      release_time = 0;
    }
    press_time++;
  }

  // Serial.println(pattern);
}

void keyPress() {
  int i = 0;

  // Loop through all defined (https://forum.arduino.cc/t/loop-over-array-values/176068)
  for (i=0; i<sizeof patterns/sizeof patterns[0]; i++) {
    String candidate = patterns[i];
    if (pattern == candidate) {
      break;
    }
  }

  if (i != sizeof patterns/sizeof patterns[0]) {  // Found a defined pattern
    Serial.println(letters[i]);
  }
}
