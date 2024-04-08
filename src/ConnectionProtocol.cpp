#include "ConnectionProtocol.h"

auto ConnectionProtocol::processEvent(State state, Event event) -> State &
{
    switch (state)
    {
    case State::kLinkDown:
        if (event == Event::kInterfaceOk)
        {

            set_state(State::kSendStart);
            SendStart();
        }
        else
        {
            LinkDown();
        }
        break;
    case State::kSendStart:
        if (event == Event::kPacketOk)
        {
            set_state(State::kSendConfig);
            SendConfig();
        }
        else if (event == Event::kPacketNok || event == Event::kPacketNotReceived)
        {

            set_state(State::kSendStart);
            SendStart();
        }
        else
        {

            set_state(State::kLinkDown);
            LinkDown();
        }
        break;
    case State::kSendConfig:
        if (event == Event::kPacketOk)
        {

            set_state(State::kSendKeepalive);
            SendKeepalive();
        }
        else if (event == Event::kPacketNotReceived)
        {

            set_state(State::kSendStart);
            SendStart();
        }
        else if (event == Event::kInterfaceNok)
        {

            set_state(State::kLinkDown);
            LinkDown();
        }
        else if (event == Event::kPacketNok)
        {
            SendConfig();
        }
        break;
    case State::kSendKeepalive:
        if (event == Event::kPacketOk)
        {
            SendKeepalive();
        }
        else if (event == Event::kPacketNok || event == Event::kPacketNotReceived)
        {

            set_state(State::kSendStart);
            SendStart();
        }
        else
        {

            set_state(State::kLinkDown);
            LinkDown();
        }
        break;
    }

    return get_state();
}

auto ConnectionProtocol::set_state(State state) -> void
{
    state_ = state;
}

auto ConnectionProtocol::get_state() -> State &
{
    return state_;
}

auto ConnectionProtocol::LinkDown() -> void
{
    std::cout << "Link Down" << std::endl;
}

auto ConnectionProtocol::SendStart() -> void
{
    std::cout << "Sending Start" << std::endl;
}

auto ConnectionProtocol::SendConfig() -> void
{
    std::cout << "Sending Configuration" << std::endl;
}

auto ConnectionProtocol::SendKeepalive() -> void
{
    std::cout << "Sending Keepalive" << std::endl;
}