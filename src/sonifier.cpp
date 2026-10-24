#include "../include/sonifier.h"

#include <algorithm>
#include <cmath>
#include <vector>

namespace {
    constexpr unsigned int sampleRate = 44100;
    constexpr int sampleCount = 4096;
    constexpr int sampleSize = 16;
    constexpr int channels = 1;

    constexpr float minFrequency = 220.0f;
    constexpr float maxFrequency = 880.0f;

    constexpr float minAmplitude = 0.01f;
    constexpr float maxAmplitude = 0.32f;

    // Generate one buffer of sine-wave samples.
    void generateSamples(
        std::vector<short>& buffer,
        float frequency,
        float amplitude,
        float& phase
    ) {
        const float phaseIncrement =
            2.0f * PI * frequency / static_cast<float>(sampleRate);

        for (short& sampleValue : buffer) {
            const float sample = std::sin(phase);

            sampleValue = static_cast<short>(
                sample * amplitude * 32767.0f
            );

            phase += phaseIncrement;

            // Keep the phase within one cycle.
            if (phase >= 2.0f * PI) {
                phase -= 2.0f * PI;
            }
        }
    }
}

void Sonifier::initialize() {
    // Configure the audio buffer before initializing the device.
    SetAudioStreamBufferSizeDefault(sampleCount);
    InitAudioDevice();

    streamA = LoadAudioStream(sampleRate, sampleSize, channels);
    streamB = LoadAudioStream(sampleRate, sampleSize, channels);

    // Start playback only after the streams have been created.
    streamAStarted = false;
    streamBStarted = false;
}

float Sonifier::thetaToFrequency(double theta) {
    const double normalizedTheta = (std::sin(theta) + 1.0) / 2.0;

    return minFrequency +
        static_cast<float>(normalizedTheta) *
        (maxFrequency - minFrequency);
}

float Sonifier::omegaToAmplitude(double omega) {
    const double speed = std::abs(omega);
    const double normalized = std::clamp(speed / 10.0, 0.0, 1.0);

    return minAmplitude +
        static_cast<float>(normalized) *
        (maxAmplitude - minAmplitude);
}

void Sonifier::update(
    const DoublePendulum& pendulumA,
    const DoublePendulum& pendulumB
) {
    if (muted) {
        return;
    }

    frequencyA = thetaToFrequency(pendulumA.state.theta2);
    frequencyB = thetaToFrequency(pendulumB.state.theta2);

    const float amplitudeA =
        omegaToAmplitude(pendulumA.state.omega2);

    const float amplitudeB =
        omegaToAmplitude(pendulumB.state.omega2);

    // Reuse buffers rather than allocating them on every update.
    static std::vector<short> bufferA(sampleCount);
    static std::vector<short> bufferB(sampleCount);

    if (!streamAStarted) {
        generateSamples(bufferA, frequencyA, amplitudeA, phaseA);
        UpdateAudioStream(streamA, bufferA.data(), sampleCount);

        PlayAudioStream(streamA);
        streamAStarted = true;
    }

    if (!streamBStarted) {
        generateSamples(bufferB, frequencyB, amplitudeB, phaseB);
        UpdateAudioStream(streamB, bufferB.data(), sampleCount);

        PlayAudioStream(streamB);
        streamBStarted = true;
    }

    if (IsAudioStreamProcessed(streamA)) {
        generateSamples(bufferA, frequencyA, amplitudeA, phaseA);
        UpdateAudioStream(streamA, bufferA.data(), sampleCount);
    }

    if (IsAudioStreamProcessed(streamB)) {
        generateSamples(bufferB, frequencyB, amplitudeB, phaseB);
        UpdateAudioStream(streamB, bufferB.data(), sampleCount);
    }
}

void Sonifier::toggleMute() {
    muted = !muted;

    if (muted) {
        PauseAudioStream(streamA);
        PauseAudioStream(streamB);
    } else {
        ResumeAudioStream(streamA);
        ResumeAudioStream(streamB);
    }
}

void Sonifier::close() {
    if (streamA.buffer != nullptr) {
        UnloadAudioStream(streamA);
    }

    if (streamB.buffer != nullptr) {
        UnloadAudioStream(streamB);
    }

    if (IsAudioDeviceReady()) {
        CloseAudioDevice();
    }

    streamAStarted = false;
    streamBStarted = false;
}
