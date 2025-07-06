#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define N_SAMPLES 12
#define N_FEATURES 4
#define K 3
#define MAX_ITERS 100

double data[N_SAMPLES][N_FEATURES] = {
    {1.0, 1.5, 0.8, 1.2},
    {1.2, 1.7, 0.9, 1.1},
    {1.1, 1.4, 0.7, 1.3},
    {1.3, 1.6, 0.85,1.15},
    {4.0, 4.5, 3.8, 4.2},
    {4.2, 4.7, 3.9, 4.1},
    {4.1, 4.4, 3.7, 4.3},
    {4.3, 4.6, 3.85,4.15},
    {2.0, 2.2, 1.8, 2.1},
    {2.1, 2.3, 1.9, 2.0},
    {4.5, 4.8, 4.0, 4.4},
    {4.4, 4.9, 3.95,4.35}
};

int assignments[N_SAMPLES];
double centroids[K][N_FEATURES];
double new_centroids[K][N_FEATURES];

double dist(const double *a, const double *b) {
    double s = 0;
    for (int i = 0; i < N_FEATURES; i++) {
        double d = a[i] - b[i];
        s += d * d;
    }
    return sqrt(s);
}

int main() {
    srand(42);
    int used[N_SAMPLES] = {0};
    for (int j = 0; j < K; j++) {
        int idx;
        do { idx = rand() % N_SAMPLES; } while (used[idx]);
        used[idx] = 1;
        memcpy(centroids[j], data[idx], sizeof data[0]);
    }

    int iter;
    for (iter = 0; iter < MAX_ITERS; iter++) {
        for (int i = 0; i < N_SAMPLES; i++) {
            double best_d = 1e300;
            int best_j = 0;
            for (int j = 0; j < K; j++) {
                double d = dist(data[i], centroids[j]);
                if (d < best_d) {
                    best_d = d;
                    best_j = j;
                }
            }
            assignments[i] = best_j;
        }

        int counts[K] = {0};
        memset(new_centroids, 0, sizeof new_centroids);

        for (int i = 0; i < N_SAMPLES; i++) {
            int c = assignments[i];
            counts[c]++;
            for (int f = 0; f < N_FEATURES; f++)
                new_centroids[c][f] += data[i][f];
        }

        for (int j = 0; j < K; j++) {
            if (counts[j] > 0)
                for (int f = 0; f < N_FEATURES; f++)
                    new_centroids[j][f] /= counts[j];
            else
                memcpy(new_centroids[j], centroids[j], sizeof centroids[j]);
        }

        int converged = 1;
        for (int j = 0; j < K; j++)
            for (int f = 0; f < N_FEATURES; f++)
                if (fabs(new_centroids[j][f] - centroids[j][f]) > 1e-6)
                    converged = 0;

        memcpy(centroids, new_centroids, sizeof centroids);

        if (converged) {
            printf("Converged at iteration %d\n", iter + 1);
            break;
        }
    }

    printf("\nFinal cluster assignments:\n");
    for (int i = 0; i < N_SAMPLES; i++)
        printf("Sample %2d: Cluster %d\n", i, assignments[i]);

    printf("\nFinal centroid positions:\n");
    for (int j = 0; j < K; j++) {
        printf("Centroid %d: ", j);
        for (int f = 0; f < N_FEATURES; f++)
            printf("%.4f ", centroids[j][f]);
        printf("\n");
    }

    double wcss = 0;
    for (int i = 0; i < N_SAMPLES; i++) {
        int c = assignments[i];
        double d = dist(data[i], centroids[c]);
        wcss += d * d;
    }
    printf("\nWithin‑Cluster Sum of Squares (WCSS): %.4f\n", wcss);

    return 0;
}
