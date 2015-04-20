/*
  Timing.h - Library for Timers and Stopwatches for the Arduino.
  Created by Fuksz Domonkos, 2015.04.20.
*/
#ifndef Timing_h
#define Timing_h

#include "Arduino.h"

typedef unsigned long Time;

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

class StopWatch{
public: 
    enum State{RESETED, ACTIVE, STOPPED};
private:
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

class ChannelTimer : public Timer{
private:
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

#endif
