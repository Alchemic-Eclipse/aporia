#include "../include/renderer.h"
#include "../include/ExperimentSettings.h"
#include "raylib.h"
#include <cmath>
#include <string>
#include "iostream"

Camera2D camera;

void initializeRenderer() {
    InitWindow(1200, 800, "Aporia");
    SetTargetFPS(120);

    camera.target = {0,0};
    camera.offset = {585,350};
    camera.rotation = 0;
    camera.zoom = 2;
}

namespace {
    constexpr int screenWidth = 1200;
    constexpr int screenHeight = 800;

    const Color background = {8, 12, 18, 255};
    const Color primaryText = {218, 239, 244, 255};
    const Color secondaryText = {154, 190, 202, 255};
    const Color accent = {91, 176, 196, 255};

    const Color pendulumAColor = {255, 90, 120, 255};
    const Color pendulumBColor = {90, 210, 255, 255};

    // Indecisive b/w them ;-;
    // const Color pendulumAColor = {255, 105, 145, 255}; // Neon rose
    // const Color pendulumBColor = {80, 220, 255, 255};   // Electric cyan
}

void renderHomeScreen() {

    BeginDrawing();
    ClearBackground(background);

    // Main Title
    const char* title = "APORIA";
    int titleFontSize = 100;
    int titleWidth = MeasureText(title, titleFontSize);
    DrawText(title, (screenWidth - titleWidth)/2 , 120, titleFontSize, primaryText);

    // Subtitle
    const char* subtitle = "HEAR CHAOS";
    int subtitleFontSize = 33;
    int subtitleWidth = MeasureText(subtitle, subtitleFontSize);
    DrawText(subtitle, (screenWidth - subtitleWidth)/2, 235, subtitleFontSize, accent);

    // Decor Line
    DrawLine(400, 350, 800, 350, Color{45, 60, 70, 255});

    // Begin Button
    float buttonWidth = 300;
    float buttonHeight = 64;

    Rectangle beginButton = {
        (1200 - buttonWidth) / 2.0f,
        570,
        buttonWidth,
        buttonHeight
    };

    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, beginButton); // Check if hovered

    // Hover Effects
    Color borderColor = hovered ? secondaryText : accent;
    Color buttonFill = hovered ? BLACK : background;

    if (hovered)
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND); // Pointer Cursor
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    // Draw the Button
    DrawRectangleRec(beginButton, buttonFill);
    DrawRectangleLinesEx(beginButton, 2, borderColor);

    // Button Text
    const char* buttonText = "BEGIN EXPERIMENT";
    int buttonFontSize = 20;
    int textWidth = MeasureText(buttonText, buttonFontSize);
    float textX = beginButton.x + (beginButton.width - textWidth) / 2.0f;
    float textY = beginButton.y + (beginButton.height - buttonFontSize) / 2.0f;

    DrawText(
        buttonText,
        static_cast<int>(textX),
        static_cast<int>(textY),
        buttonFontSize,
        primaryText
    );

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

    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, box.bounds);

    Color borderColor =
        box.active ? primaryText :
        hovered ? secondaryText :
        accent;
    Color fillColor =
        box.active ? BLACK :
        hovered ? BLACK :
        background;

    DrawRectangleRec(box.bounds, fillColor);    // Draw a color filled rectangle
    DrawRectangleLinesEx(box.bounds, 2, borderColor);   // Draw the borders of that rectangle

    DrawText(       // Draw the text inside that rectangle
        box.text.c_str(),      // box.text is std::string, but Drawtext needs C-style string, so...
        box.bounds.x + 10,     // Padding
        box.bounds.y + 8,      // Padding
        20,
        primaryText
    );
}

// Reusable func to combine different tasks into one
void drawParameterBox(const char* label, TextBox& box, int labelX, int boxX, int y) {

    DrawText(label, labelX, y+8, 25, secondaryText);

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
    // SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    ClearBackground(background);

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

    DrawText("APORIA", 40, 40, 50, primaryText);
    DrawText("EXPERIMENT SETUP", 40,110,30, secondaryText);

    // Mass
    DrawText("MASS", 60, 200, 25, WHITE);
    drawParameterBox("m1", m1Box, 80, 200, 255);
    drawParameterBox("m2", m2Box, 80, 200, 305);

    // Length
    DrawText("LENGTH", 400, 200, 25, WHITE);
    drawParameterBox("l1", l1Box, 420, 520, 255);
    drawParameterBox("l2", l2Box, 420, 520, 305);

    // Gravity
    DrawText("Gravity", 740, 200, 25, WHITE);
    drawParameterBox("g", gBox, 760, 880, 255);

    // Initial Conditions
    DrawText("Initial Conditions", 60, 385,25, WHITE);
    drawParameterBox("theta1", theta1Box, 80, 200, 440);
    drawParameterBox("theta2 A", theta2ABox, 80, 200, 490);
    drawParameterBox("theta2 B", theta2BBox, 80, 200, 540);

    drawParameterBox("omega1", omega1Box, 420, 540, 440);
    drawParameterBox("omega2", omega2Box, 420, 540, 490);

    // Time step
    DrawText("Time step", 740, 385, 25, WHITE);
    drawParameterBox("dt", dtBox, 760, 880, 440);

    // Start Button
    Rectangle startButton = {800,670, 300, 65};

    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, startButton); // Check if hovered

    // Hover Effects
    Color borderColor = hovered ? secondaryText : accent;
    Color buttonFill = hovered ? BLACK : background;

    if (hovered)
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND); // Pointer Cursor
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);


    DrawRectangleRec(startButton, buttonFill);
    DrawRectangleLinesEx(startButton, 2, borderColor);

    // Start Button Text
    const char* buttonText = "START EXPERIMENT";
    int buttonFontSize = 20;

    int textWidth = MeasureText(buttonText, buttonFontSize);
    float textX = startButton.x + (startButton.width - textWidth) / 2.0f;
    float textY = startButton.y + (startButton.height - buttonFontSize) / 2.0f;

    DrawText(buttonText,
        static_cast<int>(textX),
        static_cast<int>(textY),
        buttonFontSize,
        primaryText
        );

    EndDrawing();
}

void renderSimulation(const DoublePendulum& pendulumA, const DoublePendulum& pendulumB, double time, double divergence, double energyError) {

    BeginDrawing();

        ClearBackground(background);

        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        BeginMode2D(camera);

        // Draw and calculate A
        double Ax1 = pendulumA.parameters.l1 * std::sin(pendulumA.state.theta1);
        double Ay1 = -pendulumA.parameters.l1 * std::cos(pendulumA.state.theta1);
        DrawCircle(Ax1,Ay1,7,pendulumAColor);

        double Ax2 = Ax1 + pendulumA.parameters.l2 * std::sin(pendulumA.state.theta2);
        double Ay2 = Ay1 - pendulumA.parameters.l2 * std::cos(pendulumA.state.theta2);
        DrawCircle(Ax2,Ay2,7,pendulumAColor);

        DrawLine(0,0,Ax1,Ay1, pendulumAColor);
        DrawLine(Ax1,Ay1,Ax2,Ay2, pendulumAColor);

        // Draw and Calculate B
        double Bx1 = pendulumB.parameters.l1 * std::sin(pendulumB.state.theta1);
        double By1 = -pendulumB.parameters.l1 * std::cos(pendulumB.state.theta1);
        DrawCircle(Bx1,By1,7,pendulumBColor);

        double Bx2 = Bx1 + pendulumB.parameters.l2 * std::sin(pendulumB.state.theta2);
        double By2 = By1 - pendulumB.parameters.l2 * std::cos(pendulumB.state.theta2);
        DrawCircle(Bx2,By2,7,pendulumBColor);

        DrawLine(0,0,Bx1,By1, pendulumBColor);
        DrawLine(Bx1,By1,Bx2,By2, pendulumBColor);

        EndMode2D();

        DrawText(TextFormat("Time: %.2f", time), 20,20,25, primaryText);
        DrawText(TextFormat("Divergence: %.6f", divergence), 20, 60, 25, primaryText);
        DrawText(TextFormat("Energy Error: %.9f%%", energyError * 100), 20, 100, 25, primaryText);

        Rectangle controlButton = {1040, 20, 130, 40};

        Vector2 mouse = GetMousePosition();
        bool hovered = CheckCollisionPointRec(mouse, controlButton);

        // Hover Effects
        Color borderColor = hovered ? secondaryText : accent;
        Color buttonFill = hovered ? BLACK : background;

        if (hovered)
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND); // Pointer Cursor
        else
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        const char* buttonText = "Controls";
        int buttonFontSize = 20;

        int textWidth = MeasureText(buttonText, buttonFontSize);
        float textX = controlButton.x + (controlButton.width - textWidth) / 2.0f;
        float textY = controlButton.y + (controlButton.height - buttonFontSize) / 2.0f;

        DrawRectangleRec(controlButton, buttonFill);
        DrawRectangleLinesEx(controlButton, 2, borderColor);

        DrawText(buttonText,
            static_cast<int>(textX),
            static_cast<int>(textY),
            buttonFontSize,
            primaryText
            );

    EndDrawing();
}

void renderControlsOverlay() {

    DrawRectangle(250, 140, 700, 540, background);
    DrawRectangleLines(250, 140, 700, 520, accent);

    DrawText("Controls", 290, 180, 32, primaryText);

    DrawText("Space", 310, 250, 24, accent);
    DrawText("Pause/Resume", 470, 250, 24, primaryText);

    DrawText("N", 310, 300, 24, accent);
    DrawText("Advance one timestep while paused", 470, 300, 24, primaryText);

    DrawText("R", 310, 350, 24, accent);
    DrawText("Reset simulation", 470, 350, 24, primaryText);

    DrawText("M", 310, 400, 24, accent);
    DrawText("Mute/Unmute", 470, 400, 24, primaryText);

    DrawText("Backspace", 310, 450, 24, accent);
    DrawText("Return to experiment settings", 470, 450, 24, primaryText);

    DrawText("H", 310, 500, 24, accent);
    DrawText("Return to Home screen", 470, 500, 24, primaryText);

    DrawText("Click Controls or press ESC to close", 310, 595, 20, secondaryText);

}

void closeRenderer() {
    CloseWindow();
}
