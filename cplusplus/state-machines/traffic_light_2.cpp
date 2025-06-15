// - multiple traffic lights
// - pedestrain signal
// - event drive input (e.g. pedestrian button press)
// - state transition logging
// - customizable state durations via configuration struct

// model crossroad with
//  - north-south direction
//  - east-west direction
//  - pedestrian signal

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

enum class LightState {
    Red,
    Green,
    Yellow
};

enum class PedestrianState {
    Walk,
    DontWalk,
};

struct TrafficConfig {
    int redDuration = 30;
    int greenDuration = 30;
    int yellowDuration = 5;
    int walkDuration = 10;
};

class TrafficLight {
private:
    std::string name;
    LightState currentState;
    int stateTimer;
    const TrafficConfig& config;
    std::ofstream& logFile;

public:
    TrafficLight(
        const std::string& directionName, 
        LightState initialState, 
        const TrafficConfig& cfg,
        std::ofstream& log
    ) : 
        name(directionName),
        currentState(initialState),
        stateTimer(0),
        config(cfg),
        logFile(log) {logStateChange();}

    // event driven based on if "allowWalk" was triggered as well
    bool update(bool allowWalk) {
        stateTimer++;
        bool transitioned = false;

        switch(currentState) {
            case LightState::Red:
                if(stateTimer >= config.redDuration && allowWalk) {
                    currentState = LightState::Green;
                    stateTimer = 0;
                    transitioned = true;
                    logStateChange();
                }
                break;

            case LightState::Green:
                if(stateTimer >= config.greenDuration && allowWalk) {
                    currentState = LightState::Yellow;
                    stateTimer = 0;
                    transitioned = true;
                    logStateChange(); 
                }
                break;
            
            case LightState::Yellow:
                if(stateTimer >= config.yellowDuration && allowWalk) {
                    currentState = LightState::Red;
                    stateTimer = 0;
                    transitioned = true;
                    logStateChange();
                }
                break;
        }

        return transitioned;
    }

    LightState getState() const { return currentState; }

    std::string getStateString() const {
        switch(currentState) {
            case LightState::Red: return "RED";
            case LightState::Yellow: return "YELLOW";
            case LightState::Green: return "GREEN";
            default: return "UNKNOWN";
        }
    }

private:
    void logStateChange() {
        logFile << name << " changed to " << getStateString() << " at time " << stateTimer << "\n";
    }
};

class PedestrianSignal{
private:
    PedestrianState currentState;
    int stateTimer;
    bool walkRequested;
    const TrafficConfig& config;
    std::ofstream& logFile;

public:
    PedestrianSignal(
        const TrafficConfig &cfg,
        std::ofstream& log
    ) : currentState(PedestrianState::DontWalk), 
        stateTimer(0),
        walkRequested(false),
        config(cfg), 
        logFile(log) {logStateChange();}

    // event-driving walk signal that changes PedestrianState
    void requestWalk() {
        walkRequested = true;
    }

    void update(bool canWalk) {
        stateTimer++;

        if(currentState == PedestrianState::DontWalk && canWalk && walkRequested) {
            currentState = PedestrianState::Walk;
            stateTimer = 0;
            walkRequested = false;
            logStateChange();
        } else if(currentState == PedestrianState::Walk && stateTimer >= config.walkDuration) {
            currentState = PedestrianState::DontWalk;
            stateTimer = 0;
            logStateChange();
        }
    }

    std::string getStateString() {
        switch(currentState) {
            case PedestrianState::DontWalk: return "DON'T WALK";
            case PedestrianState::Walk: return "WALK";
            default: return "UKNOWN";
        }
    }

private:
    void logStateChange() {
        logFile << "pedestrian signal changed to " << getStateString() << " at time " << stateTimer << "\n";
    }
};

class Crossroad {
private:
    TrafficLight nsLight; // north south light
    TrafficLight ewLight; // east west light
    PedestrianSignal pedSignal;
    std::vector<int> pedestrianButtonPresses;   // simulated button presses at specific time steps
    std::ofstream &logFile;

public:
    Crossroad(const TrafficConfig& cfg, std::ofstream& log
    ) : nsLight("North-South", LightState::Red, cfg, log),
    ewLight("East-West", LightState::Green, cfg, log),
    pedSignal(cfg, log), 
    logFile(log) {
        pedestrianButtonPresses = {20, 80};
    }

    void update(int timeStep) {
        // == UPDATE THE TRAFFIC LIGHTS AT EACH STEP (so long as the pedestrian signal is not "WALK") ==
        bool nsTransitioned = nsLight.update(pedSignal.getStateString() == "DON'T WALK");
        bool ewTransitioned = ewLight.update(pedSignal.getStateString() == "DON'T WALK");


        // === TAKE CARE OF PEDESTRIANS ===

        // check for pedestrian button press
        auto iter = std::find(pedestrianButtonPresses.begin(), pedestrianButtonPresses.end(), timeStep);
        if (iter != pedestrianButtonPresses.end()) {
            // found the element in the iterator
            pedSignal.requestWalk();
        }

        // update pedestrian signal only when lights are Red
        bool canWalk = (nsLight.getState() == LightState::Red && ewLight.getState() == LightState::Red);
        pedSignal.update(canWalk);

        // print current state
        logFile << "\ntime step " << timeStep << ": \n"
                << "NS = " << nsLight.getStateString() << "\n"
                << "EW = " << ewLight.getStateString() << "\n"
                << "Ped = " << pedSignal.getStateString() << "\n\n";
    }
};

int main() {
    std::ofstream logFile("traffic_log.txt");
    if(!logFile.is_open()) {
        std::cerr << "failed to open file\n";
        return 1;
    } 

    TrafficConfig config;
    config.redDuration = 30;
    config.greenDuration = 20;
    config.yellowDuration = 5;
    config.walkDuration = 10;

    Crossroad crossroad(config, logFile);
    for(int i = 0; i <= 150; ++i) {
        crossroad.update(i);
    }

    logFile.close();
    return 0;
}