#include <iostream>
#include <variant>
#include <thread>
#include <chrono>

// separate structs for each rocket state
struct Idle{};
struct Fueling{};
struct Countdown{
    int secondsLeft;
};
struct Launching{};
struct Launched{};

// using is a type alias
// RocketState is a type alias for the variant representation that includes Idle, Fueling...
// variant is a type-safe way to represent a value
// that can hold one of several possible types
// (better alternative to unions, which can lead to accidental misinterpretations)
using RocketState = std::variant<Idle, Fueling, Countdown, Launching, Launched>;

void handleState(RocketState &state) {
    // std::visit allows us to apply a visitor
    // to the currently active variant alternative
    // it is type-safe and can access vars from
    // the outer scope with &
    //
    // takes two arguments:
    // (1) visitor: a lambda function
    //      - [&] is the capture clause
    //          means it can access vars from the
    //          surrounding scope by reference
    //      - (auto && s) is the parameter list
    //          auto make the lambda generic, meaning it can work with any type the variant might hold(e.g. int, std::string, etc.)          
    //          && is a forwarding reference, which allows the lambda to accept both lvalues (named objects) and rvalues (temporary objects)
    //          s is the value stored in the variant.
    //
    // (2) variant: specifies with variant to visit
    std::visit([&](auto && s) {
        // decltype(s) gets the type of the currently held variant
        // decay_t removes references and constness for clean type comparison
        using T = std::decay_t<decltype(s)>;

        // constexpr is a compile-time conditional
        // but lets us check the type at compile-time
        // avoids runtime overhead
        if constexpr(std::is_same_v<T, Idle>) {
            std::cout << "idle" << std::endl;
            state = Fueling{};
            
            // see, you can leave out constexpr
        } else if (std::is_same_v<T, Fueling>) {
            std::cout << "fueling" << std::endl;
            state = Countdown{5};

        } else if constexpr(std::is_same_v<T, Countdown>) {
            if(s.secondsLeft > 0) {
                std::cout << "T-minus: " << s.secondsLeft << std::endl;
                s.secondsLeft--; 
            } else {
                state = Launching{};
            }

        } else if constexpr(std::is_same_v<T, Launching>) {
            std::cout << "liftoff" << std::endl;
            state = Launched{};

        } else if constexpr(std::is_same_v<T, Launched>) {
            std::cout << "LAUNCHED" << std::endl;
        }
    }, state);
}

int main() {
    RocketState state = Idle{};

    for(int i = 0; i < 10; ++i) {
        handleState(state);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}