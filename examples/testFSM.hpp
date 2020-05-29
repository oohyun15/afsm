#include <afsm/fsm.hpp>

namespace events {

struct start {};
struct stop {};

}

struct minimal_def : ::afsm::def::state_machine<minimal_def> {
    //@{
    /** @name States */
    struct initial      : state<initial> {};
    struct running      : state<running> {};
    struct terminated   : terminal_state<terminated> {};
    //@}

    using initial_state = initial;
    
    using transitions   = transition_table<
        /*  State       Event               Next        */
        tr< initial,    events::start,      running     >,
        tr< running,    events::stop,       terminated  >
    >;
};

// State machine object
using minimal = ::afsm::state_machine<minimal_def>;

void use()
{
    minimal fsm;
    fsm.process_event(events::start{});
    fsm.process_event(events::stop{});
}