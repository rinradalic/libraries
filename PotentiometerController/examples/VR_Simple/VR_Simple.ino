const int VR_PIN = 34;  // ADC pin
const int LED_PIN = 2;  // PWM output pin

void setup() {
  Serial.begin(115200);
  pinMode(VR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read VR and map to PWM range (0-255)
  int pwmValue = analogRead(VR_PIN);
  pwmValue = map(pwmValue, 0, 4095, 0, 255);  // Assuming 12-bit ADC on ESP32
  // Set LED brightness
  analogWrite(LED_PIN, pwmValue);
  delay(50);
}