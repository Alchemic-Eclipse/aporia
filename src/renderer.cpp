#include "../include/renderer.h"
#include "raylib.h"
#include <cmath>

Camera2D camera;

void initializeRenderer() {
    InitWindow(1200, 800, "Aporia");
    SetTargetFPS(120);

    camera.target = {0,0};
    camera.offset = {585,350};
    camera.rotation = 0;
    camera.zoom = 2;
}

void renderHomeScreen() {
    BeginDrawing();

    ClearBackground(BLACK);

    DrawText("APORIA", 500, 200, 50, WHITE);
    DrawText("HEAR CHAOS", 450, 270, 30, WHITE);

    Rectangle beginButton = {500, 350, 200, 60};

    DrawRectangleRec(beginButton, DARKGRAY);
    DrawText("BEGIN", 555, 367, 25, WHITE);

    EndDrawing();
}

void renderExperimentScreen() {

    BeginDrawing();

    ClearBackground(BLACK);

    DrawText("APORIA", 60, 40, 40, WHITE);
    DrawText("EXPERIMENT SETUP", 60,100,30, WHITE);

    // Mass
    DrawText("MASS", 60, 170, 25, WHITE);
    DrawText("m1", 80, 215, 20, WHITE);
    DrawText("2.0", 200, 215, 20, WHITE);

    DrawText("m2", 80, 255, 20, WHITE);
    DrawText("1.5", 200, 255, 20, WHITE);

    // Length
    DrawText("LENGTH", 400, 170, 25, WHITE);
    DrawText("l1", 420, 215, 20, WHITE);
    DrawText("80.0", 520,215,20, WHITE);

    DrawText("l2", 420, 255, 20, WHITE);
    DrawText("80.0", 520, 255, 20, WHITE);

    // Gravity
    DrawText("Gravity", 740, 170, 25, WHITE);
    DrawText("g", 760, 215, 20, WHITE);
    DrawText("9.8", 880, 215, 20, WHITE);

    // Initial Conditions
    DrawText("Initial Conditions", 60, 330,25, WHITE);

    DrawText("theta1", 80, 375, 20, WHITE);
    DrawText("3.14", 200, 375, 20, WHITE);

    DrawText("theta2 A", 80, 415, 20, WHITE);
    DrawText("0.5", 200, 415, 20, WHITE);

    DrawText("theta2 B", 80, 455, 20, WHITE);
    DrawText("0.5000000001", 200, 455, 20, WHITE);

    DrawText("omega1", 420, 375, 20, WHITE);
    DrawText("2.0", 540, 375, 20, WHITE);

    DrawText("omega2", 420,415, 20, WHITE);
    DrawText("4.0", 540,415,20, WHITE);

    // Time step
    DrawText("Time step", 740, 330, 25, WHITE);
    DrawText("dt", 760, 375, 20, WHITE);
    DrawText("0.015", 880, 375, 20, WHITE);

    // Start Button
    Rectangle startButton = {740,500, 300, 65};

    DrawRectangleRec(startButton, DARKGRAY);
    DrawText("START EXPERIMENT", 765, 520, 20, WHITE);

    EndDrawing();
}

void renderFrame(const DoublePendulum& pendulumA, const DoublePendulum& pendulumB, double time, double divergence) {

    BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(camera);

        // Draw and calculate A

        double Ax1 = pendulumA.parameters.l1 * std::sin(pendulumA.state.theta1);
        double Ay1 = -pendulumA.parameters.l1 * std::cos(pendulumA.state.theta1);
        DrawCircle(Ax1,Ay1,7,RED);

        double Ax2 = Ax1 + pendulumA.parameters.l2 * std::sin(pendulumA.state.theta2);
        double Ay2 = Ay1 - pendulumA.parameters.l2 * std::cos(pendulumA.state.theta2);
        DrawCircle(Ax2,Ay2,7,RED);

        DrawLine(0,0,Ax1,Ay1, RED);
        DrawLine(Ax1,Ay1,Ax2,Ay2, RED);

        // Draw and Calculate B

        double Bx1 = pendulumB.parameters.l1 * std::sin(pendulumB.state.theta1);
        double By1 = -pendulumB.parameters.l1 * std::cos(pendulumB.state.theta1);
        DrawCircle(Bx1,By1,7,BLUE);

        double Bx2 = Bx1 + pendulumB.parameters.l2 * std::sin(pendulumB.state.theta2);
        double By2 = By1 - pendulumB.parameters.l2 * std::cos(pendulumB.state.theta2);
        DrawCircle(Bx2,By2,7,BLUE);

        DrawLine(0,0,Bx1,By1, BLUE);
        DrawLine(Bx1,By1,Bx2,By2, BLUE);

        EndMode2D();

        DrawText(TextFormat("Time: %.2f", time), 20,20,25,WHITE);
        DrawText(TextFormat("Divergence: %.6f", divergence), 20, 50, 25, WHITE);

    EndDrawing();
}

void closeRenderer() {
    CloseWindow();
}