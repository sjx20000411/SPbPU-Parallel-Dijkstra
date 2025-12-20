# SPbPU-Parallel-Dijkstra
### Correctness Baseline (Matlab)
 A sequential Dijkstra algorithm was implemented in Matlab with 1,000 nodes. The resulting shortest paths match the outputs of the parallel C/Python versions on the HPC, ensuring the logical correctness of the implementation.
##  Performance Results 
| Implementation  | Parallel Technology   | Max Threads/Procs  | Best Time   |
| :--- | :--- | :--- | :--- |
| **C & OpenMP** | Shared Memory   | 8 Threads | **0.1898 s** |
| **C & MPI** | Distributed  | 112 Processes | **0.6719 s** |
| **C & Pthreads** | Low-level   | 8 Threads | **0.0004 s** |
| **Python & MPI** | Scripting  | 4 Processes | **0.1001 s** |

> **Analysis **: 

 OpenMP demonstrates the best speedup for 10,000 nodes. While MPI scales to 112 processes, it is limited by inter-node communication overhead.



https://github.com/user-attachments/assets/a20dc5a4-4fa9-47db-bd15-c4938381eafa



This video captures the real-time execution outputs of all algorithm versions on Tornado nodes.
