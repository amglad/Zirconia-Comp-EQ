/*
  ==============================================================================

    CompEQ.cpp
    Created: 10 May 2023 2:02:12pm
    Author:  Mitch Glad

  ==============================================================================
*/

#include "CompEQ.h"

void EQ::updateComponents(double pot, double pivotFreq)
{
    double C1 = 0.000005 * pow(pivotFreq, -1);
    R1 = Ts / (2 * C1);

    double C2 = C1;
    R2 = Ts / (2 * C2);

    double P1 = pot * 50000.0;
    double P2 = (1 - pot) * 50000.0;

    Gw = 1 / R1 + 1 / R6;
    Gx = 1 / R3 + 1 / P1 + 1 / R5;
    Gy = 1 / R4 + 1 / P2 + 1 / (R1 * R6 * Gw);
    Gz = 1 / R2 + 1 / R5 - 1 / (R5 * R5 * Gx);

    double G1 = 1 / R4 + 1 / (R1 * R6 * Gw);
    double G2 = 1 / R2 + 1 / (R3 * R5 * Gx);

    double Gx1 = G1 / (R1 * Gy * Gw) - 1 / (R1 * Gw) + 1 - G1 / Gy;
    double Gx2 = G2 / Gz - 1;

    double Gin = 1 / (R1 * R1 * Gw) + 1 / (R3 * R3 * Gx) - 1 / R1 - 1 / R3 + G1 / (R1 * Gy) - G1 / (R1 * R1 * Gy * Gw) + G2 / (R3 * R5 * Gx * Gz);
    double Gout = 1 / R2 + 1 / R4 - G1 / (R4 * Gy) - G2 / (R2 * Gz);

    b0 = Gin / Gout;
    b1 = Gx1 / Gout;
    b2 = Gx2 / Gout;
}

float EQ::processSample(float x, int c)
{
    float Vin = x;
    float Vout = b0 * Vin + b1 * x1[c] + b2 * x2[c];

    // calculate voltages
    double Vy = Vin / (R1 * Gy) - Vin / (R1 * R1 * Gy * Gw) + Vout / (R4 * Gy) + x1[c] / (R1 * Gy * Gw) - x1[c] / Gy;
    double Vw = Vin / (R1 * Gw) + Vy / (R6 * Gw) - x1[c] / Gw;
    double Vz = Vin / (R3 * R5 * Gx * Gz) + Vout / (R2 * Gz) + x2[c] / Gz;

    // state updates
    x1[c] = 2 / R1 * (Vin - Vw) - x1[c];
    x2[c] = 2 / R2 * (Vz - Vout) - x2[c];
    
    // take our output
    return Vout;
}

void EQ::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    Fs = sampleRate;
    bufferSize = samplesPerBlock;
    Ts = 1/Fs;
    
    x1[0] = 0.0;
    x1[1] = 0.0;
    x2[0] = 0.0;
    x2[1] = 0.0;
}
