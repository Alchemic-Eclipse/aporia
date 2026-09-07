#include "../include/analysis.h"



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
