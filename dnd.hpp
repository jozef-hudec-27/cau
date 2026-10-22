#ifndef DND_HPP
#define DND_HPP

#include <random>
#include <map>

namespace dnd {
class My_random {
private:
protected:

public:
    virtual ~My_random() = default;
    virtual long long next_long() = 0;
};

class Standard_random : public My_random {
private:
    std::mt19937_64 engine{std::random_device{}()};
protected:

public:
    long long next_long() override;
};

class LCG : public My_random {
private:
    long long A, C, M, seed;
    int generated_so_far;
    long long generated_last;
protected:

public:
    LCG(long long A, long long C, long long M, long long seed);

    long long next_long() override;
};

class Die {
private:
protected:

public:
    virtual ~Die() = default;
    virtual void set_generator(My_random* new_generator) = 0;
    virtual int next_value() = 0;
    virtual int get_sides_count() const = 0;
};

class D6 : public Die {
private:
    My_random* generator;
protected:
public:
    explicit D6(My_random* initial_generator);

    void set_generator(My_random* new_generator) override;
    int next_value() override;
    int get_sides_count() const override;
};

class D20 : public Die {
private:
    My_random* generator;
protected:
public:
    explicit D20(My_random* initial_generator);

    void set_generator(My_random* new_generator) override;
    int next_value() override;
    int get_sides_count() const override;
};

class Dn : public Die {
private:
    My_random* generator;
    int n;
protected:
public:
    Dn(My_random* initial_generator, int n);

    void set_generator(My_random* new_generator) override;
    int next_value() override;
    int get_sides_count() const override; 
};

namespace die_tester {
void test_distribution(Die& d, int tries);

double eval_entropy(const std::map<int, int>& counts);
}
}
#endif