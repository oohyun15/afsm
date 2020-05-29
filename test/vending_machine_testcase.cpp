/*
 * vending_machine_testcase.cpp
 *
 *  Created on: May 29, 2020
 *      Author: oohyun15
 */

#include <gtest/gtest.h>
#include "vending_machine.hpp"

namespace vending {

using result = ::afsm::actions::event_process_result;
template < typename T >
using event = afsm::detail::event<T>;

TEST(vending_def, off_to_on)
{
    printf("\nINITIALIZE VENDING MACHINE.\n");
    vending_machine vm;
    
    // 1. initial state
    printf("\n1. initial state\n");
    EXPECT_TRUE(vm.is_in_state< vending_def::off >());

    // 2. transitions
    printf("\n2. transitions\n");
    EXPECT_TRUE(done(vm.process_event(events::power_on{})));

    // 3. final state
    printf("\n3. final state\n");
    EXPECT_TRUE(vm.is_in_state< vending_def::on >());
}

TEST(on, maintenance_to_serving)
{
    printf("\nINITIALIZE VENDING MACHINE.\n");
    vending_machine vm;

    // 1. initial state
    printf("\n1. initial state\n");
    EXPECT_TRUE(vm.is_in_state< vending_def::off >());
    EXPECT_TRUE(done(vm.process_event(events::power_on{})));
    EXPECT_TRUE(vm.is_in_state< vending_def::on::out_of_service >());

    EXPECT_TRUE(done(vm.process_event(events::start_maintenance{vending_machine::factory_code})));
    EXPECT_TRUE(vm.is_in_state< vending_def::on::maintenance >());

    EXPECT_TRUE(done(vm.process_event(events::load_goods{ 0, 10 })));
    EXPECT_TRUE(done(vm.process_event(events::set_price{ 0, 10.0 })));

    // 2. transitions
    printf("\n2. transitions\n");
    EXPECT_TRUE(done(vm.process_event(events::end_maintenance{})));

    // 3. final state
    printf("\n3. final state\n");
    EXPECT_TRUE(vm.is_in_state< vending_def::on::serving >());
}

TEST(serving, active_to_idle)
{
    printf("\nINITIALIZE VENDING MACHINE.\n");    
    vending_machine vm{ goods_storage{
        { 0, { 10, 15.0f } },
        { 1, { 100, 5.0f } }
    }};

    // 1. initial state
    printf("\n1. initial state\n");
    EXPECT_TRUE(vm.is_in_state< vending_def::off >());
    EXPECT_TRUE(done(vm.process_event(events::power_on{})));
    EXPECT_TRUE(vm.is_in_state< vending_def::on::serving >());
    EXPECT_TRUE(vm.is_in_state< vending_def::on::serving::idle >());

    EXPECT_TRUE(done(vm.process_event(events::money{10})));
    EXPECT_TRUE(vm.is_in_state< vending_def::on::serving::active >());
    
    // 2. transitions
    printf("\n2. transitions\n");
    EXPECT_TRUE(done(vm.process_event(events::select_item{1})));

    // 3. final state
    printf("\n3. final state\n");
    EXPECT_TRUE(vm.is_in_state< vending_def::on::serving::idle >());
}
}  /* namespace vending */
