#include <iostream>
#include <chrono>
#include <thread>
/////
#include <mutex>
#include <atomic>
/////
#include <variant>

//////////////////////////////////////////////////////
// (1) BASIC EXAMPLE - ENUM AS A FIELD IN A CLASS
/*
    rocket.update(); at every tick
*/

enum class RocketState1{ PreLaunch, Launching /*...*/};

class Rocket1{
private:
    //const RocketConfig& config;
    RocketState1 state;
public:
    // constructor
    // Rocket1(const RocketConfig& cfg) : 
    //      rocketCfg(cfg),
    //      state(RocketState::PreLaunch) {};

    void update() {
        switch(state) {
            case RocketState1::PreLaunch:
            /* */
                state = RocketState1::Launching;
                break;
        }
    }
};

//////////////////////////////////////////////////////
// (2) THREADS THAT DRIVE STATE CHANGES 
//      AND THREAD THAT MONITORS THEM
/*
    // std::thread(std::pointer_to_member_function, pointer_to_object)

    std::thread t1(&RocketSystem::fuelThread, &rocket);
    std::thread t2(&RocketSystem::countdownThread, &rocket);
    std::thread t3(&RocketSystem::launchControllerThread, &rocket)

    t1.join();
    t2.join();
    t3.join();
*/
class RocketSystem{
private:
    std::atomic<bool>fuelReady;
    int countdown;
    std::mutex countdownMutex;

public:
    /*void fuelThread();*/
    void countdownThread();
    void launchControllerThread();
};

void RocketSystem::countdownThread() {
    while(true) {
        std::lock_guard<std::mutex> lock(countdownMutex);
        if(countdown > 0) {
            countdown--;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } else if (!fuelReady.load()) { // updated with fuelReady.store(true)
            countdown = 3;
        } else {
            break;
        }
    }
}

void RocketSystem::launchControllerThread() {
    while(true) {
        std::lock_guard<std::mutex> lock(countdownMutex);
        if(fuelReady.load() && countdown == 0) {
            break;
        }
        // check every 100 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

//////////////////////////////////////////////////////
// (3) VISIT ON TYPE-SAFE VARIANTS (NO CLASS)
/*
    RocketState state = Idle{};

    handleState(state); at every tick
*/

struct Idle{};
// struct Fueling{};
struct Countdown{int secondsLeft;};
struct Launched{};

using RocketState = std::variant<Idle, Countdown, Launched>;

void handleState(RocketState &state) {
    std::visit([&](auto && s) {
        // clean up (refs and consts) for type comparison
        using T = std::decay_t<decltype(s)>;
        
        if constexpr(std::is_same_v<T, Idle>) {
            state = Countdown{5};
        } else if constexpr(std::is_same_v<T, Countdown>) {
            if(s.secondsLeft > 0) {
                s.secondsLeft--; 
            } else {
                state = Launched{};
            }
        } /* else if other states... */
    }, state);
}

//////////////////////////////////////////////////////
// (4) ABSTRACT BASE CLASS + DERIVED CLASS 
//      + VIRTUAL + DYNAMIC DISPATCH
/* 
    Rocket4 rocket;
    rocket.runStep(); at every tick
*/
class Rocket4; // forward dec
class RocketState4{
public:
    virtual void handle(Rocket4 &rocket) = 0;
    virtual const char* name() const = 0;
    virtual ~RocketState4() = default;
};

class IdleState4 : public RocketState4{
public:
    void handle(Rocket4& rocket) override;
    const char* name() const override{ return "Idle"; }
};

class CountdownState4 : public RocketState4{
private:
    int countdown;

public:
    CountdownState4(int seconds) : countdown(seconds){};
    void handle(Rocket4& rocket) override;
    const char* name() const override{ return "Countdown"; };
};

// more states...

// encapsulate:
class Rocket4{
private:
    std::unique_ptr<RocketState4> state;
public:
    Rocket4(): state(std::make_unique<IdleState4>()) {};
    void runStep() {
        // polymorphism
        state->handle(*this);
    }
    void setState(std::unique_ptr<RocketState4> newState) {
        state = std::move(newState);
    }
};

// state behavior implementations
void IdleState4::handle(Rocket4 &rocket){
    rocket.setState(std::make_unique<CountdownState4>());
}

void CountdownState4::handle(Rocket4 &rocket){
    if(countdown > 0) {
        countdown--;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } else {
        // rocket.setState(std::make_unique<LaunchingState4>());
    }
}


