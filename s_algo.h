#include <iostream>
#include <vector>
#include <algorithm> // For std::sort
#include"process.h"
using namespace std;
//header Guard to prevent multiple inclusion
#ifndef S_ALGO_H
#define S_ALGO_H



void FCFS() {
    cout << "\nYou Choose FCFS\n";
    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrival_time < b.arrival_time;
    });

    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (auto &p : processes) {
        if (current_time < p.arrival_time) {
            current_time = p.arrival_time; // Wait until the process arrives
        }
        p.waiting_time = current_time - p.arrival_time;
        p.turnaround_time = p.waiting_time + p.burst_time;

        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;

        cout << "Process ID=" << p.id << "\n"
             << "Start Time=" << current_time << "\n"
             << "Completion Time=" << (current_time + p.burst_time) << "\n"
             << "Waiting Time=" << p.waiting_time << "\n"
             << "Turnaround Time=" << p.turnaround_time << "\n\n";
        current_time += p.burst_time;
    }

    int n = processes.size();
    cout << "Average Waiting Time: " << (float)total_waiting_time / n << "\n";
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << "\n";
}


void SJF() {
    cout << "\nYou Choose SJF\n";
    // Sort processes by burst time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.burst_time < b.burst_time;
    });

    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (auto &p : processes) {
        if (current_time < p.arrival_time) {
            current_time = p.arrival_time; // Wait until the process arrives
        }
        p.waiting_time = current_time - p.arrival_time;
        p.turnaround_time = p.waiting_time + p.burst_time;

        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;

        cout << "Process ID=" << p.id << "\n"
             << "Start Time=" << current_time << "\n"
             << "Completion Time=" << (current_time + p.burst_time) << "\n"
             << "Waiting Time=" << p.waiting_time << "\n"
             << "Turnaround Time=" << p.turnaround_time << "\n\n";
        current_time += p.burst_time;
    }

    int n = processes.size();
    cout << "Average Waiting Time: " << (float)total_waiting_time / n << "\n";
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << "\n";
}


void LJF() {
    cout << "\nYou Choose LJF\n";
    // Sort processes by burst time in descending order
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.burst_time > b.burst_time;
    });

    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (auto &p : processes) {
        if (current_time < p.arrival_time) {
            current_time = p.arrival_time; // Wait until the process arrives
        }
        p.waiting_time = current_time - p.arrival_time;
        p.turnaround_time = p.waiting_time + p.burst_time;

        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;

        cout << "Process ID=" << p.id << "\n"
             << "Start Time=" << current_time << "\n"
             << "Completion Time=" << (current_time + p.burst_time) << "\n"
             << "Waiting Time=" << p.waiting_time << "\n"
             << "Turnaround Time=" << p.turnaround_time << "\n\n";
        current_time += p.burst_time;
    }

    int n = processes.size();
    cout << "Average Waiting Time: " << (float)total_waiting_time / n << "\n";
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << "\n";
}


void RR() {
    int quantum;
    cout << "\nEnter the time quantum for RR scheduling:\n";
    cin >> quantum;

    cout << "\nYou Chose RR\n";
    int current_time = 0;
    vector<Process> queue = processes;
    vector<Process> remaining_processes = processes; // Copy to handle remaining times

    // Initialize waiting and turnaround times to 0
    for (auto &p : remaining_processes) {
        p.waiting_time = 0;
        p.turnaround_time = 0;
    }

    while (!queue.empty()) {
        Process p = queue.front();
        queue.erase(queue.begin());

        int execution_time = min(p.burst_time, quantum);
        if (current_time < p.arrival_time) {
            current_time = p.arrival_time; // Wait until the process arrives
        }
        // Update the waiting time and turnaround time
        for (auto &proc : remaining_processes) {
            if (proc.id == p.id) {
                proc.waiting_time = current_time - proc.arrival_time;
                proc.turnaround_time = proc.waiting_time + p.burst_time;
                break;
            }
        }

        current_time += execution_time;

        // If the process still needs more time, push it to the end of the queue
        if (p.burst_time > quantum) {
            p.burst_time -= quantum;
            queue.push_back(p);
        }
    }

    // Output process details at the end
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int n = processes.size();

    cout << "\nProcess details:\n";
    for (const auto &p : remaining_processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;

        cout << "Process ID=" << p.id << "\n"
             << "Arrival Time=" << p.arrival_time << "\n"
             << "Burst Time=" << p.burst_time << "\n"
             << "Waiting Time=" << p.waiting_time << "\n"
             << "Turnaround Time=" << p.turnaround_time << "\n\n";
    }

    cout << "Average Waiting Time: " << (float)total_waiting_time / n << "\n";
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << "\n";
}


void SRTF() {
    cout << "\nYou Chose SRTF\n";

    // Initialize variables
    int current_time = 0;
    int completed = 0;
    int n = processes.size();
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Create a copy of processes and initialize remaining_time
    vector<Process> proc_queue = processes;
    for (auto &p : proc_queue) {
        p.remaining_time = p.burst_time;
    }
    // Sort by arrival time
    sort(proc_queue.begin(), proc_queue.end(), [](const Process &a, const Process &b) {
        return a.arrival_time < b.arrival_time;
    });

    // Main scheduling loop
    while (completed < n) {
        // Find the process with the shortest remaining time
        Process* current_process = nullptr;
        for (auto &p : proc_queue) {
            if (p.arrival_time <= current_time && p.remaining_time > 0 &&
                (current_process == nullptr || p.remaining_time < current_process->remaining_time)) {
                current_process = &p;
            }
        }

        if (current_process != nullptr) {
            // Execute the process for 1 time unit
            current_process->remaining_time--;
            current_time++;

            // Check if the process is completed
            if (current_process->remaining_time == 0) {
                completed++;
                current_process->turnaround_time = current_time - current_process->arrival_time;
                current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;

                // Display process details
                cout << "Process ID=" << current_process->id << "\n"
                     << "Start Time=" << (current_time - current_process->burst_time) << "\n"
                     << "Completion Time=" << current_time << "\n"
                     << "Waiting Time=" << current_process->waiting_time << "\n"
                     << "Turnaround Time=" << current_process->turnaround_time << "\n\n";

                total_waiting_time += current_process->waiting_time;
                total_turnaround_time += current_process->turnaround_time;
            }
        } else {
            // No process is ready to execute; advance time
            current_time++;
        }
    }

    // Output average metrics at the end
    cout << "Average Waiting Time: " << (float)total_waiting_time / n << "\n";
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << "\n";
}

void LRTF() {
    cout << "\nYou Chose LRTF\n";

    // Initialize variables
    int current_time = 0;
    int completed = 0;
    int n = processes.size();
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Create a copy of processes and initialize remaining_time
    vector<Process> proc_queue = processes;
    for (auto &p : proc_queue) {
        p.remaining_time = p.burst_time;
    }

    // Main scheduling loop
    while (completed < n) {
        // Find the process with the longest remaining time
        Process* current_process = nullptr;
        for (auto &p : proc_queue) {
            if (p.arrival_time <= current_time && p.remaining_time > 0 &&
                (current_process == nullptr || p.remaining_time > current_process->remaining_time)) {
                current_process = &p;
            }
        }

        if (current_process != nullptr) {
            // Execute the process for 1 time unit
            current_process->remaining_time--;
            current_time++;

            // Check if the process is completed
            if (current_process->remaining_time == 0) {
                completed++;
                current_process->turnaround_time = current_time - current_process->arrival_time;
                current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;

                // Display process details
                cout << "Process ID=" << current_process->id << "\n"
                     << "Start Time=" << (current_time - current_process->burst_time) << "\n"
                     << "Completion Time=" << current_time << "\n"
                     << "Waiting Time=" << current_process->waiting_time << "\n"
                     << "Turnaround Time=" << current_process->turnaround_time << "\n\n";

                total_waiting_time += current_process->waiting_time;
                total_turnaround_time += current_process->turnaround_time;
            }
        } else {
            // No process is ready to execute; advance time
            current_time++;
        }
    }

    // Output average metrics at the end
    cout << "Average Waiting Time: " << (float)total_waiting_time / n << "\n";
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << "\n";
}


void PriorityScheduling() {
    cout << "\nYou Chose Priority Scheduling (Non-Preemptive)\n";

    // Initialize variables
    int current_time = 0;
    int completed = 0;
    int n = processes.size();
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Create a copy of processes and initialize remaining_time
    vector<Process> proc_queue = processes;
    for (auto &p : proc_queue) {
        p.remaining_time = p.burst_time;
    }

    // Sort processes by arrival time
    sort(proc_queue.begin(), proc_queue.end(), [](const Process &a, const Process &b) {
        return a.arrival_time < b.arrival_time;
    });

    vector<Process> ready_queue;

    while (completed < n) {
        // Add processes that have arrived by current_time to the ready_queue
        for (auto &p : proc_queue) {
            if (p.arrival_time <= current_time && p.remaining_time > 0 &&
                find(ready_queue.begin(), ready_queue.end(), p) == ready_queue.end()) {
                ready_queue.push_back(p);
            }
        }

        // Find the process with the highest priority
        Process* current_process = nullptr;
        for (auto &p : ready_queue) {
            if (p.remaining_time > 0 &&
                (current_process == nullptr || p.priority > current_process->priority)) {
                current_process = &p;
            }
        }

        if (current_process != nullptr) {
            // Execute the process
            current_time += current_process->burst_time;
            current_process->waiting_time = current_time - current_process->arrival_time - current_process->burst_time;
            current_process->turnaround_time = current_process->waiting_time + current_process->burst_time;
            completed++;

            // Display process details
            cout << "Process ID=" << current_process->id << "\n"
                 << "Start Time=" << (current_time - current_process->burst_time) << "\n"
                 << "Completion Time=" << current_time << "\n"
                 << "Waiting Time=" << current_process->waiting_time << "\n"
                 << "Turnaround Time=" << current_process->turnaround_time << "\n\n";

            total_waiting_time += current_process->waiting_time;
            total_turnaround_time += current_process->turnaround_time;

            // Remove the process from the ready queue
            ready_queue.erase(remove(ready_queue.begin(), ready_queue.end(), *current_process), ready_queue.end());
        } else {
            // No process is ready to execute; advance time
            current_time++;
        }
    }

    // Output average metrics at the end
    cout << "Average Waiting Time: " << (float)total_waiting_time / n << "\n";
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << "\n";
}


void PreemptivePriorityScheduling() {
    cout << "\nYou Chose Priority Scheduling (Preemptive)\n";

    // Initialize variables
    int current_time = 0;
    int completed = 0;
    int n = processes.size();
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Initialize remaining time for each process
    vector<Process> proc_queue = processes;
    for (auto &p : proc_queue) {
        p.remaining_time = p.burst_time;
    }

    // Sort by arrival time initially
    sort(proc_queue.begin(), proc_queue.end(), [](const Process &a, const Process &b) {
        return a.arrival_time < b.arrival_time;
    });

    vector<Process> ready_queue;
    Process* current_process = nullptr;

    while (completed < n) {
        // Add processes that have arrived by current_time to the ready_queue
        for (auto &p : proc_queue) {
            if (p.arrival_time <= current_time && p.remaining_time > 0 &&
                find(ready_queue.begin(), ready_queue.end(), p) == ready_queue.end()) {
                ready_queue.push_back(p);
            }
        }

        if (current_process != nullptr) {
            if (current_process->remaining_time == 0) {
                // Process is finished
                current_process->turnaround_time = current_time - current_process->arrival_time;
                current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;

                // Display process details
                cout << "Process ID=" << current_process->id << "\n"
                     << "Start Time=" << (current_time - current_process->burst_time) << "\n"
                     << "Completion Time=" << current_time << "\n"
                     << "Waiting Time=" << current_process->waiting_time << "\n"
                     << "Turnaround Time=" << current_process->turnaround_time << "\n\n";

                total_waiting_time += current_process->waiting_time;
                total_turnaround_time += current_process->turnaround_time;

                completed++;
                current_process = nullptr;
            }
        }

        // If no current process, choose a new one from the ready_queue
        if (current_process == nullptr && !ready_queue.empty()) {
            current_process = &(*max_element(ready_queue.begin(), ready_queue.end(), [](const Process &a, const Process &b) {
                return a.priority < b.priority; // Highest priority first
            }));

            // Remove the selected process from the ready_queue
            ready_queue.erase(remove(ready_queue.begin(), ready_queue.end(), *current_process), ready_queue.end());
        }

        if (current_process != nullptr) {
            // Execute the process for 1 time unit
            current_process->remaining_time--;
            current_time++;
        } else {
            // No process is ready to execute; advance time
            current_time++;
        }
    }

    // Output average metrics at the end
    cout << "Average Waiting Time: " << (float)total_waiting_time / n << "\n";
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << "\n";
}

void HRRN() {
    cout << "\nYou Chose HRRN Scheduling\n";

    // Initialize variables
    int current_time = 0;
    int completed = 0;
    int n = processes.size();
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Create a copy of processes and initialize remaining_time
    vector<Process> proc_queue = processes;
    for (auto &p : proc_queue) {
        p.remaining_time = p.burst_time;
    }
    // Sort by arrival time initially
    sort(proc_queue.begin(), proc_queue.end(), [](const Process &a, const Process &b) {
        return a.arrival_time < b.arrival_time;
    });

    vector<Process> ready_queue;

    while (completed < n) {
        // Add processes that have arrived by current_time to the ready_queue
        for (auto &p : proc_queue) {
            if (p.arrival_time <= current_time && p.remaining_time == 0) {
                p.remaining_time = p.burst_time;
                ready_queue.push_back(p);
            }
        }

        if (!ready_queue.empty()) {
            // Calculate response ratio for each process
            Process* current_process = nullptr;
            float highest_ratio = -1;
            for (auto &p : ready_queue) {
                float response_ratio = (float)(current_time - p.arrival_time + p.burst_time) / p.burst_time;
                if (response_ratio > highest_ratio) {
                    highest_ratio = response_ratio;
                    current_process = &p;
                }
            }

            if (current_process != nullptr) {
                // Execute the process
                current_process->remaining_time--;
                current_time++;

                if (current_process->remaining_time == 0) {
                    completed++;
                    current_process->turnaround_time = current_time - current_process->arrival_time;
                    current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;

                    // Display process details
                    cout << "Process ID=" << current_process->id << "\n"
                         << "Start Time=" << (current_time - current_process->burst_time) << "\n"
                         << "Completion Time=" << current_time << "\n"
                         << "Waiting Time=" << current_process->waiting_time << "\n"
                         << "Turnaround Time=" << current_process->turnaround_time << "\n\n";

                    total_waiting_time += current_process->waiting_time;
                    total_turnaround_time += current_process->turnaround_time;

                    // Remove the process from the ready queue
                    ready_queue.erase(remove(ready_queue.begin(), ready_queue.end(), *current_process), ready_queue.end());
                }
            }
        } else {
            // No process is ready to execute; advance time
            current_time++;
        }
    }

    // Output average metrics at the end
    cout << "Average Waiting Time: " << (float)total_waiting_time / n << "\n";
    cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << "\n";
}

void p_scheduler() {
    int a;
    cout << "\nWhich scheduling algorithm do you want to apply to these processes?\n 1)FCFS \t 2)SJF \t 3)LJF \t 4)RR \t 5)SRTF \t 6)LRTF \t 7)Priority (Non-Preemptive) \t 8)Priority (Preemptive) \t 9)HRRN \n";
    cin >> a;
    switch (a) {
        case 1: FCFS(); break;
        case 2: SJF(); break;
        case 3: LJF(); break;
        case 4: RR(); break;
        case 5: SRTF(); break;
        case 6: LRTF(); break;
        case 7: PriorityScheduling(); break;
        case 8: PreemptivePriorityScheduling(); break;
        case 9: HRRN(); break;
        default: cout << "Invalid Choice!!!"; break;
    }
}

#endif // S_ALGO_H
//header Guard (end)to prevent multiple inclusion