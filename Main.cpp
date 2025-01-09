#include <print>

#include "ConnectionProtocol.h"

int main() {
  std::println("Connection Protocol!");

  ConnectionProtocol connection;

  auto events = std::vector<ConnectionProtocol::Event>{
      ConnectionProtocol::Event::kInterfaceOk,
      ConnectionProtocol::Event::kPacketOk,
      ConnectionProtocol::Event::kPacketNok,
      ConnectionProtocol::Event::kPacketOk,
      ConnectionProtocol::Event::kPacketNotReceived,
      ConnectionProtocol::Event::kInterfaceOk};

  for (const auto& event : events) {
    connection.processEvent(event);
  }

  return 0;
}