// main.ino – ESP32 Anti-Jamming Detection System
#include <Arduino.h>
#include "nrf_handler.h"
#include "config.h"

NRFHandler nrf(NRF_CE, NRF_CSN);

void setup() {
    Serial.begin(115200);
    delay(1000);

    pinMode(ALERT_LED, OUTPUT);
    pinMode(ALERT_BUZZER, OUTPUT);

    Serial.println("=== ESP32 Anti-Jamming System Started ===");

    nrf.init();
}

void alertUser() {
    digitalWrite(ALERT_LED, HIGH);
    tone(ALERT_BUZZER, 1200, 150);
}

void loop() {
    bool jammed = nrf.detectJamming();

    int rssi = nrf.getRSSI();
    float loss = nrf.getPacketLoss();

    Serial.print("[INFO] RSSI:");
    Serial.print(rssi);
    Serial.print(" dBm | Loss:");
    Serial.print(loss);
    Serial.print("% | Status:");

    if (jammed) {
        Serial.println(" JAMMING DETECTED");
        alertUser();
    } else {
        Serial.println(" OK");
        digitalWrite(ALERT_LED, LOW);
    }

    delay(MONITOR_INTERVAL);
}
