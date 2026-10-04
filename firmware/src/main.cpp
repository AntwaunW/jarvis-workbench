#include <Arduino.h>

//   constexpr uint8_t LED_RED_PIN = ___; X Gives the pin an outlet name. Replace ___ with the pin number you want to use for the LED.
constexpr uint8_t LED_RED_PIN = 4;


void setup() { 
    // Print "Boot Ok" to serial, test that the serial connection is working.
    Serial.println("Boot Ok");
    // Sets the speed in bits per second (baud) for serial data transmission. 115200 is a common speed for ESP32.
    Serial.begin(115200);
    // Set the LED pin as an OUTPUT. configures a specific digital pin to behave as an INPUT, OUTPUT, or INPUT_PULLUP
    pinMode(LED_RED_PIN, OUTPUT);
}

void loop() {
    // LED ON  (active-LOW → ON = LOW)
    digitalWrite(LED_RED_PIN, LOW);
    // Print "hello" to serial.
    Serial.println("Hello World!");
    // Wait 500 ms.
    delay(500);
    // LED OFF (active-LOW → OFF = HIGH)
    digitalWrite(LED_RED_PIN, HIGH);
    // Wait 500 ms.
    delay(500);
}