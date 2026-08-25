#include "iostream"
#include <cmath>


int main()
{

    //------------------------------------VARIABLES-------------------------------------------------------
    const double g = 9.8;

    // Pendulum 1 properties:
    double l1 = 1.0; // meters
    double m1 = 2.0; // kgs
    double angle1 = 1.0; // radians
    double v1 = 0.0; // from rest
    double a1 = 0.0;

    // Pendulum 2 properties:
    double l2 = 1.0;
    double m2 = 1.5;
    double angle2 = 0.5;
    double v2 = 0.0;
    double a2 = 0.0;

    // Time passed per frame
    double dt = 0.00001;


    //-----------------------------------MAIN LOOP------------------------------------------------------


    while (true)
    {
        double delta = angle1 - angle2;

        // Acceleration 1:
        double nr1 = -m2 * l2 * v2 * v2 * std::sin(delta);
        nr1 -= g * std::sin(angle1) * (m1 + m2);
        nr1 -= m2 * l1 * v1 * v1 * std::sin(delta) * std::cos(delta);
        nr1 += m2 * std::cos(delta) * g * std::sin(angle2);

        double dr1 = l1 * (m1 + m2) - (l1 * m2 * std::cos(delta) * std::cos(delta));

        a1 = nr1 / dr1;

        // Acceleration 2:
        double nr2 = l1 * (m1 + m2) * v1 * v1 * std::sin(delta);
        nr2 -= (m1 + m2) * g * std::sin(angle2);
        nr2 += m2 * l2 * v2 * v2 * std::cos(delta) * std::sin(delta);
        nr2 += g * std::sin(angle1) * std::cos(delta) * (m1 + m2);

        double dr2 = l2 * (m1 + m2) - (m2 * l2 * std::cos(delta) * std::cos(delta));

        a2 = nr2 / dr2;



        // Updating the Values

        v1 += a1 * dt;
        v2 += a2 * dt;

        angle1 += v1 * dt;
        angle2 += v2 * dt;

        std::cout << "Angle 1: " << angle1 << "  | Angle 2: " << angle2 << std::endl;


    }


}