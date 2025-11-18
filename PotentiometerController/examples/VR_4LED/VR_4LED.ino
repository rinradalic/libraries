const int VR_PIN = 34;                   // ADC pin
const int LED_PIN[] = { 2, 4, 16, 17 };  // output pins for 4 LEDs

void setup() {
  Serial.begin(115200);
  pinMode(VR_PIN, INPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(LED_PIN[i], OUTPUT);
  }
}

void loop() {
  // Read VR and map to PWM range (0-255)
  int pwmValue = analogRead(VR_PIN);
  pwmValue = map(pwmValue, 0, 4095, 0, 255);  // Assuming 12-bit ADC on ESP32
  if (pwmValue < 51) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(LED_PIN[i], LOW);
    }
  } else if (pwmValue < 102) {
    digitalWrite(LED_PIN[0], HIGH);
    for (int i = 1; i < 4; i++) {
      digitalWrite(LED_PIN[i], LOW);
    }
  } else if (pwmValue < 153) {
    for (int i = 0; i < 2; i++) {
      digitalWrite(LED_PIN[i], HIGH);
    }
    for (int i = 2; i < 4; i++) {
      digitalWrite(LED_PIN[i], LOW);
    }
  } else if (pwmValue < 204) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_PIN[i], HIGH);
    }
    digitalWrite(LED_PIN[3], LOW);
  } else {
    for (int i = 0; i < 4; i++) {
      digitalWrite(LED_PIN[i], HIGH);
    }
  }
  delay(50);
}