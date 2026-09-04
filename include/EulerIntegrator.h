#pragma once
#include "DoublePendulum.h"
#include "integrator.h"

// State step(const DoublePendulum& pendulum, const State& state, double dt);

class EulerIntegrator : public Integrator {
public:
    State step(const DoublePendulum& pendulum, const State& state, double dt) override;
};