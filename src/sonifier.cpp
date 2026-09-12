#include "../include/sonifier.h"

#include <cmath>
#include <vector>
#include <algorithm>

void Sonifier::initialize() {

    // Initialize Raylib audio system
    InitAudioDevice();

    // Set default size of the audio buffer
    SetAudioStreamBufferSizeDefault(4096);

    // Create an audio stream
    streamA = LoadAudioStream(44100, 16, 1);
    streamB = LoadAudioStream(44100, 16, 1);

}

float Sonifier::thetaToFrequency(double theta) {

    const float minFrequency = 220.0f;
    const float maxFrequency = 880.0f;

    double normalizedTheta = (std::sin(theta) + 1.0) / 2.0 ;

    return minFrequency + static_cast<float>(normalizedTheta) * (maxFrequency - minFrequency);
}

// Helper, that fills audio buffer with sine wave samples
void generateSamples(
    std::vector<short>& buffer,
    float frequency,
    float amplitude,
    float& phase,
    int sampleRate
) {

    const float phaseIncrement = 2.0f * PI * frequency / sampleRate;

    for (size_t i = 0; i < buffer.size(); ++i) {

        // generate one point on the sine wave
        float sample = std::sin(phase);

        // Convert the floating point sample into a 16 bit integer
        buffer[i] = static_cast<short>(sample * amplitude * 32767.0f);

        // Move forward through the sine wave
        phase += phaseIncrement;

        if (phase >= 2.0f * PI)
            phase -= 2.0f * PI;
    }
}

void Sonifier::update(const DoublePendulum &pendulumA, const DoublePendulum &pendulumB) {

    frequencyA = thetaToFrequency(pendulumA.state.theta2);
    frequencyB = thetaToFrequency(pendulumB.state.theta2);

    float amplitudeA = omegaToAmplitude(pendulumA.state.omega2);
    float amplitudeB = omegaToAmplitude(pendulumB.state.omega2);

    const int sampleCount = 4096;

    std::vector<short> bufferA(sampleCount);
    std::vector<short> bufferB(sampleCount);


    if (!streamAStarted) {
        generateSamples(bufferA, frequencyA, amplitudeA, phaseA, 44100);
        UpdateAudioStream(streamA, bufferA.data(), sampleCount);

        PlayAudioStream(streamA);
        streamAStarted = true;
    }

    if (!streamBStarted) {
        generateSamples(bufferB, frequencyB, amplitudeB, phaseB, 44100);
        UpdateAudioStream(streamB, bufferB.data(), sampleCount);

        PlayAudioStream(streamB);
        streamBStarted = true;
    }


    if (IsAudioStreamProcessed(streamA)) {
        generateSamples(bufferA, frequencyA, amplitudeA, phaseA, 44100);
        UpdateAudioStream(streamA, bufferA.data(), sampleCount);
    }

    if (IsAudioStreamProcessed(streamB)) {
        generateSamples(bufferB, frequencyB, amplitudeA, phaseB, 44100);
        UpdateAudioStream(streamB, bufferB.data(), sampleCount);
    }

}

void Sonifier::close() {
    UnloadAudioStream(streamA);
    UnloadAudioStream(streamB);

    CloseAudioDevice();
}

float Sonifier::omegaToAmplitude(double omega) {
    const float minAmplitude = 0.01f;
    const float maxAmplitude = 0.32f;

    double speed = std::abs(omega);

    double normalized = std::min(speed / 10.0, 1.0);

    return minAmplitude + static_cast<float>(normalized) * (maxAmplitude - minAmplitude);
}
