/*
 does low level communication
*/
#ifndef RoboFIFA_UDP_h
#define RoboFIFA_UDP_h

#include <Arduino.h>
#include "WiFi.h"
#include "AsyncUDP.h"


class RoboFIFA_UDP
{
  public:
    RoboFIFA_UDP(char * ssid, char * password, int port, IPAddress ip);
    int initCommunication(void (*packetHandler)(AsyncUDPPacket));
    void requestCommunication(int id);
    // void receive();

    // typedef void (*PacketHandler)(AsyncUDPPacket);
    //
    // static void handlePacket(AsyncUDPPacket packet, void* packetHandler);
    enum class State {
      unconnected,
      onwifi,
      udp_connected,
      receiving,
      error
      };
    State state;

  private:
    AsyncUDP udp;
    IPAddress ip;
    char * ssid;
    char * password;
    int port;
};

#endif
