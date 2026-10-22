#include "work_balance.hpp"
#include <climits>

void work_balance::Team::add_member(Work_unit* member) {
    members.push_back(member);
}

work_balance::Work_unit::Work_unit(const std::string& n) : name(n) {}

std::string work_balance::Work_unit::get_name() const {
    return name;
}

work_balance::Worker::Worker(const std::string& n, int s) : Work_unit(n), salary(s), workload(0) {}

work_balance::Team::Team(const std::string& n) : Work_unit{n} {}

int work_balance::Worker::get_salary() const {
    return salary;
}

std::string work_balance::Worker::print(int depth) const {
    return std::string(4 * depth, ' ') + get_name() + " (salary: " + std::to_string(get_salary()) + ")" + "\n";
}

int work_balance::Worker::get_current_workload() const {
    return workload;
}

void work_balance::Worker::add_workload(int amount) {
    workload += amount;
}

work_balance::Worker* work_balance::Worker::get_worker_with_lowest_workload() {
    return this;
}

int work_balance::Team::get_salary() const {
    int total{0};

    for (work_balance::Work_unit* member : members) {
        total += member->get_salary();
    }

    return total;
}

std::string work_balance::Team::print(int depth) const {
    std::string line = std::string(4 * depth, ' ') + get_name() + " (total salary: " + std::to_string(get_salary()) + "):" + "\n";

    for (work_balance::Work_unit* member : members) {
        line += member->print(depth + 1);
    }

    return line;
}

int work_balance::Team::get_current_workload() const {
    int total{0};

    for (work_balance::Work_unit* member : members) {
        total += member->get_current_workload();
    }

    return total;
}

void work_balance::Team::add_workload(int amount) {
    work_balance::Worker* worker = get_worker_with_lowest_workload();

    if (worker == nullptr) return;

    worker->add_workload(amount);
}

work_balance::Worker* work_balance::Team::get_worker_with_lowest_workload() {
    int lowest_workload = INT_MAX;
    work_balance::Worker* worker_with_lowest_workload = nullptr;

    for (work_balance::Work_unit* member : members) {
        work_balance::Worker* m = member->get_worker_with_lowest_workload();

        if (m != nullptr) {
            int member_workload = m->get_current_workload();

            if (member_workload < lowest_workload) {
                lowest_workload = member_workload;
                worker_with_lowest_workload = m;
            }
        }
    }

    return worker_with_lowest_workload;
}

std::ostream& work_balance::operator<<(std::ostream& os, const work_balance::Work_unit& work_unit) {
    os << work_unit.print(0);
    return os;
}