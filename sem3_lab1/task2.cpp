#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

class Rollable {
public:
    virtual unsigned roll() = 0;
    virtual ~Rollable() = default;
    virtual std::string name() const = 0;
};

class Dice : public Rollable {
public:
    Dice(unsigned max, unsigned seed)
        : max(max), dstr(1, max), reng(seed) {}
    
    unsigned roll() override {
        return dstr(reng);
    }
    
    std::string name() const override {
        return "Dice_d" + std::to_string(max);
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
          dice3(max, seed + 2000),
          max(max) {}
    
    unsigned roll() override {
        return dice1.roll() + dice2.roll() + dice3.roll();
    }
    
    std::string name() const override {
        return "ThreeDicePool_3d" + std::to_string(max);
    }
    
    unsigned getMinValue() const { return 3; }
    unsigned getMaxValue() const { return 3 * max; }
    
private:
    Dice dice1, dice2, dice3;
    unsigned max;
};

class PenaltyDice : public Rollable {
public:
    PenaltyDice(Rollable &d) : dice(d) {}
    
    unsigned roll() override {
        unsigned r1 = dice.roll();
        unsigned r2 = dice.roll();
        return std::min(r1, r2);
    }
    
    std::string name() const override {
        return "PenaltyDice_" + dice.name();
    }
    
private:
    Rollable &dice;
};

class BonusDice : public Rollable {
public:
    BonusDice(Rollable &d) : dice(d) {}
    
    unsigned roll() override {
        unsigned r1 = dice.roll();
        unsigned r2 = dice.roll();
        return std::max(r1, r2);
    }
    
    std::string name() const override {
        return "BonusDice_" + dice.name();
    }
    
private:
    Rollable &dice;
};

void to_file(Rollable &d, 
                          unsigned min_val, 
                          unsigned max_val, 
                          unsigned rolls_per_val = 50000,
                          const std::string& filename = "data.csv") {
    std::ofstream file(filename);
    file << "value,probability,distribution_name\n";
        
    for (unsigned v = min_val; v <= max_val; ++v) {
        unsigned count = 0;
        for (unsigned i = 0; i < rolls_per_val; ++i) {
            if (d.roll() == v) {
                ++count;
            }
        }
        double prob = static_cast<double>(count) / rolls_per_val;
        
        file << v << "," << std::setprecision(6) << prob 
             << "," << d.name() << "\n";
        
    }
    
    file.close();
}

int main() {
    
    Dice d100(100, 12345);
    PenaltyDice penalty_d100(d100);
    BonusDice bonus_d100(d100);
    
    to_file(d100, 1, 30, 30000, "d100_normal.csv");
    to_file(penalty_d100, 1, 30, 30000, "d100_penalty.csv");
    to_file(bonus_d100, 1, 30, 30000, "d100_bonus.csv");
        
    ThreeDicePool pool3d6(6, 67890);
    PenaltyDice penalty_pool(pool3d6);
    BonusDice bonus_pool(pool3d6);
    
    unsigned pool_min = 3;
    unsigned pool_max = 18;
    
    to_file(pool3d6, pool_min, pool_max, 50000, "3d6_normal.csv");
    to_file(penalty_pool, pool_min, pool_max, 50000, "3d6_penalty.csv");
    to_file(bonus_pool, pool_min, pool_max, 50000, "3d6_bonus.csv");
    
    std::ofstream theory_file("3d6_theoretical.csv");
    theory_file << "value,probability,distribution_name\n";
    
    std::vector<std::pair<unsigned, double>> distribution_3d6 = {
        {3, 1.0/216}, {4, 3.0/216}, {5, 6.0/216}, {6, 10.0/216},
        {7, 15.0/216}, {8, 21.0/216}, {9, 25.0/216}, {10, 27.0/216},
        {11, 27.0/216}, {12, 25.0/216}, {13, 21.0/216}, {14, 15.0/216},
        {15, 10.0/216}, {16, 6.0/216}, {17, 3.0/216}, {18, 1.0/216}
    };
    
    for (const auto& [sum, prob] : distribution_3d6) {
        theory_file << sum << "," << std::setprecision(6) << prob 
                   << "," << "3d6_theoretical" << "\n";
    }
    theory_file.close();
        
    auto compute_expectation = [](Rollable &r, unsigned rolls = 50000) {
        unsigned long long sum = 0;
        for (unsigned i = 0; i < rolls; ++i) {
            sum += r.roll();
        }
        return static_cast<double>(sum) / rolls;
    };
    
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "D100 нормальный:  " << compute_expectation(d100) << "\n";
    std::cout << "D100 penalty:     " << compute_expectation(penalty_d100) << "\n";
    std::cout << "D100 bonus:       " << compute_expectation(bonus_d100) << "\n";
    std::cout << "3D6 нормальный:   " << compute_expectation(pool3d6) << "\n";
    std::cout << "3D6 penalty:      " << compute_expectation(penalty_pool) << "\n";
    std::cout << "3D6 bonus:        " << compute_expectation(bonus_pool) << "\n";
      
    return 0;
}