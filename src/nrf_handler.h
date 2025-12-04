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
    bool detectJamming();
    float getPacketLoss();
    bool sendPacket(const char* msg);

private:
    RF24 radio;

    unsigned long packetsSent;
    unsigned long packetsReceived;

    bool isHighInterference();
    void hopChannel();

    uint8_t hopList[4] = { 90, 100, 110, 120 };
    uint8_t currentHop = 0;
};

#endif
