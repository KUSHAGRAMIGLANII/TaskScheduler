# CpuScheduler
Cpu scheduling algorithms
First Come First Serve (FCFS)
First Come First Serve (FCFS) is a scheduling algorithm where the process that arrives first is executed first. It is simple and easy to understand, but it can lead to poor performance if there are processes with long burst times. FCFS does not prioritize processes, making it a non-preemptive algorithm. This means that once a process starts executing, it runs until completion. FCFS is commonly used in batch systems where the order of processes is important.

Round Robin with Varying Time Quantum (RR)
Round Robin (RR) with variable quantum is a scheduling algorithm that uses time-sharing to divide CPU time among processes. In this version of RR, the quantum (time slice) can be adjusted depending on the requirements of the processes. Shorter processes can be given smaller quanta and longer processes larger quanta. The algorithm maintains a queue of processes, where each process is given a quantum of time to execute. When a process's quantum expires, it is moved to the back of the queue. This helps to minimize the average waiting time and avoid starvation, where long processes prevent others from executing.

Shortest Job First (SJF)
Shortest Process Next (SJF) is a scheduling algorithm that executes processes based on their burst time, or the time needed to complete their task. It is a non-preemptive algorithm, meaning that once a process starts executing, it runs until completion. The process with the shortest burst time is executed first. This minimizes the average waiting time for processes but can cause longer running processes to be blocked by shorter ones.

Shortest Remaining Time First (SRTF)
Shortest Remaining Time Next (SRTF) is similar to SPN but is a preemptive algorithm. This means that a running process can be interrupted by a new process with a shorter remaining time. The process with the shortest remaining time is executed first. SRT adapts to changes in remaining time as processes execute, making it useful when burst times are not known in advance. This helps to minimize the average waiting time for processes.

Highest Response Ratio Next (HRRN)
Highest Response Ratio Next (HRRN) is a scheduling algorithm that prioritizes processes based on their response ratio. The response ratio is calculated as (waiting time + burst time) / burst time. The process with the highest response ratio is executed first. HRRN is non-preemptive, meaning that once a process starts executing, it runs until completion. This algorithm helps to minimize the average waiting time, especially for processes with long waiting times.

Multi Level Queue(MLQ)
MLQ is a scheduling algorithm that uses multiple priority queues to allocate CPU time based on priority levels. Processes with higher priority levels are executed first. When a process completes execution, it is moved to a lower priority queue. This algorithm is beneficial for handling a mix of short and long-running processes with varying priorities. It ensures that high-priority processes are executed first while still allowing low-priority processes to eventually be executed.

Multilevel Feedback Queue (MLFQ)
Multilevel Feedback Queue (MLFQ) is a complex scheduling algorithm that uses multiple queues with different priority levels. Processes can move between queues based on their behavior and CPU burst characteristics. Initially, a process starts in the highest priority queue. If it uses up its time quantum without finishing, it is moved to a lower priority queue. Processes in lower priority queues get larger time quanta. If a process in a lower queue does not finish, it remains in that queue or moves further down. This allows MLFQ to dynamically adjust priorities based on process behavior, providing a good balance between responsiveness and throughput.
