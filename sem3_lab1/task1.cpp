#include <iostream>
#include <random>
#include <memory>

class Rollable {
public:
    virtual unsigned roll() = 0;
    virtual ~Rollable() = default;
};

class Dice : public Rollable {
public:
    Dice(unsigned max, unsigned seed)
        : max(max), dstr(1, max), reng(seed) {}
    
    unsigned roll() override {
        return dstr(reng);
    }
    
    unsigned getMax() const { return max; }
    
private:
    unsigned max;
    std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
};

class ThreeDicePool : public Rollable {
public:
    ThreeDicePool(unsigned max, unsigned seed)
        : dice1(max, seed), 
          dice2(max, seed + 1000), 
          dice3(max, seed + 2000) {}
    
    unsigned roll() override {
        return dice1.roll() + dice2.roll() + dice3.roll();
    }
    
private:
    Dice dice1, dice2, dice3;
};

double expected_value(Rollable &r, unsigned number_of_rolls = 10000) {
    unsigned long long accum = 0;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
        accum += r.roll();
    }
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

int main(){
    Dice d6(6, 123);
    ThreeDicePool pool3d6(6, 456);
    
    std::cout << "E[Dice d6] ≈ " << expected_value(d6, 100000) << std::endl;
    std::cout << "theory: " << (1 + 6) / 2.0 << std::endl;
    
    std::cout << "E[ThreeDicePool] ≈ " << expected_value(pool3d6, 100000) << std::endl;
    std::cout << "theory: " << 3 * (1 + 6) / 2.0 << std::endl;

    return 0;
}