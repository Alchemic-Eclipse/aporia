#include "../include/renderer.h"
#include "raylib.h"
#include <cmath>

Camera2D camera;

void initializeRenderer() {
    InitWindow(800, 600, "Aporia");
    SetTargetFPS(120);

    camera.target = {0,0};
    camera.offset = {400,300};
    camera.rotation = 0;
    camera.zoom = 2;
}

void renderFrame(const DoublePendulum &pendulum) {

    BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(camera);

        // pendulum.parameters.l1
        double x1 = pendulum.parameters.l1 * std::sin(pendulum.state.theta1);
        double y1 = -pendulum.parameters.l1 * std::cos(pendulum.state.theta1);
        DrawCircle(x1,y1,5,RED);

        double x2 = x1 + pendulum.parameters.l2 * std::sin(pendulum.state.theta2);
        double y2 = y1 - pendulum.parameters.l2 * std::cos(pendulum.state.theta2);
        DrawCircle(x2,y2,5,BLUE);

        DrawLine(0,0,x1,y1, RED);
        DrawLine(x1,y1,x2,y2, BLUE);




        EndMode2D();

    EndDrawing();

}

void closeRenderer() {
    CloseWindow();
}