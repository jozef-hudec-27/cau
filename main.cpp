#include "dnd.hpp"
#include <iostream>

using namespace std;

int main() {
    dnd::Standard_random standard_generator;
    dnd::LCG lcg_generator{65539, 0, 1LL << 31, 47};

    dnd::D6 cube{&standard_generator};
    dnd::die_tester::test_distribution(cube, 1000);

    cube.set_generator(&lcg_generator);
    dnd::die_tester::test_distribution(cube, 1000);

    return 0;
}