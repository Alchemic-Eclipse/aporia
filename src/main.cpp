#include <iostream>
#include "../include/DoublePendulum.h"
#include "../include/EulerIntegrator.h"
#include "../include/renderer.h"
#include "../include/RK4Integrator.h"
#include "../include/simulation.h"
#include "../include/analysis.h"
#include <raylib.h>

int main() {
    DoublePendulum pendulumA;
    DoublePendulum pendulumB;

    pendulumA.parameters={2.0, 1.5, 80.0, 80.0, 9.8};
    pendulumB.parameters = pendulumA.parameters;

    pendulumA.state = {3.14, 0.5, 2.0, 4.0};
    pendulumB.state = {3.14, 0.500001, 2.0, 4.0};

    State initialStateA = pendulumA.state;
    State initialStateB = pendulumB.state;

    double dt = 0.015;
    double time = 0.0;

    // EulerIntegrator integrator;
    RK4Integrator integrator;


    // Visual Rendering
    initializeRenderer();

    bool paused = false;

    while(!WindowShouldClose()) {

        if (IsKeyPressed(KEY_SPACE)) {
            paused = !paused;
        }

        if (!paused) {
            pendulumA.state = integrator.step(pendulumA, pendulumA.state, dt);
            pendulumB.state = integrator.step(pendulumB, pendulumB.state, dt);
            time += dt;
        }

        if (IsKeyPressed(KEY_N) && paused) {
            pendulumA.state = integrator.step(pendulumA, pendulumA.state, dt);
            pendulumB.state = integrator.step(pendulumB, pendulumB.state, dt);
            time += dt;
        }

        if (IsKeyPressed(KEY_R)) {
            pendulumA.state = initialStateA;
            pendulumB.state = initialStateB;
            time = 0.0;
        }

        renderFrame(pendulumA, pendulumB, time, divergence(pendulumA.state, pendulumB.state));
        // std::cout << divergence(pendulumA.state, pendulumB.state) << std::endl;
    }   

    closeRenderer();
}