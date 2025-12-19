// Teensy fake test
volatile uint16_t sensorValue = 0;
volatile bool newData = false;

unsigned long lastStrobe = 0;
const unsigned long strobeInterval = 1000000; // microseconds = 1 kHz

const int SENSOR_PIN = A0;   // Analog sensor input (0-3.3V)

void fakeStrobe() {
  onStrobe();  // trigger ISR manually
}

void onStrobe() {
  sensorValue = analogRead(SENSOR_PIN); // read actual analog value from pin A0
  newData = true;
}

void setup() {
  Serial.begin(921600); // PC logging
}

void loop() {
  if (micros() - lastStrobe >= strobeInterval) {
    lastStrobe += strobeInterval;
    fakeStrobe();
  }

  if (newData) {
    noInterrupts();
    uint16_t value = sensorValue;
    newData = false;
    interrupts();
    Serial.println(value); // send as ASCII line
  }
}
