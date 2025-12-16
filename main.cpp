#include "scheduler.h"
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter Arrival Time & Burst Time for P" << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    int contextSwitch = 1;
    int timeQuantum = 2;

    fcfs(processes, contextSwitch);
    sjfNonPreemptive(processes, contextSwitch);
    sjfPreemptive(processes, contextSwitch);
    roundRobin(processes, timeQuantum, contextSwitch);

    return 0;
}
