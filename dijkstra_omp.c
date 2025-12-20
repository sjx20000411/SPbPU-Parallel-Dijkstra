#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdbool.h>

#define INF 1e9

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // 1. 读取数据 (Read Graph Data)
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    int n, m;
    if (fscanf(file, "%d %d", &n, &m) != 2) return 1;

    // 分配内存 (Memory Allocation)
    int** adj = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        adj[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) adj[i][j] = (i == j) ? 0 : INF;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        if (fscanf(file, "%d %d %d", &u, &v, &w) == 3) {
            if (u < n && v < n) adj[u][v] = w;
        }
    }
    fclose(file);

    int* dist = (int*)malloc(n * sizeof(int));
    bool* visited = (bool*)malloc(n * sizeof(bool));

    // 2. 并行计算 (Parallel Calculation)
    double start_time = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = false;
    }
    dist[0] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        int min_val = INF;

        #pragma omp parallel
        {
            int local_min = INF;
            int local_u = -1;
            #pragma omp for
            for (int i = 0; i < n; i++) {
                if (!visited[i] && dist[i] < local_min) {
                    local_min = dist[i];
                    local_u = i;
                }
            }
            #pragma omp critical
            {
                if (local_min < min_val) {
                    min_val = local_min;
                    u = local_u;
                }
            }
        }

        if (u == -1) break;
        visited[u] = true;

        #pragma omp parallel for
        for (int v = 0; v < n; v++) {
            if (!visited[v] && adj[u][v] != INF) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }

    double end_time = omp_get_wtime();
    printf("Nodes: %d, Execution Time: %f seconds\n", n, end_time - start_time);

    // 输出前5个结果 (Print first 5 results)
    for(int i=0; i<5 && i<n; i++) printf("Distance to node %d: %d\n", i, dist[i]);

    return 0;
}
