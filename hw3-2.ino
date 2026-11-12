
const int buttonPin = 2;
const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

int buttonState = LOW;
int lastButtonReading = LOW;

unsigned long debounceTimer = 0;
const unsigned long debounceInterval = 30;

// MODES
int currentMode = 0;

// BLINK
unsigned long blinkTimer = 0;
unsigned long blinkInterval = 1000;
bool blinkOn = true;

// COLORS
int RLightColor = 0;
int GLightColor = 255;
int BLightColor = 255;

int RCurrentColor = 0;
int GCurrentColor = 0;
int BCurrentColor = 0;

void setup() {
  pinMode(buttonPin, INPUT);

  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  setRGBLEDColor(RLightColor, GLightColor, BLightColor);
}

void loop() {
  checkButton();
  updateLEDColor();

  setRGBLEDColor(
    RCurrentColor,
    GCurrentColor,
    BCurrentColor
  );
}

// BUTTON
void checkButton() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonReading) {
    debounceTimer = millis();
  }

  if (millis() - debounceTimer >= debounceInterval) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        changeMode();
      }
    }
  }

  lastButtonReading = reading;
}

// CHANGE MODE
void changeMode() {
  currentMode++;

  if (currentMode >= 4) {
    currentMode = 0;
  }

  blinkTimer = millis();
  blinkOn = true;
}

// UPDATE LED
void updateLEDColor() {

  // MODE 0: STEADY
  if (currentMode == 0) {
    RCurrentColor = RLightColor;
    GCurrentColor = GLightColor;
    BCurrentColor = BLightColor;
  }

  // MODE 1: SLOW BLINK
  else if (currentMode == 1) {
    blinkInterval = 1000;
  }

  // MODE 2: MEDIUM BLINK
  else if (currentMode == 2) {
    blinkInterval = 500;
  }

  // MODE 3: FAST BLINK
  else if (currentMode == 3) {
    blinkInterval = 150;
  }

  if (currentMode != 0) {
    unsigned long currentTime = millis();

    if (currentTime - blinkTimer >= blinkInterval) {
      blinkOn = !blinkOn;
      blinkTimer = currentTime;
    }

    if (blinkOn) {
      RCurrentColor = RLightColor;
      GCurrentColor = GLightColor;
      BCurrentColor = BLightColor;
    }
    else {
      RCurrentColor = 0;
      GCurrentColor = 0;
      BCurrentColor = 0;
    }
  }
}

// RGB OUTPUT (COMMON ANODE)
void setRGBLEDColor(int R, int G, int B) {
  analogWrite(RledPin, 255 - R);
  analogWrite(GledPin, 255 - G);
  analogWrite(BledPin, 255 - B);
}
