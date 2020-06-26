#include <iostream>
#include <random>
#include <chrono>
#include "TrafficLight.h"
#include <future>

/* Implementation of class "MessageQueue" */

// Receive function of the message queue
template <typename T>
T MessageQueue<T>::receive()
{
    std::unique_lock<std::mutex> lock(_mutex);
    _cond.wait(lock, [this] { return !_queue.empty(); });
    auto returnvalue = std::move(_queue.back());
    _queue.clear();
    return returnvalue;
}

// Send function of the message queue
template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    std::lock_guard<std::mutex> lguard(_mutex);
    _queue.push_back(std::move(msg));
    _cond.notify_one();
}


/* Implementation of class "TrafficLight" */

// Constructor
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
    _messages = std::make_shared<MessageQueue<TrafficLightPhase>>();
}

// Destructor
TrafficLight::~TrafficLight() { }

// Waits until the traffic light turns green
void TrafficLight::waitForGreen()
{
    while(true) {
        auto phase = _messages->receive();
        if (phase == green) {
            return;
        }
    }
}

// Returns the current Phase of the traffic light
TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

// Start a thread for the cycleThroughPhases function
void TrafficLight::simulate()
{
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
// The function changes the phase after a random time between 4 and 6 seconds
void TrafficLight::cycleThroughPhases()
{
    auto start = std::chrono::system_clock::now();

    std::uniform_real_distribution<double> uni_dis(4.0,6.0);
    std::default_random_engine random_engine(std::random_device{}());
    double elapsed_min = uni_dis(random_engine);

    while(true) {
        // Reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        auto loop_time = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = loop_time-start;

        if (elapsed_seconds.count() >= elapsed_min) {
            // Change phase
            if (_currentPhase == green) {
                _currentPhase = red;
            } else {
                _currentPhase = green;
            }

            // Add the new phase to the message queue
            auto message = _currentPhase;
            auto f_send = std::async(std::launch::async, &MessageQueue<TrafficLightPhase>::send, _messages, std::move(message));
            f_send.wait();

            elapsed_min = uni_dis(random_engine);
            start = std::chrono::system_clock::now(); 
        }
    }
}