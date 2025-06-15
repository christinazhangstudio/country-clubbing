#include <iostream>
#include <chrono>
#include <thread>

enum class RocketState {
    PreLaunch,
    Launch,
    InOrbit,
};

struct RocketConfig {
    int countdownTicks;
    int launchTimeTicks; // before officially being in orbit

    RocketConfig(int ct, int lt): countdownTicks{ct}, launchTimeTicks{lt} {};
};

class Rocket {
    private:
        // doesn't have to be a pointer... 
        //just for fun, can be const reference 
        // (which we'd access fields with . and not ->)  
        // it would be better as a reference, since pointer
        // can be null, and would be best used if cfg were optional (it's not) 
        // however passing by value will not allow the field to be updated
        // like pointer/reference 
        // this would actually even not be a separate struct
        // but just fields on this class.
        RocketConfig* rocketCfg; 
        RocketState state;

    public:
        Rocket(RocketConfig *cfg) : 
            rocketCfg(cfg),
            state(RocketState::PreLaunch)
            {};
        
        void update() {
            switch(state) {
                case RocketState::PreLaunch:
                    std::cout << "prelaunch: T-" << rocketCfg->countdownTicks << std::endl;
                    rocketCfg->countdownTicks--;

                    // simulate 1 sec delay
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    
                    if(rocketCfg->countdownTicks <= 0) {
                        std::cout << "LAUNCHING" << std::endl;
                        state = RocketState::Launch;
                    }
                    
                    break;
                case RocketState::Launch:
                    std::cout << "to orbit: T-" << rocketCfg->launchTimeTicks << std::endl;
                    
                    rocketCfg->launchTimeTicks--;

                    // simulate 1 sec delay
                    std::this_thread::sleep_for(std::chrono::seconds(1));

                    if(rocketCfg->launchTimeTicks <= 0) {
                        std::cout << "IN ORBIT" << std::endl;
                        state = RocketState::InOrbit;
                    }
                    
                    break;
                case RocketState::InOrbit:
                    std::cout << "staying in orbit..." << std::endl;

                    break;
            }
        }
};

int main() {
    // the new constructor RETURNS pointer
    RocketConfig* cfg = new RocketConfig(5, 3);

    // probably better off as RocketConfig cfg;... cfg.countdownTimer = 5;...
    Rocket rocket(cfg);

    for(int i = 0; i < 10; i++) {
        rocket.update();
    }
}