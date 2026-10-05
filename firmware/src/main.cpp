#include <Arduino.h>

constexpr uint32_t BLINK_INTERVAL_MS = 500; // Sets the interval for blinking the LED in milliseconds. 500 ms = 0.5 seconds.
constexpr uint8_t LED_RED_PIN = 4; // Sets the pin number for the red
constexpr uint8_t LED_ON = LOW; // Defines the state for turning the LED ON. HIGH means the pin is set to a high voltage level.
constexpr uint8_t LED_OFF = HIGH; // Defines the state for turning the LED OFF. LOW means


void setup() { 

    // Sets the speed in bits per second (baud) for serial data transmission. 115200 is a common speed for ESP32.
    Serial.begin(115200);
    
    // Print "Boot Ok" to serial, test that the serial connection is working.
    Serial.println("Boot Ok");
  
    // Set the LED pin as an OUTPUT. configures a specific digital pin to behave as an INPUT, OUTPUT, or INPUT_PULLUP
    pinMode(LED_RED_PIN, OUTPUT);
}

void loop() {
    uint32_t now = millis();

    static uint32_t lastBlinkTime = 0; // Stores the last time the LED was toggled. static means it retains its value between function calls.

    static bool ledIsOn = false; // Tracks the current state of the LED. true = ON, false = OFF
    
    if ((now - lastBlinkTime) >= BLINK_INTERVAL_MS ) {
        ledIsOn = !ledIsOn; // Toggle the LED state. If it was ON, turn it OFF, and vice versa.
        digitalWrite(LED_RED_PIN, ledIsOn ? LED_ON : LED_OFF);
        lastBlinkTime = now; // Update the last blink time to the current time.
        Serial.println("Hello World"); // Print "Hello World" to serial each time the LED state changes.
    }
}