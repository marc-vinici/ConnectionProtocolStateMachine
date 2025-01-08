#pragma once
#include <chrono>
#include <concepts>
#include <functional>
#include <iostream>
#include <map>
#include <print>
#include <string>

class ConnectionProtocol {
 public:
  ConnectionProtocol(){};

  enum class State { kLinkDown = 0, kSendStart, kSendConfig, kSendKeepalive };

  enum class Event {
    kInterfaceNok = 0,
    kInterfaceOk,
    kPacketNok,
    kPacketOk,
    kPacketNotReceived,
  };

  [[nodiscard]] auto processEvent(State state, Event event) -> const State &;

 private:
  State state_{State::kLinkDown};

  auto set_state(State, Event) -> void;
  auto get_state() -> State &;

  auto LinkDown() -> void;

  auto SendStart() -> void;

  auto SendConfig() -> void;

  auto SendKeepalive() -> void;
};
