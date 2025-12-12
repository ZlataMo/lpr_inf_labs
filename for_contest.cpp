#include <iostream>
#include <vector>
#include <climits>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> dims(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> dims[i];
    }
    std::vector<std::vector<long long>> mas(n - 1, std::vector<long long>(n - 1, 0));
    for (int l = 2; l < n; ++l) {
        for (int i = 0; i < n - l; ++i) {
            int j = i + l - 1;
            mas[i][j] = LLONG_MAX;
            for (int k = i; k < j; ++k) {
                long long cost = mas[i][k] + mas[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                mas[i][j] = std::min(mas[i][j], cost);
            }
        }
    }
    std::cout << mas[0][n - 2] << std::endl;
}

