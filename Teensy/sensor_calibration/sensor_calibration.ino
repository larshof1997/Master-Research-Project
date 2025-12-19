// Teensy 100 Hz sampling, 1 Hz averaged output

const int SENSOR_PIN = A0;

const unsigned long sampleInterval = 10000; // 10 ms = 100 Hz
unsigned long lastSampleTime = 0;

uint32_t sum = 0;
uint16_t sampleCount = 0;

void setup() {
  Serial.begin(921600);
}

void loop() {
  unsigned long now = micros();

  // Take a sample every 10 ms
  if (now - lastSampleTime >= sampleInterval) {
    lastSampleTime += sampleInterval;

    uint16_t value = analogRead(SENSOR_PIN);
    sum += value;
    sampleCount++;

    // After 100 samples (1 second)
    if (sampleCount == 100) {
      uint16_t average = sum / 100;
      Serial.println(average);

      sum = 0;
      sampleCount = 0;
    }
  }
}
