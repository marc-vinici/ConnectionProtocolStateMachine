#include "ConnectionProtocol.h"

auto ConnectionProtocol::processEvent(Event event) -> const State& {
  switch (get_state()) {
    case State::kLinkDown:
      if (event == Event::kInterfaceOk) {
        set_state(State::kSendStart, event);
        handleSendStart();
      } else {
        set_state(get_state(), event);
        handleLinkDown();
      }
      break;
    case State::kSendStart:
      if (event == Event::kPacketOk) {
        set_state(State::kSendConfig, event);
        handleSendConfig();
      } else if (event == Event::kPacketNok ||
                 event == Event::kPacketNotReceived) {
        set_state(State::kSendStart, event);
        handleSendStart();
      } else {
        set_state(State::kLinkDown, event);
        handleLinkDown();
      }
      break;
    case State::kSendConfig:
      if (event == Event::kPacketOk) {
        set_state(State::kSendKeepalive, event);
        handleSendKeepalive();
      } else if (event == Event::kPacketNotReceived) {
        set_state(State::kSendStart, event);
        handleSendStart();
      } else if (event == Event::kInterfaceNok) {
        set_state(State::kLinkDown, event);
        handleLinkDown();
      } else if (event == Event::kPacketNok) {
        set_state(get_state(), event);
        handleSendConfig();
      }
      break;
    case State::kSendKeepalive:
      if (event == Event::kPacketOk) {
        handleSendKeepalive();
      } else if (event == Event::kPacketNok ||
                 event == Event::kPacketNotReceived) {
        set_state(State::kSendStart, event);
        handleSendStart();
      } else {
        set_state(State::kLinkDown, event);
        handleLinkDown();
      }
      break;
  }

  return get_state();
}

auto ConnectionProtocol::set_state(State newState, Event cause) -> void {
  // logging function
  logTransition(state_, newState, cause);
  state_ = newState;
}

auto ConnectionProtocol::get_state() -> State& { return state_; }

auto ConnectionProtocol::stateToString(State state) const -> std::string {
  switch (state) {
    case State::kLinkDown:
      return "LinkDown";
    case State::kSendStart:
      return "SendStart";
    case State::kSendConfig:
      return "SendConfig";
    case State::kSendKeepalive:
      return "SendKeepalive";
    default:
      return "Unknown";
  }
}

auto ConnectionProtocol::eventToString(Event event) const -> std::string {
  switch (event) {
    case Event::kInterfaceNok:
      return "InterfaceNok";
    case Event::kInterfaceOk:
      return "InterfaceOk";
    case Event::kPacketNok:
      return "PacketNok";
    case Event::kPacketOk:
      return "PacketOk";
    case Event::kPacketNotReceived:
      return "PacketNotReceived";
    default:
      return "Unknown";
  }
}

auto ConnectionProtocol::logTransition(State oldState, State newState,
                                       Event cause) -> void {
  auto now = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);

  std::ostringstream oss;
  oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
  std::print("[{}] Transition: {} -> {} on event {}\n", oss.str(),
             stateToString(oldState), stateToString(newState),
             eventToString(cause));
}

auto ConnectionProtocol::handleLinkDown() -> void {
  std::cout << "Handling: Link Down" << std::endl;
}

auto ConnectionProtocol::handleSendStart() -> void {
  std::cout << "Handling: Sending Start" << std::endl;
}

auto ConnectionProtocol::handleSendConfig() -> void {
  std::cout << "Handling: Sending Configuration" << std::endl;
}

auto ConnectionProtocol::handleSendKeepalive() -> void {
  std::cout << "Handling: Sending Keepalive" << std::endl;
}