#pragma once

#include "integrator.h"

class RK4Integrator : public Integrator {
public:

    State step(const DoublePendulum &pendulum, const State &state, double dt) override;
};