#pragma once
#include <vector>

#include "DoublePendulum.h"
#include "integrator.h"

std::vector<double> simulate(const DoublePendulum& pendulum, Integrator& integrator, double dt, int steps);