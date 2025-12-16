# Advanced CPU Scheduling Simulator

## Overview
This project simulates core CPU scheduling algorithms used in operating systems.
It models real-world behavior including **preemption** and **context switching overhead**.

## Algorithms Implemented
- FCFS (First Come First Serve)
- SJF (Non-Preemptive)
- SJF (Preemptive / Shortest Remaining Time First)
- Round Robin

## Features
- Arrival time handling
- Burst & remaining time tracking
- Context switching overhead simulation
- Waiting time & turnaround time computation
- Performance comparison of scheduling policies

## How to Run
```bash
g++ main.cpp scheduler.cpp -o scheduler
./scheduler


## Sample Input
Number of processes: 3  
P1: Arrival=0 Burst=5  
P2: Arrival=1 Burst=3  
P3: Arrival=2 Burst=1  

## Sample Output
Displays completion time, waiting time, turnaround time, and averages for each scheduling algorithm.
