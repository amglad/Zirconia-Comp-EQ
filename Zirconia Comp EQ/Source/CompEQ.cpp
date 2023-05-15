/*
  ==============================================================================

    CompEQ.cpp
    Created: 10 May 2023 2:02:12pm
    Author:  Mitch Glad

  ==============================================================================
*/

#include "CompEQ.h"

//void EQ::processBlock(juce::AudioBuffer<float> &buffer, float pot, float pivotFreq)
//{
//    const int numChannels = buffer.getNumChannels();    // amount of channels in buffer
//    const int numSamples = buffer.getNumSamples();      // amount of samples in buffer
//
//    const double Ts = 1 / Fs;
//    const double C1 = 5e-6 * pow(pivotFreq, -1);
//    const double R1 = Ts / (2 * C1);
//
//    const double C2 = C1;
//    const double R2 = Ts / (2 * C2);
//
//    double P1 = pot * 50e3;
//    double P2 = (1 - pot) * 50e3;
//
//    double Gw = 1 / R1 + 1 / R6;
//    double Gx = 1 / R3 + 1 / P1 + 1 / R5;
//    double Gy = 1 / R4 + 1 / P2 + 1 / (R1 * R6 * Gw);
//    double Gz = 1 / R2 + 1 / R5 - 1 / (R5 * R5 * Gx);
//
//    double G1 = 1 / R4 + 1 / (R1 * R6 * Gw);
//    double G2 = 1 / R2 + 1 / (R3 * R5 * Gx);
//
//    double Gx1 = G1 / (R1 * Gy * Gw) - 1 / (R1 * Gw) + 1 - G1 / Gy;
//    double Gx2 = G2 / Gz - 1;
//
//    double Gin = 1 / (R1 * R1 * Gw) + 1 / (R3 * R3 * Gx) - 1 / R1 - 1 / R3 + G1 / (R1 * Gy) - G1 / (R1 * R1 * Gy * Gw) + G2 / (R3 * R5 * Gx * Gz);
//    double Gout = 1 / R2 + 1 / R4 - G1 / (R4 * Gy) - G2 / (R2 * Gz);
//
//    double b0 = Gin / Gout;
//    double b1 = Gx1 / Gout;
//    double b2 = Gx2 / Gout;
//
//    for (int c = 0; c < numChannels; ++c) {             // iterate through our two channels
//
//        double x1 = 0;
//        double x2 = 0;
//
//        for (int n = 0; n < numSamples; ++n) {          // iterate through the number of samples
//
//            float x = buffer.getWritePointer(c) [n];    // grab the value of our signal
//
//            double Vin = x;
//            double Vout = b0 * Vin + b1 * x1 + b2 * x2;
//
//            // calculate voltages
//            double Vy = Vin / (R1 * Gy) - Vin / (pow(R1, 2) * Gy * Gw) + Vout / (R4 * Gy) + x1 / (R1 * Gy * Gw) - x1 / Gy;
//            double Vw = Vin / (R1 * Gw) + Vy / (R6 * Gw) - x1 / Gw;
//            double Vz = Vin / (R3 * R5 * Gx * Gz) + Vout / (R2 * Gz) + x2 / Gz;
//
//            // state updates
//            x1 = 2 / R1 * (Vin - Vw) - x1;
//            x2 = 2 / R2 * (Vz - Vout) - x2;
//
//            buffer.getWritePointer(c) [n] = Vout;          // write our output to the buffer
//        }
//    }
//}

//void EQ::processInPlace(float *buffer, float gain_Lin, const int numSamples, const int channel)
//{
//    for (int n = 0; n < numSamples; ++n) {   // iterate through the number of samples
//
//        float Vin = *buffer;
//        float Vout = b0 * Vin + b1 * x1 + b2 * x2;
//
//        // calculate voltages
//        float Vy = Vin / (R1 * Gy) - Vin / (R1 * R1 * Gy * Gw) + Vout / (R4 * Gy) + x1 / (R1 * Gy * Gw) - x1 / Gy;
//        float Vw = Vin / (R1 * Gw) + Vy / (R6 * Gw) - x1 / Gw;
//        float Vz = Vin / (R3 * R5 * Gx * Gz) + Vout / (R2 * Gz) + x2 / Gz;
//
//        // state updates
//        x1 = 2 / R1 * (Vin - Vw) - x1;
//        x2 = 2 / R2 * (Vz - Vout) - x2;
//
//        // take our output
//        *buffer = Vout * gain_Lin;
//        ++buffer;
//    }
//}


void EQ::updateComponents(float pot, float pivotFreq)
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

void EQ::resetStates()
{
    x1 = 0.0;
    x2 = 0.0;
}

float EQ::processSample(float x)
{
    float Vin = x;
    double Vout = b0 * Vin + b1 * x1 + b2 * x2;
    float VoutF = static_cast<float> (Vout);

    // calculate voltages
    double Vy = Vin / (R1 * Gy) - Vin / (R1 * R1 * Gy * Gw) + Vout / (R4 * Gy) + x1 / (R1 * Gy * Gw) - x1 / Gy;
    double Vw = Vin / (R1 * Gw) + Vy / (R6 * Gw) - x1 / Gw;
    double Vz = Vin / (R3 * R5 * Gx * Gz) + Vout / (R2 * Gz) + x2 / Gz;

    // state updates
    x1 = 2 / R1 * (Vin - Vw) - x1;
    x2 = 2 / R2 * (Vz - Vout) - x2;
    
    // take our output
    return VoutF;
}

void EQ::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    Fs = sampleRate;
    bufferSize = samplesPerBlock;
    Ts = 1/Fs;
}
