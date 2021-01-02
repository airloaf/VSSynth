#include <iostream>

#include <VSynth/WAVWriter.h>

int main(int argc, char *argv[]){
    VSynth::WAVWriter writer;

    unsigned int SAMPLING_RATE = 48000;

    writer.open("TestOut.wav");

    double timeStep = 1.0 / (double) SAMPLING_RATE;
    double time = 0;
    double frequency = 200;
    double amp = 4000;

    for(int i = 0; i < SAMPLING_RATE *10; i++){
        short sample = amp * sin(frequency * time * 2.0 * 3.1415926);
        writer.writeSample(sample);
        time += timeStep;
    }

    writer.close();

    return 0;
}