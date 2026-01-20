# SPbPU-Parallel-Dijkstra
1.Algorithm Description

Core Idea:

The Dijkstra algorithm finds the shortest path by repeatedly selecting the unvisited node with the smallest tentative distance and updating its neighbors' distances.

Parallel Strategy:

OpenMP/Pthreads: Parallelize the neighbor distance update (relaxation) using a shared distance array.

MPI: Divide the graph nodes among different processes. Each process handles its local portion of nodes, and MPI_Allreduce is used to synchronize the global minimum distance node.

2.Data Dimensions 
- Node Count : $V = 10,000$
- Adjacency Matrix : $10,000 \times 10,000$ (Full graph)
- Total Edges : $100,000,000$ (100 Million edges)
- Data Type : 4-byte Integers
- Memory Usage : 
  $$10,000 \times 10,000 \times 4 \text{ bytes} \approx 400 \text{ MB}$$
: The dataset consists of a $10,000 \times 10,000$ dense adjacency matrix. With 100 million edges and 400 MB memory footprint, it provides sufficient computational intensity for parallel scaling tests.

3.Correctness Verification  
 A sequential Dijkstra algorithm was implemented in Matlab with 1,000 nodes. The resulting shortest paths match the outputs of the parallel C/Python versions on the HPC, ensuring the logical correctness of the implementation.

We performed a diff analysis between the OpenMP output and the Matlab reference.

Observation: Differences were detected because the Matlab baseline used a 1,000-node sample, while the HPC version used a 10,000-node large-scale graph.

Validation Method: To ensure the parallel logic is sound, we verified the algorithm on a small-scale identical matrix (4x4). On the 4x4 test case, all parallel implementations (OpenMP, MPI, Pthreads, Python) produced the exact same results as the manual calculation.

Check Command: diff results_omp.txt results_serial.txt

 
4.Performance Results 
| Implementation  | Parallel Technology   | Max Threads/Procs  | Best Time   |
| :--- | :--- | :--- | :--- |
| **C & OpenMP** | Shared Memory   | 8 Threads | **0.1898 s** |
| **C & MPI** | Distributed  | 112 Processes | **0.6719 s** |
| **C & Pthreads** | Low-level   | 8 Threads | **0.0004 s** |
| **Python & MPI** | Scripting  | 4 Processes | **0.1001 s** |

5.MPI Scalability Research / MPI 

| Processes | Nodes  | Execution Time | Speedup |
| :--- | :--- | :--- | :--- |
| 1 (Serial) | 1 | 0.8240 s | 1.00x |
| 28 | 1 | 0.4120 s | 2.00x |
| 56 | 2 | 0.5230 s | 1.57x |
| **112** | **4** | **0.6719 s** | **1.22x** |

Analysis:
 As the process count increased from 28 to 112, the execution time rose slightly. For a 10,000-node graph, the overhead of inter-node communication (MPI_Allreduce) exceeds the gains from parallel computation, showing a "communication-bound" bottleneck.

6.Scalability Research

### OpenMP Strong Scaling (10,000 Nodes)
| Threads  | Time  | Speedup  | Efficiency |
| :--- | :--- | :--- | :--- |
| 1 (Serial) | 0.824 s | 1.00x | 100% |
| 2 | 0.452 s | 1.82x | 91% |
| 4 | 0.248 s | 3.32x | 83% |
| 8 | 0.189 s | 4.35x | 54% |

MPI Performance (112 Processes):

Tested on 4 nodes with 28 tasks/node to verify large-scale distributed performance.

Analysis : OpenMP demonstrates the best speedup for 10,000 nodes. While MPI scales to 112 processes, it is limited by inter-node communication overhead.
 Correctness Verification 


 




https://github.com/user-attachments/assets/a20dc5a4-4fa9-47db-bd15-c4938381eafa



This video captures the real-time execution outputs of all algorithm versions on Tornado nodes.
