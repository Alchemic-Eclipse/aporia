#include "../include/renderer.h"
#include "../include/ExperimentSettings.h"
#include "raylib.h"
#include <cmath>
#include <string>

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


void updateTextBox(TextBox& box) {
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        box.active = CheckCollisionPointRec(mouse, box.bounds); // True if click point inside the box, else false
    }

    if (!box.active)
        return; // If textbox isn't selected, stop processing it

    int key = GetCharPressed(); // get the next char typed by user
    while (key > 0) {           // while char are waiting, keep processing
        box.text += static_cast<char>(key);     // convert int char code to "char" --> add that char to the end of string
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !box.text.empty()) {
        box.text.pop_back();    // Remove the final char
    }
}

void drawTextBox(const TextBox &box) {

    DrawRectangleRec(box.bounds, BLACK);    // Draw a color filled rectangle

    Color borderColor = box.active ? WHITE : GRAY;      // condition ? ifTrue : ifFalse
    DrawRectangleLinesEx(box.bounds, 2, borderColor);   // Draw the borders of that rectangle

    DrawText(       // Draw the text inside that rectangle
        box.text.c_str(),      // box.text is std::string, but Drawtext needs C-style string, so...
        box.bounds.x + 10,     // Padding
        box.bounds.y + 8,      // Padding
        20,
        WHITE
    );
}

// Reusable func to combine different tasks into one
void drawParameterBox(const char* label, TextBox& box, int labelX, int boxX, int y) {

    DrawText(label, labelX, y+8, 25, WHITE);

    box.bounds = {
        static_cast<float>(boxX),       // Top left corner X position
        static_cast<float>(y),          // Top left corner Y position
        180,
        35
    };

    updateTextBox(box);
    drawTextBox(box);
}

// Take whatever the user typed and try to turn it into a double
double readDouble(const TextBox& box, double currentValue) {
    try {
        size_t charactersRead = 0;      // Variable keeping track of how many chars stod() successfully understood
        double value = std::stod(box.text, &charactersRead);    // convert String to double and tell how many you successfully understood

        if (charactersRead != box.text.size()) {
            return currentValue;    // if stod didn't convert the entire textbox, reject it
        }
        return value;       // if everything worked fine, give us the converted number
    }

    catch (...) {
        return currentValue;      // If conversion fails entirely, keep the previous valid value.
    }
}


void renderExperimentScreen(ExperimentSettings& settings) {

    BeginDrawing();

    ClearBackground(BLACK);

    // Drawing Text Boxes

    // Here "static", because renderExperimentScreen() gets called every frame: if not for static, it'd reset to default value every frame (120 fps)
    static TextBox m1Box = {{0,0,0,0}, "2.0"};
    static TextBox m2Box = {{0,0,0,0}, "1.5"};

    static TextBox l1Box = {{0,0,0,0}, "80.0"};
    static TextBox l2Box = {{0,0,0,0}, "80.0"};

    static TextBox gBox = {{0,0,0,0}, "9.8"};

    static TextBox theta1Box = {{0,0,0,0}, "3.14"};
    static TextBox theta2ABox = {{0,0,0,0}, "0.5"};
    static TextBox theta2BBox = {{0,0,0,0}, "0.5000000001"};

    static TextBox omega1Box = {{0,0,0,0}, "2.0"};
    static TextBox omega2Box = {{0,0,0,0}, "4.0"};

    static TextBox dtBox = {{0,0,0,0}, "0.015"};


    settings.m1 = readDouble(m1Box, settings.m1);       // Take the text inside m1Box, covert it into a double, and put that into settings.m1
    settings.m2 = readDouble(m2Box, settings.m2);

    settings.l1 = readDouble(l1Box, settings.l1);
    settings.l2 = readDouble(l2Box, settings.l2);

    settings.g = readDouble(gBox, settings.g);

    settings.theta1 = readDouble(theta1Box, settings.theta1);
    settings.theta2A = readDouble(theta2ABox, settings.theta2A);
    settings.theta2B = readDouble(theta2BBox, settings.theta2B);

    settings.omega1 = readDouble(omega1Box, settings.omega1);
    settings.omega2 = readDouble(omega2Box, settings.omega2);

    settings.dt = readDouble(dtBox, settings.dt);




    DrawText("APORIA", 60, 40, 40, WHITE);
    DrawText("EXPERIMENT SETUP", 60,100,30, WHITE);

    // Mass
    DrawText("MASS", 60, 170, 25, WHITE);
    drawParameterBox("m1", m1Box, 80, 200, 215);
    drawParameterBox("m2", m2Box, 80, 200, 255);

    // Length
    DrawText("LENGTH", 400, 170, 25, WHITE);
    drawParameterBox("l1", l1Box, 420, 520, 215);
    drawParameterBox("l2", l2Box, 420, 520, 255);

    // Gravity
    DrawText("Gravity", 740, 170, 25, WHITE);
    drawParameterBox("g", gBox, 760, 880, 215);

    // Initial Conditions
    DrawText("Initial Conditions", 60, 330,25, WHITE);
    drawParameterBox("theta1", theta1Box, 80, 200, 375);
    drawParameterBox("theta2 A", theta2ABox, 80, 200, 415);
    drawParameterBox("theta2 B", theta2BBox, 80, 200, 455);

    drawParameterBox("omega1", omega1Box, 420, 540, 375);
    drawParameterBox("omega2", omega2Box, 420, 540, 415);

    // Time step
    DrawText("Time step", 740, 330, 25, WHITE);
    drawParameterBox("dt", dtBox, 760, 880, 375);

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