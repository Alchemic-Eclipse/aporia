#include "../include/analysis.h"
#include <cmath>


double maxEnergyError(const std::vector<double> &energyHistory) {
    double E0 = energyHistory[0];
    double maxError = 0;

    for (double E : energyHistory) {
            double relativeError = std::abs((E - E0)/E0) * 100;

            if (relativeError > maxError) {
                maxError = relativeError;
            }
    }
    return maxError;
}


double divergence(const State &a, const State &b) {
    double d1 = (a.theta1 - b.theta1) * (a.theta1 - b.theta1);
    double d2 = (a.theta2 - b.theta2) * (a.theta2 - b.theta2);
    double d3 = (a.omega1 - b.omega1) * (a.omega1 - b.omega1);
    double d4 = (a.omega2 - b.omega2) * (a.omega2 - b.omega2);
    return std::sqrt(d1 + d2 + d3 + d4);
}
