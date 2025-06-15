#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

// OOP concepts
//  (1) abstraction
//      - class RocketState with pure virtual functions
//  (2) inheritance
//      - class IdleState : public RocketState
//  (3) polymorphism
//      - virtual void handle(Rocket&)
//  (4) dynamic dispatch
//      - currentState->handle(*this)
//  (5) encapsulation
//      - Rocket manages state transitions


// forward declaration of Rocket class
// allows to refer to Rocket in the state class declarations below.
class Rocket;

// abstract base class
// 
class RocketState{
public:
    // virtual func defines behavior for each
    // step in a state's lifecycle
    // derived classes MUST implement this
    virtual void handle(Rocket &rocket) = 0;

    // second virtual function just for printing
    // the name of the state
    virtual const char* name() const = 0;

    // always give base classes virtual
    // destructors to ensure proper cleanup
    // through base class pointers
    virtual ~RocketState() = default;
};

// derived state classes
//
class IdleState : public RocketState {
public:
    // the override keyword tells the compiler:
    // "This function is intended to override a 
    // virtual function in a base class. 
    // Please check that it actually does."
    // e.g. you can remove "Rocket& rocket"
    // and see this is a compiler error

    // implementation of this is deferred below
    void handle(Rocket& rocket) override;

    // return name of this state
    // const marks the method as read-only
    // (does not modify the object)
    const char* name() const override{ return "Idle"; }
};

class FuelingState : public RocketState {
public:
    void handle(Rocket& rocket) override;
    const char* name() const override{ return "Fueling"; }
};

class CountdownState : public RocketState {
private:
    int countdown;

public:
    CountdownState(int seconds) : countdown(seconds){};

    void handle(Rocket& rocket) override;
    const char* name() const override{ return "Countdown"; };
};

class LaunchingState : public RocketState {
public:
    void handle(Rocket& rocket) override;
    const char* name() const override{ return "Launching"; };
};

class LaunchedState : public RocketState{
public:
    void handle(Rocket& rocket) override;
    const char* name() const override{ return "Launched"; };
};

// main Rocket class
class Rocket{
private:
    // this will give you "object of abstract class type
    // "RocketState" is not allowed"
    //RocketState state;

    // you need this
    // means it is owned exclusively by the Rocket class
    // it is basically a better `new` and showcases smart pointers
    std::unique_ptr<RocketState> state;

public:
    // Rocket() : state(IdleState) {}; is not allowed
    // because IdleState is a type name
    // make_unique is the alternative to `new`
    Rocket() : state(std::make_unique<IdleState>()) {};

    void runStep() {
        std::cout << "[rocket] current state: " << state->name() << std::endl;

        // delegate the behavior to the current state
        // polymorphism ensure correct handle() is called.
        state->handle(*this);
    }

    void setState(std::unique_ptr<RocketState> newState) {
        // transfer ownership of new state
        state = std::move(newState);
    }
};

// state behavior implementations
void IdleState::handle(Rocket &rocket){
    rocket.setState(std::make_unique<FuelingState>());
}

void FuelingState::handle(Rocket &rocket){
    rocket.setState(std::make_unique<CountdownState>(5));
}

void CountdownState::handle(Rocket &rocket){
    if(countdown > 0) {
        std::cout << "T-minus: " << countdown << std::endl;
        countdown--;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } else {
        rocket.setState(std::make_unique<LaunchingState>());
    }
}

void LaunchingState::handle(Rocket &rocket){
    rocket.setState(std::make_unique<LaunchedState>());
}

void LaunchedState::handle(Rocket &){
    // no state change
}

int main() {
    Rocket rocket;

    for(int i = 0; i < 10; ++i) {
        rocket.runStep();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}