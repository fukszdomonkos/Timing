/*
  Timing.h - Library for Timers and Stopwatches for the Arduino.
  Created by Fuksz Domonkos, 2015.04.20.
*/
#ifndef Timing_h
#define Timing_h

#include "Arduino.h"

//defining a Time type for clearer use
typedef unsigned long Time;

//Timer and ChannelTimer:
//call update method in the beginning of the loop! else it never stops by itself

//after started it will stop after the time specified
//you can read its state any time
class Timer{
protected:
    bool isOn;
    Time activeTime;
    Time presetTime;
    Time startMillis;
public:
    Timer(Time time);
    bool isActive();
    virtual void start();
    virtual void start(Time time);
    virtual void stop();
    void update();
    Time remainingTime();
};

//extension for the Timer class with a channel (Pin) that changes with the state
class ChannelTimer : public Timer{
protected:
    int channelNumber;
    int channelState;
public:
    ChannelTimer(int channel, Time time);
    void set();
    int getChannel();
    void start();
    void start(Time time);
    void stop();
};

//counts time from the time it got started
//you can read its state any time
class StopWatch{
public: 
    enum State{RESETED, ACTIVE, STOPPED};
protected:
    bool isOn;
    Time startTime;
    State state;
public:   
    StopWatch();
    State getState();
    void start();
    void startOrContinue();
    void stop();
    void reset();
    Time elapsedTime();
    bool isOver(Time limit);
};



#endif
