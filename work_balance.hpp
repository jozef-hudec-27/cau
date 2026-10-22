#ifndef WORK_BALANCE_HPP
#define WORK_BALANCE_HPP

#include <vector>
#include <string>
#include <ostream>

namespace work_balance {
class Worker;

class Work_unit {
    friend class Team;
    std::string name;

public:
    virtual ~Work_unit() = default;
    virtual int get_salary() const = 0;
    virtual std::string print(int depth) const = 0;
    virtual int get_current_workload() const = 0;
    virtual void add_workload(int amount) = 0;

protected:
    explicit Work_unit(const std::string& n);
    std::string get_name() const;
private:
    virtual Worker* get_worker_with_lowest_workload() = 0;
};

class Worker : public Work_unit {
    int salary;
    int workload;

public:
    Worker(const std::string& n, int s);

    int get_salary() const override;

    std::string print(int depth) const override;

    int get_current_workload() const override;
    void add_workload(int amount) override;
private:
    Worker* get_worker_with_lowest_workload() override;
};

class Team : public Work_unit {
    std::vector<Work_unit*> members;

public:
    explicit Team(const std::string& n);

    void add_member(Work_unit* member);

    int get_salary() const override;

    std::string print(int depth) const override;

    int get_current_workload() const override;
    void add_workload(int amount) override;

private:
    Worker* get_worker_with_lowest_workload() override;
};

std::ostream& operator<<(std::ostream& os, const work_balance::Work_unit& work_unit);

}
#endif