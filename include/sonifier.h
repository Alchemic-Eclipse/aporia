#pragma once

#include "DoublePendulum.h"
#include "raylib.h"

class Sonifier {
public:

    void initialize();
    void update(const DoublePendulum& pendulumA, const DoublePendulum& pendulumB);
    void close();

private:

    // Represents two continuous audio streams
    AudioStream streamA;
    AudioStream streamB;

    // Remembers where we are inside the sine wave
    float phaseA = 0.0f;
    float phaseB = 0.0f;

    float frequencyA = 440.0f;
    float frequencyB = 440.0f;

    bool streamAStarted = false;
    bool streamBStarted = false;

    float thetaToFrequency(double theta);

    float omegaToAmplitude(double omega);

};
