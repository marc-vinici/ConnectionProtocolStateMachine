#include "ConnectionProtocol.h"

auto ConnectionProtocol::processEvent(State state,
                                      Event event) -> const State& {
  switch (state) {
    case State::kLinkDown:
      if (event == Event::kInterfaceOk) {
        set_state(State::kSendStart, event);
        SendStart();
      } else {
        LinkDown();
      }
      break;
    case State::kSendStart:
      if (event == Event::kPacketOk) {
        set_state(State::kSendConfig, event);
        SendConfig();
      } else if (event == Event::kPacketNok ||
                 event == Event::kPacketNotReceived) {
        set_state(State::kSendStart, event);
        SendStart();
      } else {
        set_state(State::kLinkDown, event);
        LinkDown();
      }
      break;
    case State::kSendConfig:
      if (event == Event::kPacketOk) {
        set_state(State::kSendKeepalive, event);
        SendKeepalive();
      } else if (event == Event::kPacketNotReceived) {
        set_state(State::kSendStart, event);
        SendStart();
      } else if (event == Event::kInterfaceNok) {
        set_state(State::kLinkDown, event);
        LinkDown();
      } else if (event == Event::kPacketNok) {
        SendConfig();
      }
      break;
    case State::kSendKeepalive:
      if (event == Event::kPacketOk) {
        SendKeepalive();
      } else if (event == Event::kPacketNok ||
                 event == Event::kPacketNotReceived) {
        set_state(State::kSendStart, event);
        SendStart();
      } else {
        set_state(State::kLinkDown, event);
        LinkDown();
      }
      break;
  }

  return get_state();
}

auto ConnectionProtocol::set_state(State newState, Event cause) -> void {
  // logging function
  state_ = newState;
}

auto ConnectionProtocol::get_state() -> State& { return state_; }

auto ConnectionProtocol::LinkDown() -> void {
  std::cout << "Link Down" << std::endl;
}

auto ConnectionProtocol::SendStart() -> void {
  std::cout << "Sending Start" << std::endl;
}

auto ConnectionProtocol::SendConfig() -> void {
  std::cout << "Sending Configuration" << std::endl;
}

auto ConnectionProtocol::SendKeepalive() -> void {
  std::cout << "Sending Keepalive" << std::endl;
}