const int POT_PIN = A0;
const int DRS_BUTTON = 2;
const int ERS_BUTTON = 4;
const int LED_RED = 8;
const int LED_YELLOW = 9;
const int LED_PURPLE = 10;
const int LED_DRS = 11;
const int LED_ERS = 12;

bool ersState = false;
bool drsState = false;
bool lastDRSstate = HIGH;
bool lastERSstate = HIGH;
float ersPower = 100.0; 

void setup() {
  pinMode(ERS_BUTTON, INPUT_PULLUP);
  pinMode(DRS_BUTTON, INPUT_PULLUP);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_PURPLE, OUTPUT);
  pinMode(LED_DRS, OUTPUT);
  pinMode(LED_ERS, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  int rawValue = analogRead(POT_PIN);
  int rpm = map(rawValue, 0, 1023, 0, 15000);
  
  bool currentERSstate = digitalRead(ERS_BUTTON);
  bool currentDRSstate = digitalRead(DRS_BUTTON);

  if (currentDRSstate == LOW && lastDRSstate == HIGH) {
    drsState = !drsState;
    delay(50);
  }
  lastDRSstate = currentDRSstate;

  if (currentERSstate == LOW && lastERSstate == HIGH) {
    ersState = !ersState;
    delay(50);
  }
  lastERSstate = currentERSstate;

  if (ersState && ersPower > 0) {
    ersPower -= 0.2;
  } else if (!ersState && ersPower < 100) {
    ersPower += 0.1;
  }

  if (ersPower <= 0) {
    ersPower = 0;
    ersState = false;
  }

  digitalWrite(LED_DRS, drsState);
  digitalWrite(LED_ERS, ersState);
  digitalWrite(LED_RED, rpm > 10000);
  digitalWrite(LED_YELLOW, rpm > 12500);
  
  if (rpm > 14000) {
    digitalWrite(LED_PURPLE, (millis() / 50) % 2);
  } else {
    digitalWrite(LED_PURPLE, LOW);
  }

  Serial.print("RPM: ");
  Serial.print(rpm);
  
  Serial.print(" | ERS: ");
  Serial.print((int)ersPower);
  Serial.print("%");

  Serial.print(" | DRS: ");
  Serial.println(drsState ? "ACTIVE" : "OFF");

  delay(10);
}