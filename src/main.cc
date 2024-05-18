#include <chrono>
#include <thread>
#include <cstdlib>
#include <iostream>

#define DELAY 10
#define SIZE 8L * 1024 * 1024 * 1024

volatile char var = 'a';

// tested on Ubuntu VM (oracle) seems like it does not load
void read_array(char* array, size_t len) {
    int steps = len / 1024;
    for (long i = 0; i<steps; i++) {
        var = array[i * 1024];
        if (i%1024 == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
        }
    }
}

// successfully load memory
void write_array(char* array, size_t len) {
    int steps = len / 1024;
    for (long i = 0; i<steps; i++) {
        array[i * 1024] = 'a';
        if (i%1024 == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
        }
    }
}

int main() {
    char* arr = new char[SIZE];
    // read_array(arr, SIZE);
    write_array(arr, SIZE);
    return 0;
}
