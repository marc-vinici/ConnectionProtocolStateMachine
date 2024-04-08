#pragma once
#include <iostream>

class ConnectionProtocol
{

public:
    ConnectionProtocol() : state_(State::kLinkDown)
    {
        LinkDown();
    }

    enum class State
    {
        kLinkDown = 0,
        kSendStart,
        kSendConfig,
        kSendKeepalive
    };

    enum class Event
    {
        kInterfaceNok = 0,
        kInterfaceOk,
        kPacketNok,
        kPacketOk,
        kPacketNotReceived,
    };

    auto processEvent(State state, Event event) -> State &;

private:
    State state_;
    
    auto set_state(State state) -> void;
    auto get_state() -> State &;

    auto LinkDown() -> void;

    auto SendStart() -> void;

    auto SendConfig() -> void;

    auto SendKeepalive() -> void;
};
