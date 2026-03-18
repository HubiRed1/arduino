// F1 Junior Engineer Program - Cadillac F1 Simulation
// System: Shift Lights & DRS Logic

const int POT_PIN = A0;      // Potencjometr symuluje obroty silnika (RPM)
const int DRS_BUTTON = 2;    // Przycisk aktywacji DRS
const int LED_GREEN = 8;     // Dioda: Niskie obroty
const int LED_YELLOW = 9;    // Dioda: Średnie obroty
const int LED_BLUE = 10;     // Dioda: SHIFT (Zmień bieg!)
const int LED_DRS = 11;      // Kontrolka aktywnego DRS

void setup() {
  pinMode(DRS_BUTTON, INPUT_PULLUP); // Przycisk z rezystorem podciągającym
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_DRS, OUTPUT);
  
  Serial.begin(9600); // Konsola do podglądu danych (Telemetria)
}

void loop() {
  // 1. ODCZYT DANYCH (Symulacja telemetrii)
  int rawValue = analogRead(POT_PIN);
  int rpm = map(rawValue, 0, 1023, 0, 15000); // Mapowanie na 0-15k RPM
  bool drsRequested = (digitalRead(DRS_BUTTON) == LOW); // Przycisk wciśnięty

  // 2. LOGIKA SHIFT LIGHTS
  digitalWrite(LED_GREEN, rpm > 10000);
  digitalWrite(LED_YELLOW, rpm > 12500);
  
  // Miganie niebieską diodą przy 14k RPM (Over-rev protection)
  if (rpm > 14000) {
    digitalWrite(LED_BLUE, (millis() / 50) % 2); // Szybkie miganie bez delay()!
  } else {
    digitalWrite(LED_BLUE, LOW);
  }

// 3. LOGIKA DRS
  // System zadziała TYLKO jeśli:
  // - Przycisk jest wciśnięty (LOW)
  // - ORAZ obroty są powyżej 8000
  if (digitalRead(DRS_BUTTON) == LOW) {
    digitalWrite(LED_DRS, HIGH);
  } else {
    digitalWrite(LED_DRS, LOW);
  }

// 4. WYWYSŁANIE DANYCH DO INŻYNIERÓW (Serial Monitor)
  Serial.print("RPM: ");
  Serial.print(rpm);
  Serial.print(" | DRS Status: ");
  
  if (digitalRead(LED_DRS) == HIGH) {
    Serial.println("ACTIVE");
  } else {
    Serial.println("OFF");
  }

  delay(10); // Mały odstęp dla stabilności symulacji
}