#include "../include/my_math.hpp"
#include <cmath>
#include <limits>

static long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}


static double normalize_angle(double x) {
    const double PI = 3.1415;
    const double TWO_PI = 2.0 * PI;
    
    x = std::fmod(x, TWO_PI);
    if (x > PI) {
        x -= TWO_PI;
    } else if (x < -PI) {
        x += TWO_PI;
    }
    return x;
}

AnswerHandler my_sin(double x) {
    AnswerHandler answer;
    answer.x = x;

    x = normalize_angle(x);
    

    double result = 0.0;
    double term = x;
    int n = 1;
    
    for (int i = 0; i < 15; ++i) {
        result += term;
        n += 2;
        term = -term * x * x / ((n - 1) * n);
        
        if (std::abs(term) < std::numeric_limits<double>::epsilon()) {
            break;
        }
    }
    
    answer.result = result;
    return answer;
}

AnswerHandler my_cos(double x) {
    AnswerHandler answer;
    answer.x = x;
    
    x = normalize_angle(x);
    
    double result = 1.0;
    double term = 1.0;
    int n = 0;
    
    for (int i = 0; i < 15; ++i) {
        n += 2;
        term = -term * x * x / ((n - 1) * n);
        result += term;
        
        if (std::abs(term) < std::numeric_limits<double>::epsilon()) {
            break;
        }
    }
    
    answer.result = result;
    return answer;
}

AnswerHandler my_tan(double x) {
    AnswerHandler answer;
    answer.x = x;
    
    AnswerHandler sin_result = my_sin(x);
    AnswerHandler cos_result = my_cos(x);
    
    if (std::abs(cos_result.result) < std::numeric_limits<double>::epsilon()) {
        answer.result = std::numeric_limits<double>::infinity();
    } else {
        answer.result = sin_result.result / cos_result.result;
    }
    
    return answer;
}

AnswerHandler my_exp(double x) {
    AnswerHandler answer;
    answer.x = x;
    
    double result = 1.0;
    double term = 1.0;
    int n = 1;
    
    for (int i = 0; i < 30; ++i) {
        term = term * x / n;
        result += term;
        n++;
        
        if (std::abs(term) < std::numeric_limits<double>::epsilon()) {
            break;
        }
    }
    
    answer.result = result;
    return answer;
}