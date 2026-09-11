#include <iostream>
#include "../include/DoublePendulum.h"
#include "../include/EulerIntegrator.h"
#include "../include/renderer.h"
#include "../include/RK4Integrator.h"
#include "../include/simulation.h"
#include "../include/analysis.h"
#include "../include/ExperimentSettings.h"
#include <raylib.h>


enum class Screen {
    HOME,
    EXPERIMENT,
    SIMULATION
};


int main() {

    Screen currentScreen = Screen::HOME;

    ExperimentSettings settings;

    DoublePendulum pendulumA;
    DoublePendulum pendulumB;

    pendulumA.parameters={
        settings.m1,
        settings.m2,
        settings.l1,
        settings.l2,
        settings.g
    };

    pendulumB.parameters = pendulumA.parameters;

    pendulumA.state = {
        settings.theta1, //
        settings.theta2A, //
        settings.omega1,
        settings.omega2
    };

    pendulumB.state = {
        settings.theta1,
        settings.theta2B, //
        settings.omega1,
        settings.omega2
    };

    State initialStateA = pendulumA.state;
    State initialStateB = pendulumB.state;

    double dt = settings.dt;
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

        if (currentScreen == Screen::HOME) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mouse = GetMousePosition();

                if (CheckCollisionPointRec(mouse, {500,350,200,60})) {
                    currentScreen = Screen::EXPERIMENT;
                }
            }

            renderHomeScreen();
        }

        else if (currentScreen == Screen::EXPERIMENT) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mouse = GetMousePosition();

                if (CheckCollisionPointRec(mouse, {740, 500, 300, 65})) {
                    currentScreen = Screen::SIMULATION;
                }
            }

            renderExperimentScreen();
        }

        else if (currentScreen == Screen::SIMULATION) {
            renderFrame(
                pendulumA,
                pendulumB,
                time,
                divergence(pendulumA.state, pendulumB.state));
        }
    }

    closeRenderer();
}
