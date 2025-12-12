#include "include/my_math.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>

int main() {

    while(true){
        int x;
        std::cin >> x;
        AnswerHandler my_sin_result = my_sin(x);
        AnswerHandler my_cos_result = my_cos(x);
        AnswerHandler my_tan_result = my_tan(x);
         double std_sin = std::sin(x);
        double std_cos = std::cos(x);
        double std_tan = std::tan(x);

        std::cout << "  sin(x): our=" << std::setw(12) << my_sin_result.result 
                  << " std=" << std::setw(12) << std_sin
                  << " diff=" << std::setw(12) << std::abs(my_sin_result.result - std_sin) << "\n";
        
        std::cout << "  cos(x): our=" << std::setw(12) << my_cos_result.result 
                  << " std=" << std::setw(12) << std_cos
                  << " diff=" << std::setw(12) << std::abs(my_cos_result.result - std_cos) << "\n";
        
        std::cout << "  tan(x): our=" << std::setw(12) << my_tan_result.result 
                  << " std=" << std::setw(12) << std_tan
                  << " diff=" << std::setw(12) << std::abs(my_tan_result.result - std_tan) << "\n";
        
        std::cout << "\n";
        AnswerHandler my_exp_result = my_exp(x);
        double std_exp = std::exp(x);
        
        std::cout << "  exp(" << x << "): our=" << std::setw(12) << my_exp_result.result
                  << " std=" << std::setw(12) << std_exp
                  << " diff=" << std::setw(12) << std::abs(my_exp_result.result - std_exp) << "\n";
    }
    
    return 0;
}