#pragma once
#include <vector>
#include "DoublePendulum.h"

double maxEnergyError(const std::vector<double>& energyHistory);
double divergence(const State& a, const State& b);
