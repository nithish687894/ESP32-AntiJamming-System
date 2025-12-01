// nrf_handler.h – Header file

#ifndef NRF_HANDLER_H
#define NRF_HANDLER_H

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

class NRFHandler {
public:
    NRFHandler(uint8_t cePin, uint8_t csnPin);
    void init();
    int getRSSI();
    float getPacketLoss();
    bool detectJamming();

private:
    RF24 radio;
    unsigned long packetsSent;
    unsigned long packetsReceived;
};

#endif
