#pragma once
#include <raylib.h>
#include "ExperimentSettings.h"
#include "DoublePendulum.h"
#include <string>

void initializeRenderer();

struct TextBox {
    Rectangle bounds;
    std::string text;
    bool active = false;
};

void updateTextBox(TextBox& box);
void drawTextBox(const TextBox& box);

void drawParameterBox(const char* label, TextBox& box, int labelX, int boxX, int y);

void renderHomeScreen();
void renderExperimentScreen(ExperimentSettings& settings);

void renderFrame(const DoublePendulum& pendulumA, const DoublePendulum& pendulumB, double time, double divergence);

void closeRenderer();


