#ifndef CONFIG_H
#define CONFIG_H

// NRF24 pins
#define NRF_CE 4
#define NRF_CSN 5

// Alerts
#define ALERT_LED 2
#define ALERT_BUZZER 15

// System thresholds
#define PACKET_LOSS_THRESHOLD 40     // % packet loss to trigger hop
#define MONITOR_INTERVAL 200         // ms between checks

#endif
