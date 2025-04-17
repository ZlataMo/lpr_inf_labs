#include <iostream>
#include <chrono>
#include <fstream>
#include <stdexcept>

struct Queue {
    int* data;
    size_t capacity;
    size_t read_idx;
    size_t write_idx;
    size_t size;
};

void queue_new(Queue& queue, size_t init_cap = 4) {
    queue.data = new int[init_cap];
    queue.capacity = init_cap;
    queue.read_idx = 0;
    queue.write_idx = 0;
    queue.size = 0;
}

void queue_del(Queue& queue) {
    delete[] queue.data;
    queue.data = nullptr;
    queue.capacity = 0;
    queue.read_idx = 0;
    queue.write_idx = 0;
    queue.size = 0;
}

bool queue_poll(Queue& queue, int& el) {
    if (queue.size == 0)
        return false;    
    el = queue.data[queue.read_idx];
    queue.read_idx = (queue.read_idx + 1) % queue.capacity;
    queue.size--;
    return true;
}

bool resize_queue(Queue& queue) {
    size_t new_cap = queue.capacity * 2;
    int* new_data = new int[new_cap];
    for (size_t i = 0; i < queue.size; ++i) {
        new_data[i] = queue.data[(queue.read_idx + i) % queue.capacity];
    }
    delete[] queue.data;
    queue.data = new_data;
    queue.read_idx = 0;
    queue.write_idx = queue.size;
    queue.capacity = new_cap;
    return true;
}

bool queue_push(Queue& queue, int el) {
    if (queue.size == queue.capacity) {
        if (!resize_queue(queue))
            return false;
    }    
    queue.data[queue.write_idx] = el;
    queue.write_idx = (queue.write_idx + 1) % queue.capacity;
    queue.size++;
    return true;
}

int main() {
    std::ofstream data;
    data.open("data.txt");
    const size_t max_operations = 1000000;
    const size_t step = 10000;
    Queue queue;
    queue_new(queue);
    for (size_t n = step; n <= max_operations; n += step) {
        auto begin_push = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < n; ++i) {
            if (!queue_push(queue, i)) {
                throw std::runtime_error("Push failed");
            }
        }
        auto end_push = std::chrono::high_resolution_clock::now();
        auto push_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_push - begin_push).count();

        auto start_poll = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < n; ++i) {
            int element;
            if (!queue_poll(queue, element)) {
                throw std::runtime_error("Poll failed");
            }
        }
        auto end_poll = std::chrono::high_resolution_clock::now();
        auto poll_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_poll - start_poll).count();

        data << n << " " << push_time << " " << poll_time << "\n";
    }
    queue_del(queue);
    return 0;
}