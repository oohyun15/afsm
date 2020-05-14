/*
* minimalFSM_test.cpp
*
* Create on: May 14, 2020
*     Author: oohyun15
*/

#include <gtest/gtest.h>
#include "testFSM.hpp"


using result = ::afsm::actions::event_process_result;
template <typename T >
using event = afsm::detail::event<T>;

TEST(minimal, OnOff)
{
    minimal fsm;
    
    EXPECT_TRUE(fsm.is_in_state< minimal_def::initial >())
    << "Process 1: Initial State.";

    EXPECT_TRUE(done(fsm.process_event(events::start{})))
    << "Process 2: Change state using event: start{}.";

    EXPECT_FALSE(fsm.is_in_state< minimal_def::initial > ())
    << "Process 3: Check Wrong State.";

    EXPECT_TRUE(fsm.is_in_state< minimal_def::running >())
    << "Process 4: Check Correct State.";

    EXPECT_FALSE(done(fsm.process_event(events::start{})))
    << "Process 5: Can't Change State.";

    EXPECT_TRUE(done(fsm.process_event(events::stop{})))
    << "Process 6: Change state.";

    EXPECT_TRUE(fsm.is_in_state< minimal_def::terminated >())
    << "Process 7: END.";
}