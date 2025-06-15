#include <iostream>
#include <string>

enum class LightState {
    Red,
    Green,
    Yellow
};

class TrafficLight {
private:
    LightState currentState;
    int stateTimer;

public:
    TrafficLight() : currentState(LightState::Red), stateTimer(0) {}

    void update() {
        stateTimer++;

        switch (currentState) {
            case LightState::Red:
                std::cout << "light is red\n";
                if (stateTimer >= 30) {     // red is 30 "seconds"
                    currentState = LightState::Green;
                    stateTimer = 0;         // reset timer
                }
                break;
            
            case LightState::Green:
                std::cout << "light is green\n";
                if(stateTimer >= 30) {
                    currentState = LightState::Yellow;
                    stateTimer = 0;
                }
                break;

            case LightState::Yellow:
                std::cout << "light is yellow\n";
                if(stateTimer >= 5) {
                    currentState = LightState::Red;
                    stateTimer = 0;
                }
                break;
        }
    }
};

int main() {
    TrafficLight light;

    // simulate 100 time steps
    for(int i = 0; i < 100; ++i) {
        std::cout << "time step" << i + 1 << ": ";
        light.update();
    }

    return 0;
}