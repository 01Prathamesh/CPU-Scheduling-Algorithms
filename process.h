#include <iostream>
#include <vector>
#include <algorithm> // For std::sort
using namespace std;
//header Guard to prevent multiple inclusion
#ifndef PROCESS_H
#define PROCESS_H




enum class state {
    READY,
    RUNNING,
    WAITING,
    TERMINATE
};

static int pid = 1;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time; // For preemptive algorithms
    int remaining_burst_time; // Added to track remaining burst time
    int priority;       // For priority scheduling
    int waiting_time = 0;
    int turnaround_time = 0;

    bool operator==(const Process &other) const {
        return id == other.id; // or any other comparison criteria that makes sense
    }
};


vector<Process> processes;

void create_process(int a_t, int b_t) {
    if (a_t < 0 || b_t <= 0) {
        cout << "Invalid Arrival Time or Burst Time!" << endl;
        return;
    }
    Process p;
    p.id = pid++;
    p.arrival_time = a_t;
    p.burst_time = b_t;
    p.remaining_time = b_t; // Initialize remaining_time
    processes.push_back(p);

    cout << "Process ID=" << p.id << "\n"
         << "Arrival Time=" << p.arrival_time << "\n"
         << "Burst Time=" << p.burst_time << "\n\n";
}

void create() {
    int a;
    cout << "How many Processes do you have?\n";
    cin >> a;
    processes.clear(); // Clear any existing processes

    vector<int> arrival_times(a);
    vector<int> burst_times(a);

    cout << "Type the Arrival time of Process one by one.\n";
    for (int i = 0; i < a; ++i) {
        cin >> arrival_times[i];
    }

    cout << "Type the Burst Time of Process one by one in the same order as the arrival time.\n";
    for (int i = 0; i < a; ++i) {
        cin >> burst_times[i];
    }

    for (int i = 0; i < a; ++i) {
        create_process(arrival_times[i], burst_times[i]);
    }
}

#endif // PROCESS_H
//header Guard (end)to prevent multiple inclusion