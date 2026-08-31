#pragma once

struct Parameters {
    double m1;
    double m2;
    double l1;
    double l2;
    double g;
};

struct State {
    double theta1;
    double theta2;
    double omega1;
    double omega2;
};

struct Derivative {
    double theta1;
    double theta2;
    double omega1;
    double omega2;
};

class DoublePendulum {
public:
    Parameters parameters;
    State state;

    Derivative derivatives(const State& s) const;
    double energy(const State& s) const;
};