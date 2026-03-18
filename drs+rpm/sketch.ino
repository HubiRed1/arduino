const int POT_PIN = A0;
const int DRS_BUTTON = 2;
const int LED_GREEN = 8;
const int LED_YELLOW = 9;
const int LED_BLUE = 10;
const int LED_DRS = 11;

bool drsState = false;
bool lastButtonState = HIGH;

void setup() {
  pinMode(DRS_BUTTON, INPUT_PULLUP);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_DRS, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  int rawValue = analogRead(POT_PIN);
  int rpm = map(rawValue, 0, 1023, 0, 15000);
  
  bool currentButtonState = digitalRead(DRS_BUTTON);

  if (currentButtonState == LOW && lastButtonState == HIGH) {
    drsState = !drsState;
    delay(50);
  }
  lastButtonState = currentButtonState;

  digitalWrite(LED_DRS, drsState);

  digitalWrite(LED_GREEN, rpm > 10000);
  digitalWrite(LED_YELLOW, rpm > 12500);
  
  if (rpm > 14000) {
    digitalWrite(LED_BLUE, (millis() / 50) % 2);
  } else {
    digitalWrite(LED_BLUE, LOW);
  }

  Serial.print("RPM: ");
  Serial.print(rpm);
  Serial.print(" | DRS Status: ");
  Serial.println(drsState ? "ACTIVE" : "OFF");

  delay(10);
}