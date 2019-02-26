#include "Utils/Rewind.h"

/* Recorder */

Recorder::Recorder(double seconds, double preiod){
    this->period = period;
    this->maxSize = (seconds + period - 1) / period;
}

void Recorder::Record(double point){
    if(this->index > this->maxSize){
        std::cout << "Max recording length reached!" << std::endl;
        return;
    }

    this->recording.push_back(point);

    ++this->index;
}

void Recorder::EchoRecording(){
    for (std::vector<double>::const_iterator i = this->recording.begin(); i != this->recording.end(); ++i)
        std::cout << *i << ' ';
}

/* Player */
Player::Player(std::vector<double> recording){
    this->recording = recording;
}

double Player::Next(){
    ++this->index;
    return this->recording[index - 1];
}

bool Player::IsFinished(){
    return this->index > this->recording.size();
}