#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>

class RocketSystem{
private:
    std::atomic<bool>fuelReady;
    // NOT atomic because compound updates 
    // (e.g. read then write as 1 operation) 
    // rather than a simple read
    int countdown;  
    std::mutex countdownMutex;

    std::atomic<bool> launched;

public:
    RocketSystem(): fuelReady(false), countdown(5), launched(false) {};
    
    void fuelThread();
    
    void countdownThread();

    // drives the state transitions based on updates 
    // to vars from the other threads
    void launchControllerThread(); 
};

void RocketSystem::fuelThread() {
    std::cout << "fueling..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(6));
    std::cout << "done fueling!" << std::endl;
    fuelReady.store(true);
}

void RocketSystem::countdownThread() {
    while(true) {
        std::lock_guard<std::mutex> lock(countdownMutex);

        if(countdown > 0) {
            std::cout << "T-minus: " << countdown << std::endl;
            countdown--;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } else if (!fuelReady.load()) {
            std::cout << "fuel systems not ready!! delaying countdown..." << std::endl;
            countdown = 3;
        } else {
            std::cout << "signal to launch..." << std::endl;
            break;
        }
    }
}

void RocketSystem::launchControllerThread() {
    while(true) {
        std::lock_guard<std::mutex> lock(countdownMutex);
        if(fuelReady.load() && countdown == 0) {
            std::cout << "LAUNCHING" << std::endl;
            launched.store(true);
            break;
        }

        // check every 100 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    RocketSystem rocket;

    // std::thread(std::function_pointer_to_member_function, pointer_to_object, args...)

    // &RocketSystem::fuelThread is a pointer to the
    // member function
    // &rocket is the pointer to the instance that the
    // member function should be called on.
    // "Start a thread that will call rocket.fuelThread()."
    std::thread t1(&RocketSystem::fuelThread, &rocket);
    std::thread t2(&RocketSystem::countdownThread, &rocket);
    std::thread t3(&RocketSystem::launchControllerThread, &rocket);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}