#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>

int *func_1(int *mas, size_t size, int new_el){
    int *new_mas = new int[size + 1];
    for (size_t i = 0; i < size; ++i){
        new_mas[i] = mas[i];
    }
    new_mas[size] = new_el;
    delete[] mas;
    return new_mas;
}

int *func_2(int *mas, size_t size,size_t num, int new_el){
    if (num > size - 1){
        int *new_mas = new int[size + 100];
        for (size_t i = 0; i < size; ++i){
            new_mas[i] = mas[i];
        }
        delete[] mas;
        return new_mas;
    }
    mas[size] = new_el;
    return mas;
}

int *func_3(int *mas, size_t size,size_t num, int new_el){
    if (num > size - 1){
        int *new_mas = new int[size * 2];
        for (size_t i = 0; i < size; ++i){
            new_mas[i] = mas[i];
        }
        delete[] mas;
        return new_mas;
    }
    mas[size] = new_el;
    return mas;
}

int main(){
    int *mas = new int[0];
    size_t size = 0;
    int num = 0;
    long long int t = 0;
    std::ofstream data_1, data_2, data_3;
    // data_1.open("data_1.txt");
    // data_2.open("data_2.txt");
    data_3.open("data_3.txt");
    for (unsigned cnt = 0; cnt < 100000; ++cnt){
        auto begin = std::chrono::steady_clock::now();
        // mas = func_1(mas, size, cnt);
        // mas = func_2(mas, size, num, cnt);
        mas = func_3(mas, size, num, cnt);
        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        t = t + time_span.count();
        // size++;
        // if (num > size - 1)
        //     size = size + 100;
        if (num > size - 1)
            size = size * 2;
        num++;
        data_3 << cnt << " " << t <<'\n';
    }
    return 0;
}