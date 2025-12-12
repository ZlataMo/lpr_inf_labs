#include <fstream>
#include <string>

void part2() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    
    std::string line;
    
    while (std::getline(input, line)) {
        output << line << std::endl;
    }
    
    input.close();
    output.close();
}

int main() {
    part2();
    return 0;
}