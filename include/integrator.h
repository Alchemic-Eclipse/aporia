#pragma once

#include "DoublePendulum.h"

class Integrator {
public:
    virtual State step(const DoublePendulum& pendulum, const State& state, double dt) = 0;
    virtual ~Integrator() = default;
};