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

  [[nodiscard]] auto processEvent(Event event) -> const State &;

 private:
  State state_{State::kLinkDown};

  auto set_state(State newState, Event cause) -> void;
  auto get_state() -> State &;

  [[nodiscard]] auto stateToString(State state) const -> std::string;
  [[nodiscard]] auto eventToString(Event event) const -> std::string;

  auto logTransition(State oldState, State newState, Event cause) -> void;

  auto handleLinkDown() -> void;

  auto handleSendStart() -> void;

  auto handleSendConfig() -> void;

  auto handleSendKeepalive() -> void;
};
