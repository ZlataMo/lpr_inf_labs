#include <iostream>
#include <chrono>
#include <random>

int mas[1000000] = {};

void random_lin_mas(int size){
    std::default_random_engine rng((int)time(0));
    std::uniform_int_distribution<unsigned>dstr(0, size - 1);

    for (int i = 0; i < size; ++i) {
        mas[i] = dstr(rng);
    }
}

void random_bin_mas(int size){
    std::default_random_engine rng((int)time(0));
    std::uniform_int_distribution<unsigned>dstr(0, 10);
    mas[0] = dstr(rng);
    for (int i = 1; i < size; ++i) {
        mas[i] = mas[i - 1] + dstr(rng);
    }

}

bool linear_func(int start, int end, int size, int x){
    for (int i = 0; i < size; ++i) {
        if (mas[i] == x) {
            return true;
        }
    }
    return false;
}

bool bin_func(int start, int end, int size, int x){
    while (end >= start) {
        size = end - start + 1;
        int mid = start + size/2;
        if (mas[mid] == x) {
            return true;
        }
        else if (mas[mid] > x){
            end = mid - 1;
        }
        else {
            start = mid + 1;
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
    return ((time_span.count() + 0.0)/100);
}

void data_max(bool(*searching)(int start, int end, int size, int x), void(*rand_mas)(int size)){
    for (int size = 100; size <= 1000000; size+=10000) {
        rand_mas(size);
        std::cout << size << ' ' << searching_time(searching,size, -1)<< '\n';
    }
    std::cout << '\n';
}

void data_average(bool(*searching)(int start, int end, int size, int x), void(*rand_mas)(int size)){
    srand((int)time(0));
    for (int size = 100; size <= 1000000; size+=10000) {
        rand_mas(size);
        std::cout << size << ' ' << searching_time(searching, size, rand() % size) << '\n';
    }        
}

int main() {
    int mas[]={};
    int len = 0;
    for(int i=0; i<10000; ++i){
        linear_adding(mas, len, i);
    }
    //data_average(linear_func, random_lin_mas);
}
    