#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

class CSVTable {
private:
    std::vector<std::vector<int>> data;
    int rows;
    int cols;
    
public:
    CSVTable() : rows(0), cols(0) {}
    
    bool readFromFile(const std::string& filename) {
        std::ifstream input(filename);

        input >> rows >> cols;
        input.ignore();
        
        data.resize(rows, std::vector<int>(cols));
        
        for (int i = 0; i < rows; i++) {
            std::string line;
            
            std::stringstream ss(line);
            std::string cell;
            
            for (int j = 0; j < cols; j++) {
                    data[i][j] = std::stoi(cell);
            }
        }
        
        input.close();
        return true;
    }
    
    void printTable() const {
        const int CELL_WIDTH = 10;
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << std::setw(CELL_WIDTH) << data[i][j];
                
                if (j < cols - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }
        const std::vector<std::vector<int>>& getData() const {
        return data;
    }
    
    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

int main() {
    CSVTable table;
    
    if (table.readFromFile("input.txt")) {
        table.printTable();
    }
    
    return 0;
}