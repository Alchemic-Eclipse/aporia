#pragma once
#include "DoublePendulum.h"

void initializeRenderer();
void renderFrame(const DoublePendulum& pendulumA, const DoublePendulum& pendulumB, double time, double divergence);
void closeRenderer();
