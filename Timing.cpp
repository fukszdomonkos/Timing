#include "Arduino.h"
#include "Timing.h"


    Timer::Timer(Time time){
        isOn = false;
        startMillis = 0;
        activeTime = time;
        presetTime = time;
    }
    
    bool Timer::isActive(){ return isOn; }
    
    void Timer::start(){
        start(presetTime);
    }
    void Timer::start(Time time){//start can be called with a different time than preset
        isOn = true;
        startMillis = millis();
        activeTime = time;
    }
    void Timer::stop(){
        isOn = false;
       // startMillis = 0;
    }
    void Timer::update(){
        Time currentMillis = millis();
        if((isOn == true) && ((currentMillis - startMillis) > activeTime)){
            stop();
        } 
    }
    Time Timer::remainingTime(){
        if(isOn==false) return -1;
        Time currentMillis = millis();
        return currentMillis - startMillis;
    }



    StopWatch::StopWatch(/*Time limit*/){
        isOn = false;
        startTime = 0;  
        state = RESETED;
//        limitTime = limit;
    }
    StopWatch::State StopWatch::getState(){return state;}
    void StopWatch::start(){//restarts!!!
        isOn = true;
        startTime = millis();
        state = ACTIVE;
    }
    void StopWatch::startOrContinue(){//if on does nothing, if off starts
        if(isOn==true) return;
        start();
    }
    void StopWatch::stop(){
        isOn = false;
        state = STOPPED;
        //no reset
    }
    void StopWatch::reset(){
        isOn = false;
        startTime = 0;
        state = RESETED;
    }
    Time StopWatch::elapsedTime(){
        if (state==RESETED) return 0;
        Time currentTime = millis();
        return currentTime - startTime;
    }

    bool StopWatch::isOver(Time limit){
        if(limit<elapsedTime()) return true; else return false;
    }



    ChannelTimer::ChannelTimer(int channel, Time time): Timer(time){
        channelNumber = channel;
        pinMode(channelNumber, OUTPUT);
        channelState = LOW;
        set();
    }
    void ChannelTimer::set(){
        digitalWrite(channelNumber, channelState);
    }
    int ChannelTimer::getChannel(){ return channelNumber; }
    void ChannelTimer::start(){
        start(presetTime);
    }
    void ChannelTimer::start(Time time){
      
        Timer::start(time);
        channelState = HIGH;
        set();
    }
    void ChannelTimer::stop(){
        Timer::stop();
        channelState = LOW;
        set();
    }
