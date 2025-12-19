// Teensy 4.1: Sensor reading on QUARC trigger, storing in array

const int STROBE_PIN = 2;    // Teensy interrupt pin connected to Quanser
const int SENSOR_PIN = A0;   // Analog sensor input (0-3.3V)

const int MAX_READINGS = 5001; // max number of readings to store

volatile uint16_t sensorValue = 0; // latest sensor reading
volatile bool strobeFlag = false;

uint16_t readings[MAX_READINGS]; // array to store readings
unsigned int readingCount = 0;

unsigned long lastReadingTime = 0;
bool experimentStarted = false;

void onStrobe() {
    sensorValue = analogRead(SENSOR_PIN); 
    strobeFlag = true;
}

void setup() {
    pinMode(STROBE_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(STROBE_PIN), onStrobe, CHANGE);  // both edges
    Serial.begin(2000000);  // high baud for fast logging
}

void loop() {
    if (strobeFlag) {
        strobeFlag = false;

        // Start experiment on first reading
        if (!experimentStarted) {
            experimentStarted = true;
            readingCount = 0;
        }

        // Store reading if there's space
        if (readingCount < MAX_READINGS) {
            readings[readingCount++] = sensorValue;
            lastReadingTime = millis();
        }
    }

    // Check if experiment has started and 1s has passed without readings
    if (experimentStarted && (millis() - lastReadingTime > 1000) && readingCount > 0) {
        // Send all readings over serial
        for (unsigned int i = 0; i < readingCount; i++) {
            Serial.println(readings[i]);
        }

        // Reset experiment
        experimentStarted = false;
        readingCount = 0;
    }
}
