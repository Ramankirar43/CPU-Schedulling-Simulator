#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

void fcfs(std::vector<Process> processes, int contextSwitch);
void sjfNonPreemptive(std::vector<Process> processes, int contextSwitch);
void sjfPreemptive(std::vector<Process> processes, int contextSwitch);
void roundRobin(std::vector<Process> processes, int timeQuantum, int contextSwitch);

void printResults(const std::string& algo, const std::vector<Process>& processes);

#endif
