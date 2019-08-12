#include <RoboFIFA_UDP.h>

RoboFIFA_UDP* udp_client;

void handlePacket(AsyncUDPPacket packet) {
    Serial.print("UDP Packet Type: ");
    Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
    Serial.print(", From: ");
    Serial.print(packet.remoteIP());
    Serial.print(":");
    Serial.print(packet.remotePort());
    Serial.print(", To: ");
    Serial.print(packet.localIP());
    Serial.print(":");
    Serial.print(packet.localPort());
    Serial.print(", Length: ");
    Serial.print(packet.length());
    Serial.print(", Data: ");
    Serial.write(packet.data(), packet.length());
    Serial.println();
    ////reply to the client
    //packet.printf("Got %u bytes of data", packet.length());
}

void setup()
{
    Serial.begin(115200);
    Serial.println("serial set up");
    char * ssid = "miwifi";
    char * password = "neeneenee";
    int port = 0xF1FA;
    IPAddress server_ip = IPAddress(192,168,43,12);
    delay(2000);
    udp_client = new RoboFIFA_UDP(ssid, password, port, server_ip);
    udp_client->initCommunication(handlePacket);
}

void loop()
{
    delay(1000);
    udp_client->requestCommunication(0);
    //Send broadcast on port 0xF1FA
//    udp.broadcastTo("Anyone here?", port);
}
