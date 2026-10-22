#include "dnd.hpp"
#include <map>
#include <iostream>

long long dnd::Standard_random::next_long() {
    long long value = engine() >> 1;
    return value;
}

int dnd::D6::get_sides_count() const {
    return 6;
}

int dnd::D6::next_value() {
    return generator->next_long() % 6;
}

dnd::D6::D6(My_random* initial_generator) : generator{initial_generator} {}

void dnd::D6::set_generator(My_random* new_generator) {
    generator = new_generator;
}

int dnd::D20::get_sides_count() const {
    return 20;
}

int dnd::D20::next_value() {
    return generator->next_long() % 20;
}

dnd::D20::D20(My_random* initial_generator) : generator{initial_generator} {}

void dnd::D20::set_generator(My_random* new_generator) {
    generator = new_generator;
}

int dnd::Dn::get_sides_count() const {
    return n;
}

int dnd::Dn::next_value() {
    return generator->next_long() % n;
}

dnd::Dn::Dn(My_random* initial_generator, int n) : generator{initial_generator}, n{n} {}

void dnd::Dn::set_generator(My_random* new_generator) {
    generator = new_generator;
}

void dnd::die_tester::test_distribution(Die& d, int tries) {
    std::map<int, int> m;

    for (int i = 0; i < tries; i++) {
        int val = d.next_value();
        m[val]++;
    }

    for (const auto& [key, value] : m) {
        std::cout << key << ": " << value << std::endl;
    }

    std::cout << "Entropy: " << eval_entropy(m) << " bits\n";
}

double dnd::die_tester::eval_entropy(const std::map<int, int>& counts) {
    long long total = 0;

    for (const auto& [key, value] : counts) {
        total += value;
    }

    double entropy = 0.0;
    for (const auto& [key, value] : counts) {
        if (value == 0) continue;

        double p = static_cast<double>(value) / total;
        entropy -= p * std::log2(p);
    }

    return entropy;
}

dnd::LCG::LCG(long long A, long long C, long long M, long long seed) : A{A}, C{C}, M{M}, seed{seed}, generated_so_far{0} {}

long long dnd::LCG::next_long() {
    if (generated_so_far == 0) {
        generated_so_far++;
        generated_last = seed;
        return generated_last;
    }

    generated_last = (A * generated_last + C) % M;
    generated_so_far++;

    return generated_last;
}