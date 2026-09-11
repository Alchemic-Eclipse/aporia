#include "../include/renderer.h"
#include "raylib.h"
#include <cmath>
#include <forward_list>

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