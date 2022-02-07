#include "time.h"

Time::Time() {
    time = 0;
}

unsigned Time::get() {
    return this->time;
}

void Time::operator++() {
    this->time++;
}