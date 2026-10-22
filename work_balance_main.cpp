#include "work_balance.hpp"
#include <iostream>

int main() {
    work_balance::Worker worker1("A", 1), worker2("B", 2), worker3("C", 3);

    work_balance::Team my_team("My team");
    my_team.add_member(&worker1);
    my_team.add_member(&worker2);

    work_balance::Team second_team("Second team");
    second_team.add_member(&worker3);
    second_team.add_member(&my_team);

    std::cout << worker1 ;        // prints 1
    std::cout << my_team ;        // prints 3  (1 + 2)
    std::cout << second_team ;

    return 0;
}