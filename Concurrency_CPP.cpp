#include <iostream>
#include <thread>
#include <mutex>

// Global variables
int counter1 = 0;
int counter2 = 20;
std::mutex mutex;

// Function for the first thread to count up to 20
void countUp() {
    for (int i = 1; i <= 20; ++i) {
        {
            std::lock_guard<std::mutex> lock (mutex);
            counter1 = i;
            std::cout << "Counter 1: " << counter1 << std::endl;

        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulating work
    }
}

// Function for the second thread to count down to 0
void countDown() {
    for (int i = 20; i >= 0; --i) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            counter2 = i;
            std::cout << "Counter 2: " << counter2 << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulating work
    }
}

int main() {
    std::thread t1(countUp);
    t1.join(); // Wait for the first thread to finish before starting second

    std::thread t2(countDown);
    t2.join();

    return 0;
}