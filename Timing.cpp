#include "Arduino.h"
#include "Timing.h"

//constructor for Timer class
Timer::Timer(Time time){
    isOn = false;
    startMillis = 0;
    activeTime = time;
    presetTime = time;
}

//getter for the active flag
bool Timer::isActive(){
    return isOn; 
}

//starts the timer with the time given in the constructor
void Timer::start(){
    start(presetTime);
}

//starts the timer with the time given (doesn't change the preset time)
void Timer::start(Time time){
    isOn = true;
    startMillis = millis();
    activeTime = time;
}

//stops the timer
void Timer::stop(){
    isOn = false;
}

//updater function
//call this at the beginning of the loop function
//stops the timer if time runs out
void Timer::update(){
    Time currentMillis = millis();
    if((isOn == true) && ((currentMillis - startMillis) > activeTime)){
        stop();
    } 
}

//calculates the remaining time
Time Timer::remainingTime(){
    if(isOn==false) return -1;
    Time currentMillis = millis();
    return currentMillis - startMillis;
}

//constructor fot the ChannelTimer class
//calls superclass' constructor
//sets channel low
ChannelTimer::ChannelTimer(int channel, Time time): Timer(time){
    channelNumber = channel;
    pinMode(channelNumber, OUTPUT);
    channelState = LOW;
    set();
}

//sets the channel with the current parameters
void ChannelTimer::set(){
    digitalWrite(channelNumber, channelState);
}

//getter for the channel
int ChannelTimer::getChannel(){ 
    return channelNumber; 
}

//starts with the preset time
void ChannelTimer::start(){
    start(presetTime);
}

//starts with a time given
void ChannelTimer::start(Time time){
  
    Timer::start(time);
    channelState = HIGH;
    set();
}

//stops the timer
void ChannelTimer::stop(){
    Timer::stop();
    channelState = LOW;
    set();
}

//constructor for the stopwatch class
StopWatch::StopWatch(){
    isOn = false;
    startTime = 0;  
    state = RESETED;
}

//gets the state of the stopwatch
StopWatch::State StopWatch::getState(){
    return state;
}

//starts the stopwatch, reseting it
void StopWatch::start(){//restarts!!!
    isOn = true;
    startTime = millis();
    state = ACTIVE;
}

//starts if not started, does nothing if on
void StopWatch::startOrContinue(){//if on does nothing, if off starts
    if(isOn==true) return;
    start();
}

//stops the stopwatch, changes state to stopped
void StopWatch::stop(){
    isOn = false;
    state = STOPPED;
}

//changes state to reseted
void StopWatch::reset(){
    isOn = false;
    startTime = 0;
    state = RESETED;
}

//gets the elapsed time
Time StopWatch::elapsedTime(){
    if (state==RESETED) return 0;
    Time currentTime = millis();
    return currentTime - startTime;
}

//checks if the time given if more than the elapsed
bool StopWatch::isOver(Time limit){
    if(limit<elapsedTime()) return true; else return false;
}


