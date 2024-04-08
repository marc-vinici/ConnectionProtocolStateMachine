#include "ConnectionProtocol.h"
#include "gmock/gmock.h"

#include <array>

using ::testing::Eq;
using State = ConnectionProtocol::State;
using Event = ConnectionProtocol::Event;
using TransitionTuple = std::tuple<State, Event, State>;

class ConnectionProtocolTest : public testing::Test
{
public:
    ConnectionProtocol protocol;
};

TEST_F(ConnectionProtocolTest, TransitionHappyPath)
{
    TransitionTuple transition_happy_path[] = {
        {State::kLinkDown, Event::kInterfaceOk, State::kSendStart},
        {State::kSendStart, Event::kPacketOk, State::kSendConfig},
        {State::kSendConfig, Event::kPacketOk, State::kSendKeepalive},
        {State::kSendKeepalive, Event::kPacketOk, State::kSendKeepalive}};

    for (const auto &state_event : transition_happy_path)
    {
        auto current_state = std::get<0>(state_event);
        auto event = std::get<1>(state_event);
        auto next_state = std::get<2>(state_event);

        ASSERT_THAT(protocol.processEvent(current_state, event), Eq(next_state));
    }
}

TEST_F(ConnectionProtocolTest, TransitionConnectionFailed)
{
    TransitionTuple transition_happy_path[] = {
        {State::kLinkDown, Event::kInterfaceNok, State::kLinkDown},
        {State::kLinkDown, Event::kInterfaceOk, State::kSendStart},
        {State::kSendStart, Event::kPacketOk, State::kSendConfig},
        {State::kSendConfig, Event::kPacketNok, State::kSendConfig},
        {State::kSendConfig, Event::kInterfaceNok, State::kLinkDown},
        {State::kLinkDown, Event::kInterfaceOk, State::kSendStart},
        {State::kSendStart, Event::kPacketOk, State::kSendConfig},
        {State::kSendConfig, Event::kPacketOk, State::kSendKeepalive},
        {State::kSendKeepalive, Event::kPacketNotReceived, State::kSendStart},
        {State::kSendStart, Event::kPacketOk, State::kSendConfig},
        {State::kSendConfig, Event::kPacketOk, State::kSendKeepalive},
        {State::kSendKeepalive, Event::kPacketOk, State::kSendKeepalive}};

    for (const auto &state_event : transition_happy_path)
    {
        auto current_state = std::get<0>(state_event);
        auto event = std::get<1>(state_event);
        auto next_state = std::get<2>(state_event);

        ASSERT_THAT(protocol.processEvent(current_state, event), Eq(next_state));
    }
}