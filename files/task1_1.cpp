#include <iostream>
#include <fstream>
#include <string>

void part1() {
    std::ifstream input("input.txt");
    std::string line;
    while (std::getline(input, line)) {
        std::cout << line << std::endl;
    }
    
    input.close();
}

int main() {
    part1();
    return 0;
}