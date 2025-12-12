#include<iostream>
#include <fstream>
#include <chrono>
#include <string>

struct array1
{
public:
    int* arr = nullptr;
    int size = 0;

    void push_back(int elem) {
        arr = (int*)std::realloc(arr, (++size) * sizeof(int));
        arr[size - 1] = elem;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
    }

    void clean() {
        std::free(arr);
    }
};

struct array2 {
public:
    int* arr = nullptr;
    int size = 0;
    int max_size = 0;

    array2(int max_size) {
        size = 0;
        arr = nullptr;
        arr = (int*)std::realloc(arr, max_size * sizeof(int));
        this->max_size = max_size;
    }

    void push_back(int elem) {
        if (size == max_size) {
            arr = (int*)std::realloc(arr, 2*max_size * sizeof(int));
            max_size = 2 * max_size;
        }
        arr[size++] = elem;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
    }

    void clean() {
        std::free(arr);
    }
};


struct array3 {
public:
    int* arr = nullptr;
    int size = 0;
    int max_size = 0;

    void push_back(int elem) {
        if (size < max_size) {
            arr[size++] = elem;
        }
        else if (size == 0) {
            arr = (int*)std::realloc(arr, sizeof(int));
            arr[size++] = elem;
            max_size = size;
        }
        else {
            max_size = size * 2;
            arr = (int*)std::realloc(arr, (max_size) * sizeof(int));
            arr[size++] = elem;
        }
    }
    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
    }

    void clean() {
        std::free(arr);
    }
};

struct queue {
    std::size_t poll_idx = 0;
    std::size_t push_idx = 0;
    int* data = new int;
    std::size_t size = 0;
    std::size_t max_size = 1;

    queue() {}

    queue(int size) {
        this->size = size;
        max_size = size;
        data = (int*)std::realloc(data, (max_size) * sizeof(int));
        push_idx = 0;
        poll_idx = max_size - 1;
        for (int i = 0; i < size; i++) {
            data[i] = i;
        }
    }

    std::pair<bool, int> poll() {
        if (size == 0) {
            return { false, 0 };
        }
        int elem = data[poll_idx];
        size--;
        if (poll_idx == push_idx) {
            ;
        }
        else if (poll_idx == 0) {
            poll_idx = max_size - 1;
        }
        else {
            poll_idx--;
        }
        return { true, elem };
    }

    void push(int elem) {
        if (size == 0) {
            data[push_idx] = elem;
            size++;
            return;
        }
        if (size == max_size) {
            // int cnt = 0;
            // std::cout << ++cnt << std::endl;
            data = (int*)std::realloc(data, (2 * max_size) * sizeof(int));
            // std::cout << ++cnt << std::endl;
            std::size_t idx = 2 * max_size - 1;
            // std::cout << poll_idx << ' ' << push_idx;


            if (poll_idx >= push_idx) {
                for (std::size_t i = poll_idx; i >= push_idx; i--, idx--) {
                    data[idx] = data[i];
                    // std::cout << idx <<' ' << i << std::endl;
                    if (i == 0) {
                        idx--;
                        break;
                    }
                    // std::cout << ++cnt << " 1" << std::endl;
                }
            }
            else {
                for (std::size_t i = poll_idx; i >= 0; i--, idx--) {
                    data[idx] = data[i];
                    // std::cout << idx <<' ' << i << std::endl;
                    if (i == 0) {
                        idx--;
                        break;
                    }
                    // std::cout << ++cnt << " 1" << std::endl;
                }
                // std::cout << "focus";
                for (std::size_t i = max_size - 1; i >= push_idx; i--, idx--) {
                    data[idx] = data[i];
                    // std::cout << idx << ' ' << i << std::endl;
                    // std::cout << ++cnt << " 1" << std::endl;
                    if (i == push_idx) {
                        idx--;
                        break;
                    }
                }
            }

            push_idx = max_size;
            poll_idx = 2 * max_size - 1;
            max_size *= 2;
            // std::cout << ++cnt << std::endl;
        }

        if (push_idx == 0) {
            push_idx = max_size - 1;
            data[push_idx] = elem;
            size++;
        }
        else {
            data[--push_idx] = elem;
            size++;
        }
    }

    void del() {
        std::free(data);
    }



    void print() {
        if (size != 0) {
            if (poll_idx >= push_idx) {
                for (std::size_t i = push_idx; i <= poll_idx; ++i) {
                    std::cout << data[i] << ' ';
                }
            }
            else {
                for (std::size_t i = push_idx; i < max_size; ++i) {
                    std::cout << data[i] << ' ';
                }
                std::cout << ": ";
                for (std::size_t i = 0; i <= poll_idx; ++i) {
                    std::cout << data[i] << ' ';
                }
            }

        }

        std::cout << std::endl << "size = " << size << " maxsize = " << max_size << std::endl;
        std::cout << "poll_idx = " << poll_idx << " push_idx = " << push_idx << std::endl;
    }

};

struct deque {
    std::size_t poll_idx = 0;
    std::size_t push_idx = 0;
    void* data = nullptr;
    std::size_t size = 0;
    std::size_t max_size = 1;
    std::size_t element_size;

    deque(std::size_t element_size) {
        this->element_size = element_size;
        data = malloc(element_size);
    }

    std::pair<bool, void*> poll_back() {
        if (size == 0) {
            return { false, nullptr };
        }
        void* elem = std::malloc(element_size);
        elem = data+poll_idx*element_size;
        size--;
        if (poll_idx == push_idx) {
            ;
        }
        else if (poll_idx == 0) {
            poll_idx = max_size - 1;
        }
        else {
            poll_idx--;
        }
        return { true, elem };
    }

    std::pair<bool, void*> poll_front() {
        if (size == 0) {
            return { false, 0 };
        }
        int elem = data[push_idx];
        size--;
        if (poll_idx == push_idx) {
            ;
        }
        else if (push_idx == max_size-1) {
            push_idx = 0;
        }
        else {
            push_idx++;
        }
        return { true, elem };
    }


    void push_front(int elem) {
        if (size == 0) {
            data[push_idx] = elem;
            size++;
            return;
        }
        if (size == max_size) {
            // int cnt = 0;
            // std::cout << ++cnt << std::endl;
            data = (int*)std::realloc(data, (2 * max_size) * sizeof(int));
            // std::cout << ++cnt << std::endl;
            std::size_t idx = 2 * max_size - 1;
            // std::cout << poll_idx << ' ' << push_idx;

            if (poll_idx >= push_idx) {
                for (std::size_t i = poll_idx; i >= push_idx; i--, idx--) {
                    data[idx] = data[i];
                    // std::cout << idx <<' ' << i << std::endl;
                    if (i == 0) {
                        idx--;
                        break;
                    }
                    // std::cout << ++cnt << " 1" << std::endl;
                }
            }
            else {
                for (std::size_t i = poll_idx; i >= 0; i--, idx--) {
                    data[idx] = data[i];
                    // std::cout << idx <<' ' << i << std::endl;
                    if (i == 0) {
                        break;
                    }
                    // std::cout << ++cnt << " 1" << std::endl;
                }
                // std::cout << "focus";
                for (std::size_t i = max_size - 1; i >= push_idx; i--, idx--) {
                    data[idx] = data[i];
                    // std::cout << idx << ' ' << i << std::endl;
                    // std::cout << ++cnt << " 1" << std::endl;
                    if (i == push_idx) {
                        idx--;
                        break;
                    }
                }
            }

            push_idx = max_size;
            poll_idx = 2 * max_size - 1;
            max_size *= 2;
            // std::cout << ++cnt << std::endl;
        }

        if (push_idx == 0) {
            push_idx = max_size - 1;
            data[push_idx] = elem;
            size++;
        }
        else {
            data[--push_idx] = elem;
            size++;
        }
    }

    void push_back(int elem) {
        if (size == 0) {
            data[poll_idx] = elem;
            size++;
            return;
        }
        if (size == max_size) {
            // int cnt = 0;
            // std::cout << ++cnt << std::endl;
            data = (int*)std::realloc(data, (2 * max_size) * sizeof(int));
            // std::cout << ++cnt << std::endl;
            std::size_t idx = 2 * max_size - 1;
            // std::cout << poll_idx << ' ' << push_idx;

            if (poll_idx >= push_idx) {
                for (std::size_t i = poll_idx; i >= push_idx; i--, idx--) {
                    data[idx] = data[i];
                    // std::cout << idx <<' ' << i << std::endl;
                    if (i == 0) {
                        break;
                    }
                    // std::cout << ++cnt << " 1" << std::endl;
                }
            }
            else {
                for (std::size_t i = poll_idx; i >= 0; i--, idx--) {
                    data[idx] = data[i];
                    // std::cout << idx <<' ' << i << std::endl;
                    if (i == 0) {
                        idx--;
                        break;
                    }
                    // std::cout << ++cnt << " 1" << std::endl;
                }
                // std::cout << "focus";
                for (std::size_t i = max_size - 1; i >= push_idx; i--, idx--) {
                    data[idx] = data[i];
                    // std::cout << idx << ' ' << i << std::endl;
                    // std::cout << ++cnt << " 1" << std::endl;
                    if (i == push_idx) {
                        idx--;
                        break;
                    }
                }
            }

            push_idx = max_size;
            poll_idx = 2 * max_size - 1;
            max_size *= 2;
            // std::cout << ++cnt << std::endl;
        }


        if (poll_idx == max_size -1) {
            poll_idx = 0;
            data[poll_idx] = elem;
            size++;
        }
        else {
            data[++poll_idx] = elem;
            size++;
        }
    }

    void del() {
        delete data;
    }



    void print() {
        if (size != 0) {
            if (poll_idx >= push_idx) {
                for (std::size_t i = push_idx; i <= poll_idx; ++i) {
                    std::cout << data[i] << ' ';
                }
            }
            else {
                for (std::size_t i = push_idx; i < max_size; ++i) {
                    std::cout << data[i] << ' ';
                }
                std::cout << ": ";
                for (std::size_t i = 0; i <= poll_idx; ++i) {
                    std::cout << data[i] << ' ';
                }
            }

        }

        std::cout << std::endl << "size = " << size << " maxsize = " << max_size << std::endl;
        std::cout << "poll_idx = " << poll_idx << " push_idx = " << push_idx << std::endl;
    }

};


void test_queue() {
    queue* q = new queue();
    q->print();
    while (true) {
        char elem;
        std::cin >> elem;
        if (elem == 'a') {
            int key;
            std::cin >> key;
            q->push(key);
            q->print();
        }
        else if (elem == 'd') {
            auto p = q->poll();
            std::cout << "Return " << p.first << ' ' << p.second << std::endl;;
            q->print();
        }
    }
}

void test_deque() {
    deque* q = new deque();
    q->print();
    while (true) {
        std::string elem;
        std::cin >> elem;
        if (elem == "af") {
            int key;
            std::cin >> key;
            q->push_front(key);
            q->print();
        }
        else if (elem == "db") {
            auto p = q->poll_back();
            std::cout << "Return " << p.first << ' ' << p.second << std::endl;;
            q->print();
        }
        else if (elem == "ab") {
            int key;
            std::cin >> key;
            q->push_back(key);
            q->print();
        }
        else if (elem == "df") {
            auto p = q->poll_front();
            std::wcout << "Retrun " << p.first << ' ' << p.second << std::endl;
            q->print();
        }
    }
}

void count_time_array1() {
    std::ofstream out;
    out.open("array1.txt");


    if (out.is_open()) {
        for (int n = 10; n < 20000; n += 250) {
            auto begin = std::chrono::steady_clock::now();
            const int MAX_ITER = 1000;
            for (int iter = 0; iter < MAX_ITER; iter++) {
                array1* arr = new array1;
                for (int i = 0; i < n; ++i) {
                    arr->push_back(i);
                }
                arr->clean();
                delete arr;
            }
            auto end = std::chrono::steady_clock::now();
            auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            out << n << ' ' << time_span.count() << std::endl;
        }
    }
    out.close();

    std::cout << "end" << std::endl;
}

void count_time_array2() {
    std::ofstream out;
    out.open("array2.txt");


    if (out.is_open()) {
        for (int n = 10; n < 10000; n += 500) {
            auto begin = std::chrono::steady_clock::now();
            const int MAX_ITER = 1000;
            for (int iter = 0; iter < MAX_ITER; iter++) {
                array2* arr = new array2(1000);
                for (int i = 0; i < n; ++i) {
                    arr->push_back(i);
                }
                arr->clean();
                delete arr;
            }
            auto end = std::chrono::steady_clock::now();
            auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            out << n << ' ' << time_span.count() << std::endl;
        }
    }
    out.close();

    std::cout << "end" << std::endl;
}


void count_time_array3() {
    std::ofstream out;
    out.open("array3.txt");


    if (out.is_open()) {
        for (int n = 10; n < 10000; n += 500) {
            auto begin = std::chrono::steady_clock::now();
            const int MAX_ITER = 1000;
            for (int iter = 0; iter < MAX_ITER; iter++) {
                array3* arr = new array3;
                for (int i = 0; i < n; ++i) {
                    arr->push_back(i);
                }
                arr->clean();
                delete arr;
            }
            auto end = std::chrono::steady_clock::now();
            auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            out << n << ' ' << time_span.count() << std::endl;
        }
    }
    out.close();

    std::cout << "end" << std::endl;
}

void count_time_queue_push() {
    std::ofstream out1;
    out1.open("queue_push.txt");


    if (out1.is_open()) {
        for (int n = 10; n < 10000; n += 500) {
            auto begin = std::chrono::steady_clock::now();
            const int MAX_ITER = 1000;
            for (int i = 0; i < MAX_ITER; i++){
                queue* q = new queue();
                for (int i = 0; i < n; i++) {
                    q->push(i);
                }
                q->del();
                delete q;
            }
            
            auto end = std::chrono::steady_clock::now();
            auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            out1 << n << ' ' << time_span.count() << std::endl;
        }
    }
    out1.close();

    std::cout << "end" << std::endl;
}

void count_time_queue_poll() {
    std::ofstream out1;
    out1.open("queue_poll.txt");


    if (out1.is_open()) {
        for (int n = 10; n < 10000; n += 500) {
            auto begin = std::chrono::steady_clock::now();
            const int MAX_ITER = 1000;
            for (int i = 0; i < MAX_ITER; i++) {
                queue* q = new queue(n);
                for (int i = 0; i < n; i++) {
                    q->poll();
                }
                q->del();
                delete q;
            }

            auto end = std::chrono::steady_clock::now();
            auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            out1 << n << ' ' << time_span.count() << std::endl;
        }
    }
    out1.close();

    std::cout << "end" << std::endl;
}

int main() {
    test_deque();
    return 0;
}
