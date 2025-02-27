#include <iostream>
#include <chrono>
#include <random>

int mas[1000000] = {};

bool poisk_sum_lin(int beg, int end, int size, int s){
    std::default_random_engine rng((int)time(0));
    std::uniform_int_distribution<unsigned>dstr(0, size - 1);

    for (int i = 0; i < size; ++i) {
        mas[i] = dstr(rng);
    }

    for (int i = 0; i < end+1; ++i) {
        for (int j = 0; j < end+1; ++j) {
            if (mas[i] + mas[j] == s){
                return true;
            }
        }
    }
    return false;
}

bool poisk_sum_smart(int start, int end, int size, int s){
    std::default_random_engine rng((int)time(0));
    std::uniform_int_distribution<unsigned>dstr(0, 10);
    mas[0] = dstr(rng);
    for (int i = 1; i < size; ++i) {
        mas[i] = mas[i - 1] + dstr(rng);
    }

    int cur_sum;
    while (start != end){
        cur_sum = mas[start] + mas[end];
        if (cur_sum < s){
            start += 1;
        }
        else if (cur_sum > s){
            end -= 1;
        }
        else{
            return true;
        }
    }
    return false;
}

float searching_time(bool(*searching)(int start, int end, int size, int x), int size, int x){
    auto begin = std::chrono::steady_clock::now();
    for (unsigned cnt = 100; cnt != 0; --cnt)
        searching(0, size - 1, size, x);
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    return ((time_span.count() + 0.0) / 100);
}

void data_max(bool(*searching)(int start, int end, int size, int x)){
    for (int size = 100; size <= 1000000; size+=9999) {
        std::cout << size << ' ' << searching_time(searching, size, -1) << '\n';
    }
    std::cout << '\n';
}

void data_average(bool(*searching)(int start, int end, int size, int x)){
    srand((int)time(0));
    int er = 30;
    for (int size = 100; size <= 1000000; size+=9999) {
        float s = 0;
        for (int u = 0; u < er; ++u) {
            s += searching_time(searching, size, rand() % size);
        }
        std::cout << size << ' ' << s/(er + 0.0) << '\n';
    }        
}

int main() {
    data_average(poisk_sum_lin);
}
    