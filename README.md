# Advanced CPU Scheduling Simulator

## Overview
This project implements core CPU scheduling algorithms used in operating systems,
including preemptive scheduling and context switching overhead simulation.

## Algorithms Implemented
- FCFS (First Come First Serve)
- SJF (Non-Preemptive)
- SJF (Preemptive / Shortest Remaining Time First)
- Round Robin

## Features
- Arrival time handling
- Burst and remaining time tracking
- Context switching overhead simulation
- Waiting time and turnaround time computation
- Performance comparison of scheduling policies

## How to Run
```bash
g++ main.cpp scheduler.cpp -o scheduler
./scheduler
