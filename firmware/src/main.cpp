#include <Arduino.h>
#include <TFT_eSPI.h>  // Display library; pins/driver come from platformio.ini build_flags

// ---------- Heartbeat LED ----------
constexpr uint32_t BLINK_INTERVAL_MS     = 500;   // LED toggles every 0.5 s
constexpr uint32_t SERIAL_HEARTBEAT_MS   = 5000;  // Serial "alive" print every 5 s
constexpr uint8_t  LED_RED_PIN           = 4;
constexpr uint8_t  LED_ON  = LOW;   // Active-LOW: pin at 0 V lets current flow, so the LED lights
constexpr uint8_t  LED_OFF = HIGH;  // Pin at 3.3 V = no voltage difference, so the LED stays dark

// ---------- Display ----------
TFT_eSPI tft = TFT_eSPI();  // Global so both setup() and loop() can use it

void setup() {
    Serial.begin(115200);
    Serial.println("Boot OK");

    pinMode(LED_RED_PIN, OUTPUT);
    digitalWrite(LED_RED_PIN, LED_OFF);  // Start in a known state, never assume

    // 1) Turn the screen on FIRST, then configure it
    tft.init();

    // 2) Rotation: 0/2 = portrait, 1/3 = landscape. 3 = landscape, flipped 180° from 1
    tft.setRotation(3);

    // 3) Wipe whatever random pixels were there at power-up
    tft.fillScreen(TFT_BLACK);

    // 4) Text: white letters ON a black box, so redraws overwrite cleanly (no flicker)
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    // 5) MC_DATUM = "Middle Center": x,y now marks the CENTER of the text, not its top-left
    tft.setTextDatum(MC_DATUM);

    // 6) Center of a 320x240 landscape screen is (160, 120). Last arg = font NUMBER 4
    tft.drawString("Hello JARVIS", tft.width() / 2, tft.height() / 2, 4);

    // 7) Last line of setup: if you don't see this in serial, the display code hung above
    Serial.println("Display init done");
}

void loop() {
    uint32_t now = millis();

    // --- LED heartbeat ---
    static uint32_t lastBlinkTime = 0;  // static = remembers its value between loop() runs
    static bool ledIsOn = false;

    if (now - lastBlinkTime >= BLINK_INTERVAL_MS) {
        lastBlinkTime = now;
        ledIsOn = !ledIsOn;
        digitalWrite(LED_RED_PIN, ledIsOn ? LED_ON : LED_OFF);
    }

    // --- Serial heartbeat (slow, so it doesn't bury real messages) ---
    static uint32_t lastSerialBeat = 0;
    if (now - lastSerialBeat >= SERIAL_HEARTBEAT_MS) {
        lastSerialBeat = now;
        Serial.println("[heartbeat] alive");
    }
}