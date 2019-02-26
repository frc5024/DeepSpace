#ifndef _UTILS_REWIND_H
#define _UTILS_REWIND_H

#include <iostream>
#include <vector>

class Recorder{
    public:
        Recorder(double seconds, double period);

        void Record(double point);
        std::vector<double> GetRecording();
        void EchoRecording();

    private:
        double period;
        unsigned int index = 0;
        unsigned int maxSize;

        std::vector<double> recording;
};

class Player{
    public:
        Player(std::vector<double> recording);
        double Next();
        void Rewind();
        bool IsFinished();
    
    private:
        unsigned int index = 0;
        std::vector<double> recording;
};

#endif