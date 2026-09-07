#include "../include/simulation.h"

std::vector<double> simulate(const DoublePendulum &pendulum, Integrator &integrator, double dt, int steps) {
    State state = pendulum.state;
    std::vector<double> energyHistory;
    
    double initialEnergy = pendulum.energy(state);
    energyHistory.push_back(initialEnergy);

    for (int i = 0; i < steps; i++) {
        state = integrator.step(pendulum, state, dt);

        double currentEnergy = pendulum.energy(state);
        energyHistory.push_back(currentEnergy);

    }
    return energyHistory;
}
