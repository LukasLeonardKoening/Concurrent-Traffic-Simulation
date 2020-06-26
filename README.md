# Project 4 - Concurrent Traffic Simulation

This is the fourth project from [Udacity's C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). It covers concurrency, especially threads, tasks, futures, mutexes, locks and message queues in the coding language C++.

<img src="data/traffic_simulation.gif"/>

----

## Project Overview

### Goals:

* Implement the logic for traffic lights.
* Add a message queue to prevent data races, deadlocks and improve performance and responsibility of the program

### Structure:

The project is divided into different files. All header files can be found in the `include` folder.

* `src/graphics.cpp` (and header file): Logic for visualization of the traffic simulation
* `src/intersection.cpp` (and header file): Class for the intersection objects with the corresponding functions and logic
* `src/street.cpp` (and header file): Class for the streets connecting intersections
* `src/TrafficLight.cpp` (and header file): Class for the traffic light objects with the corresponding functions and logic
* `src/TrafficObject.cpp` (and header file): Parent class for TrafficLight, street, intersection and Vehicle
* `src/TrafficSimulator_Final.cpp`: Main logic of the traffic simulation
* `src/Vehicle.cpp` (and header file): Class for the vehicle objects with the corresponding functions and logic
* other helper, build and installation files

### Dependencies

* cmake >= 2.8
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
* OpenCV >= 4.1
* gcc/g++ >= 5.4

### Basic Build and Run Instructions

1. Clone this repository.
2. Install dependencies.
3. Make a build directory in the top level directory: `mkdir build && cd build`
4. Compile: `cmake .. && make`
5. Run it: `./traffic_simulation`.

# Results

Here you can see an example result:

<img src="data/traffic_simulation.gif"/>