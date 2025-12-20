# SPbPU-Parallel-Dijkstra
### 3. Performance Results / 

| Implementation  | Parallel Technology   | Max Threads/Procs  | Best Time   |
| :--- | :--- | :--- | :--- |
| **C & OpenMP** | Shared Memory   | 8 Threads | **0.1898 s** |
| **C & MPI** | Distributed  | 112 Processes | **0.6719 s** |
| **C & Pthreads** | Low-level   | 8 Threads | **0.0004 s** |
| **Python & MPI** | Scripting  | 4 Processes | **0.1001 s** |

> **Analysis **: 

> - **EN**: OpenMP demonstrates the best speedup for 10,000 nodes. While MPI scales to 112 processes, it is limited by inter-node communication overhead.
### 4. Project Demo Video / 演示视频

<div align="center">
  <video src="[这里粘贴你刚才复制的链接](https://github.com/sjx20000411/SPbPU-Parallel-Dijkstra/releases/download/v1.0/tm5u40@login1_.2025-12-20.18-07-10.mp4)" controls width="80%">
    Your browser does not support the video tag.
  </video>
  
  <p>
    <strong>[CN]</strong> 如果视频无法加载，请 <a href="[这里粘贴你刚才复制的链接](https://github.com/sjx20000411/SPbPU-Parallel-Dijkstra/releases/download/v1.0/tm5u40@login1_.2025-12-20.18-07-10.mp4)">点击此处直接下载观看</a>。<br>
    <strong>[EN]</strong> If the video fails to load, please <a href="[这里粘贴你刚才复制的链接](https://github.com/sjx20000411/SPbPU-Parallel-Dijkstra/releases/download/v1.0/tm5u40@login1_.2025-12-20.18-07-10.mp4)">click here to download and watch</a>.
  </p>
</div>
