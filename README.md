# Lunar-Lander-Mimic

## Description
A terminal-based version of the classic [Lunar Lander](http://moonlander.seb.ly/) game that takes in multiple landers and input to manage each one of them. The goal of the original game is to successfully land one's lander by tilting and accelerating to slow one's velocity down to comfortably land on a rough surface. In my implementation, there is no rotation, but the thrust and flow rate are used to keep the lander(s) afloat and land safely.

## Functionality
As there are multiple landers being simulated at once, I utilized my own implementation of a priority queue to keep track of the properties of the different landers. This also allowed me to overload the "<" operator and utilize it to maintain the minheap structure of the priority queue.

## Usage
By downloading main.cpp, priority.cpp, priority.h, lander.cpp, lander.h, LanderInput.txt, and Simulation.txt, one could simply compile using GCC and the command "g++ main.cpp lander.cpp" followed by "./a.out < Simulation.txt". This will run the simulation, and, if desired, one could change the values in Simulation.txt and see the response of the program (the input values must remain between 0 and 1).

The Simulation.txt file takes the format of:
LanderName flow_rate
where 0 <= flow_rate <= 1

I would recommend playing the original game to better visualize this implementation, keeping in mind that there are multiple landers playing at once in my program.
