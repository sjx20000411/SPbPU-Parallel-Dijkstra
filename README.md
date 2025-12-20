# SPbPU-Parallel-Dijkstra
###  Performance Results / 

| Implementation  | Parallel Technology   | Max Threads/Procs  | Best Time   |
| :--- | :--- | :--- | :--- |
| **C & OpenMP** | Shared Memory   | 8 Threads | **0.1898 s** |
| **C & MPI** | Distributed  | 112 Processes | **0.6719 s** |
| **C & Pthreads** | Low-level   | 8 Threads | **0.0004 s** |
| **Python & MPI** | Scripting  | 4 Processes | **0.1001 s** |

> **Analysis **: 

> - **EN**: OpenMP demonstrates the best speedup for 10,000 nodes. While MPI scales to 112 processes, it is limited by inter-node communication overhead.

