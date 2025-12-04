#include "nrf_handler.h"
#include "config.h"

NRFHandler::NRFHandler(uint8_t cePin, uint8_t csnPin)
    : radio(cePin, csnPin)
{
    packetsSent = 0;
    packetsReceived = 0;
}

void NRFHandler::init() {
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_1MBPS);

    radio.enableDynamicPayloads();

    radio.setChannel(hopList[currentHop]);

    const byte address[6] = "NODE1";
    radio.openReadingPipe(0, address);
    radio.openWritingPipe(address);

    radio.startListening();
}

// REAL interference detection using RPD
bool NRFHandler::isHighInterference() {
    radio.startListening();
    delayMicroseconds(130);  // RPD settle time
    bool rpd = radio.testRPD();
    return rpd;  // 1 = strong signal (> -64 dBm)
}

// Frequency Hopping
void NRFHandler::hopChannel() {
    currentHop = (currentHop + 1) % 4;
    radio.setChannel(hopList[currentHop]);
    delay(5);
}

// Transmit packet
bool NRFHandler::sendPacket(const char* msg) {
    packetsSent++;

    radio.stopListening();
    delayMicroseconds(200);

    bool ok = radio.write(msg, strlen(msg) + 1);

    radio.startListening();

    if (ok) packetsReceived++;

    return ok;
}

// Jamming detection logic
bool NRFHandler::detectJamming() {
    // Periodic heartbeat
    sendPacket("PING");

    float loss = getPacketLoss();

    // RPD detect strong interference
    if (isHighInterference()) {
        hopChannel();
        return true;
    }

    // Packet loss detection
    if (loss > PACKET_LOSS_THRESHOLD) {
        hopChannel();
        return true;
    }

    return false;
}

// Calculate packet loss
float NRFHandler::getPacketLoss() {
    if (packetsSent == 0) return 0;
    return (1 - (float)packetsReceived / packetsSent) * 100;
}
