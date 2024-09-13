# CPU-Scheduling-Algorithms
CPU Scheduling Algorithms
This repository contains a collection of CPU scheduling algorithms implemented in C++. The project demonstrates a variety of scheduling techniques and provides an interactive command-line interface for users to input processes and choose different scheduling algorithms.

Algorithms Implemented:
*First-Come, First-Served (FCFS): A basic scheduling algorithm where processes are executed in the order they arrive.

*Shortest Job First (SJF): An algorithm that selects the process with the shortest burst time next.

*Longest Job First (LJF): An algorithm that selects the process with the longest burst time next.

*Round Robin (RR): A preemptive scheduling algorithm where each process is assigned a fixed time quantum and cycles through the queue.

*Shortest Remaining Time First (SRTF): A preemptive version of SJF where the process with the shortest remaining time is selected next.

*Longest Remaining Time First (LRTF): A preemptive algorithm that selects the process with the longest remaining time.

*Priority Scheduling (Non-Preemptive): Processes are selected based on their priority. Higher priority processes are executed first.

*Priority Scheduling (Preemptive): A preemptive version of priority scheduling where the current process can be interrupted if a higher priority process arrives.

*Highest Response Ratio Next (HRRN): A non-preemptive algorithm that selects processes based on their response ratio, which considers waiting time and burst time.



Features:
*Interactive User Input: Allows users to specify the number of processes, their arrival times, burst times, and scheduling algorithm preferences.

*Detailed Output: Provides detailed scheduling metrics including start time, completion time, waiting time, and turnaround time for each process, along with average waiting and turnaround times.


Usage:
*Clone the repository: git clone <repository-url>
Compile the code using a C++ compiler.
Run the executable and follow the prompts to input process details and select a scheduling algorithm.


Contributing:
Feel free to contribute by adding new scheduling algorithms, improving the user interface, or enhancing the code structure.

License:
This project is licensed under the MIT License - see the LICENSE file for details.
