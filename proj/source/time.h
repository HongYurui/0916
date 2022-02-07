#ifndef TIME_H
#define TIME_H

class Time {
 public:
    Time();
    unsigned get();
    void operator++();
 private:
    unsigned time;
};

#endif