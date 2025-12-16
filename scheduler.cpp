#include "scheduler.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

void printResults(const string& algo, const vector<Process>& processes) {
    double totalWT = 0, totalTAT = 0;

    cout << "\n--- " << algo << " ---\n";
    cout << "PID  AT  BT  CT  WT  TAT\n";

    for (const auto& p : processes) {
        cout << p.pid << "   "
             << p.arrivalTime << "   "
             << p.burstTime << "   "
             << p.completionTime << "   "
             << p.waitingTime << "   "
             << p.turnaroundTime << "\n";

        totalWT += p.waitingTime;
        totalTAT += p.turnaroundTime;
    }

    cout << fixed << setprecision(2);
    cout << "Average Waiting Time: " << totalWT / processes.size() << endl;
    cout << "Average Turnaround Time: " << totalTAT / processes.size() << endl;
}

// ---------------- FCFS ----------------
void fcfs(vector<Process> processes, int contextSwitch) {
    sort(processes.begin(), processes.end(),
         [](auto& a, auto& b) { return a.arrivalTime < b.arrivalTime; });

    int time = 0;

    for (auto& p : processes) {
        if (time < p.arrivalTime)
            time = p.arrivalTime;

        time += p.burstTime;
        p.completionTime = time;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
        time += contextSwitch;
    }

    printResults("FCFS", processes);
}

// ---------------- SJF (Non-Preemptive) ----------------
void sjfNonPreemptive(vector<Process> processes, int contextSwitch) {
    int time = 0, completed = 0, n = processes.size();
    vector<bool> done(n, false);

    while (completed < n) {
        int idx = -1, minBT = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].arrivalTime <= time &&
                processes[i].burstTime < minBT) {
                minBT = processes[i].burstTime;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += processes[idx].burstTime;
        processes[idx].completionTime = time;
        processes[idx].turnaroundTime =
            processes[idx].completionTime - processes[idx].arrivalTime;
        processes[idx].waitingTime =
            processes[idx].turnaroundTime - processes[idx].burstTime;

        done[idx] = true;
        completed++;
        time += contextSwitch;
    }

    printResults("SJF (Non-Preemptive)", processes);
}

// ---------------- SJF (Preemptive / SRTF) ----------------
void sjfPreemptive(vector<Process> processes, int contextSwitch) {
    int time = 0, completed = 0, n = processes.size();
    int lastPid = -1;

    for (auto& p : processes)
        p.remainingTime = p.burstTime;

    while (completed < n) {
        int idx = -1, minRT = 1e9;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time &&
                processes[i].remainingTime > 0 &&
                processes[i].remainingTime < minRT) {
                minRT = processes[i].remainingTime;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        if (lastPid != -1 && lastPid != processes[idx].pid)
            time += contextSwitch;

        processes[idx].remainingTime--;
        time++;
        lastPid = processes[idx].pid;

        if (processes[idx].remainingTime == 0) {
            processes[idx].completionTime = time;
            processes[idx].turnaroundTime =
                time - processes[idx].arrivalTime;
            processes[idx].waitingTime =
                processes[idx].turnaroundTime - processes[idx].burstTime;
            completed++;
        }
    }

    printResults("SJF (Preemptive / SRTF)", processes);
}

// ---------------- Round Robin ----------------
void roundRobin(vector<Process> processes, int tq, int contextSwitch) {
    queue<int> q;
    int time = 0, completed = 0, n = processes.size();

    for (auto& p : processes)
        p.remainingTime = p.burstTime;

    vector<bool> inQueue(n, false);

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && processes[i].arrivalTime <= time &&
                processes[i].remainingTime > 0) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if (q.empty()) {
            time++;
            continue;
        }

        int idx = q.front();
        q.pop();

        int exec = min(tq, processes[idx].remainingTime);
        processes[idx].remainingTime -= exec;
        time += exec;

        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && processes[i].arrivalTime <= time &&
                processes[i].remainingTime > 0) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if (processes[idx].remainingTime > 0) {
            q.push(idx);
        } else {
            processes[idx].completionTime = time;
            processes[idx].turnaroundTime =
                time - processes[idx].arrivalTime;
            processes[idx].waitingTime =
                processes[idx].turnaroundTime - processes[idx].burstTime;
            completed++;
        }

        time += contextSwitch;
    }

    printResults("Round Robin", processes);
}
