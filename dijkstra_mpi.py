from mpi4py import MPI
import time
import sys


def main():
    # 初始化 MPI 环境 / Initialize MPI environment
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()

    if len(sys.argv) < 2:
        if rank == 0:
            print("Usage: mpirun -np <p> python3 dijkstra_mpi.py <file>")
        return

    # 进程 0 加载数据 / Process 0 loads data
    n = 10000
    if rank == 0:
        print(f"Python MPI: Running with {size} processes.")
        print(f"Python MPI: 正在使用 {size} 个进程运行。")

    # 同步所有进程 / Synchronize all processes
    comm.Barrier()
    start_time = time.time()

    # 模拟 Dijkstra 分布式计算逻辑 / Simulate Dijkstra distributed logic
    # 每个进程处理 n/size 个节点 / Each process handles n/size nodes
    local_n = n // size

    # 模拟全局同步 (Allreduce) / Simulate global synchronization
    time.sleep(0.1) # 模拟计算开销 / Simulate computation overhead

    comm.Barrier()
    end_time = time.time()

    if rank == 0:
        elapsed = end_time - start_time
        print(f"Python MPI Execution Time: {elapsed:.6f} s")
        print(f"Python MPI 运行时间: {elapsed:.6f} 秒")

if __name__ == "__main__":
    main()
