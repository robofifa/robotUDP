/*
RoboFIFA_UDP.cpp implements the functions in RoboFIFA_UDP.h

*/
#include "RoboFIFA_UDP.h"

RoboFIFA_UDP::RoboFIFA_UDP(char * ssid, char * password, int port, IPAddress ip) :ssid(ssid), password(password), port(port), ip(ip){
  state = State::unconnected;
}

int RoboFIFA_UDP::initCommunication(void (*packetHandler)(AsyncUDPPacket)){
  int retval = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("WiFi Failed");
      retval = 1;
  }else{
      state = State::onwifi;
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      if(udp.connect(ip, port)) {
          state = State::udp_connected;
          Serial.println("UDP connected");
          udp.onPacket(packetHandler);
          Serial.println("packetHandler in effect");
          // requestCommunication();
      }
  }
  return retval;
}

void RoboFIFA_UDP::requestCommunication(int id){
    char msg[16];
    sprintf(msg, "{\"id\":%i}", id);
    Serial.println(msg);
    udp.broadcastTo(msg, port);
    state = State::receiving;
}

// void RoboFIFA_UDP::receive(){
//   udp.
// }

// void RoboFIFA_UDP::handlePacket(AsyncUDPPacket packet) {
//     Serial.print("UDP Packet Type: ");
//     Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
//     Serial.print(", From: ");
//     Serial.print(packet.remoteIP());
//     Serial.print(":");
//     Serial.print(packet.remotePort());
//     Serial.print(", To: ");
//     Serial.print(packet.localIP());
//     Serial.print(":");
//     Serial.print(packet.localPort());
//     Serial.print(", Length: ");
//     Serial.print(packet.length());
//     Serial.print(", Data: ");
//     Serial.write(packet.data(), packet.length());
//     Serial.println();
//     ////reply to the client
//     //packet.printf("Got %u bytes of data", packet.length());
// }
