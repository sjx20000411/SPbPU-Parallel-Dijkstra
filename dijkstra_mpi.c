#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define INF 1000000000

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 2) {
        if (rank == 0) printf("Usage: mpirun -np <p> %s <file>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    int n, m;
    int *adj = NULL;

   
    FILE *file = NULL;
    if (rank == 0) {
        file = fopen(argv[1], "r");
        if (!file) { perror("Error opening file"); MPI_Abort(MPI_COMM_WORLD, 1); }
        fscanf(file, "%d %d", &n, &m);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

   
    adj = (int*)malloc(n * n * sizeof(int));
    for (int i = 0; i < n * n; i++) adj[i] = (i / n == i % n) ? 0 : INF;

    if (rank == 0) {
        int u, v, w;
        for (int i = 0; i < m; i++) {
            fscanf(file, "%d %d %d", &u, &v, &w);
            if (u < n && v < n) adj[u * n + v] = w;
        }
        fclose(file);
    }
  
    MPI_Bcast(adj, n * n, MPI_INT, 0, MPI_COMM_WORLD);

 
    int start_v = (n / size) * rank;
    int end_v = (rank == size - 1) ? n : (n / size) * (rank + 1);

    int *dist = (int*)malloc(n * sizeof(int));
    int *visited = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) dist[i] = adj[0 * n + i]; // 假设源点为 0
    visited[0] = 1;

    double startTime = MPI_Wtime();

    for (int count = 1; count < n; count++) {
        struct { int d; int v; } local_min, global_min;
        local_min.d = INF; local_min.v = -1;

        for (int i = start_v; i < end_v; i++) {
            if (!visited[i] && dist[i] < local_min.d) {
                local_min.d = dist[i];
                local_min.v = i;
            }
        }

      
        MPI_Allreduce(&local_min, &global_min, 1, MPI_2INT, MPI_MINLOC, MPI_COMM_WORLD);

        if (global_min.v == -1) break;
        visited[global_min.v] = 1;

     
        for (int i = start_v; i < end_v; i++) {
            if (!visited[i] && dist[i] > global_min.d + adj[global_min.v * n + i]) {
                dist[i] = global_min.d + adj[global_min.v * n + i];
            }
        }
    }

    double endTime = MPI_Wtime();

    if (rank == 0) {
        printf("MPI (Nodes: %d, Processes: %d) Time: %f s\n", n, size, endTime - startTime);
    }

    free(adj); free(dist); free(visited);
    MPI_Finalize();
    return 0;
}
