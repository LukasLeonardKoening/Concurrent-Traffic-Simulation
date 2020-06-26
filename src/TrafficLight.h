#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

// Decleration of the MessageQueue class
template <class T>
class MessageQueue
{
public:
    void send(T &&msg);
    T receive();

private:
    std::deque<T> _queue;
    std::condition_variable _cond;
    std::mutex _mutex;
    
};

// Enum for traffic light phases
enum TrafficLightPhase {red, green};

// Decleration of the TrafficLight class
class TrafficLight : public TrafficObject
{
public:
    // constructor / desctructor
    TrafficLight();
    ~TrafficLight();

    // getters / setters
    TrafficLightPhase getCurrentPhase();

    // typical behaviour methods
    void waitForGreen();
    void simulate();

private:
    // typical behaviour methods
    void cycleThroughPhases();
    TrafficLightPhase _currentPhase;

    std::shared_ptr<MessageQueue<TrafficLightPhase>> _messages;

    std::condition_variable _condition;
    std::mutex _mutex;
};

#endif