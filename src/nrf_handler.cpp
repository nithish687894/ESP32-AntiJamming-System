// nrf_handler.cpp – Implementation

#include "nrf_handler.h"
#include "config.h"

NRFHandler::NRFHandler(uint8_t cePin, uint8_t csnPin)
    : radio(cePin, csnPin) {
    packetsSent = 0;
    packetsReceived = 0;
}

void NRFHandler::init() {
    radio.begin();
    radio.setChannel(108);
    radio.setDataRate(RF24_1MBPS);
    radio.setPALevel(RF24_PA_LOW);
    const byte address[6] = "NODE1";
    radio.openReadingPipe(0, address);
    radio.startListening();
}

int NRFHandler::getRSSI() {
    return random(-100, -40); // Simulated RSSI (NRF24 cannot read actual RSSI)
}

float NRFHandler::getPacketLoss() {
    if (packetsSent == 0) return 0;
    return (1 - (float)packetsReceived / packetsSent) * 100;
}

bool NRFHandler::detectJamming() {
    packetsSent++;

    if (radio.available())
        packetsReceived++;

    int rssi = getRSSI();
    float loss = getPacketLoss();

    if (rssi < RSSI_THRESHOLD || loss > PACKET_LOSS_THRESHOLD)
        return true;

    return false;
}

