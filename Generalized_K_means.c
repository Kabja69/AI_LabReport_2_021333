#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N_SAMPLES 12
#define N_FEATURES 4
#define K 3
#define MAX_ITERS 100

double data[N_SAMPLES][N_FEATURES] = {
    {1.0, 1.5, 0.8, 1.2},
    {1.2, 1.7, 0.9, 1.1},
    {1.1, 1.4, 0.7, 1.3},
    {1.3, 1.6, 0.85, 1.15},
    {4.0, 4.5, 3.8, 4.2},
    {4.2, 4.7, 3.9, 4.1},
    {4.1, 4.4, 3.7, 4.3},
    {4.3, 4.6, 3.85, 4.15},
    {2.0, 2.2, 1.8, 2.1},
    {2.1, 2.3, 1.9, 2.0},
    {4.5, 4.8, 4.0, 4.4},
    {4.4, 4.9, 3.95, 4.35}
};

double centroids[K][N_FEATURES];
int cluster_assignments[N_SAMPLES];

double distance(double *a, double *b, int n) {
    double sum = 0.0;
    for(int i=0; i<n; i++) {
        double diff = a[i] - b[i];
        sum += diff*diff;
    }
    return sqrt(sum);
}

void copy_point(double *src, double *dest, int n) {
    for(int i=0; i<n; i++) {
        dest[i] = src[i];
    }
}

int main() {
    srand(42);
    int chosen_indices[K] = {-1, -1, -1};
    int selected = 0;

    while(selected < K) {
        int idx = rand() % N_SAMPLES;
        int unique = 1;
        for(int j=0; j<selected; j++) {
            if(chosen_indices[j] == idx) {
                unique = 0;
                break;
            }
        }
        if(unique) {
            chosen_indices[selected++] = idx;
        }
    }
    for(int i=0; i<K; i++) {
        copy_point(data[chosen_indices[i]], centroids[i], N_FEATURES);
    }

    for(int iter=0; iter<MAX_ITERS; iter++) {
        int changed = 0;
        for(int i=0; i<N_SAMPLES; i++) {
            double min_dist = distance(data[i], centroids[0], N_FEATURES);
            int cluster = 0;
            for(int c=1; c<K; c++) {
                double dist = distance(data[i], centroids[c], N_FEATURES);
                if(dist < min_dist) {
                    min_dist = dist;
                    cluster = c;
                }
            }
            if(cluster_assignments[i] != cluster) {
                changed = 1;
                cluster_assignments[i] = cluster;
            }
        }

        if(!changed) {
            printf("Converged at iteration %d\n", iter+1);
            break;
        }

        for(int c=0; c<K; c++) {
            int count = 0;
            double sum[N_FEATURES] = {0};
            for(int i=0; i<N_SAMPLES; i++) {
                if(cluster_assignments[i] == c) {
                    for(int f=0; f<N_FEATURES; f++) {
                        sum[f] += data[i][f];
                    }
                    count++;
                }
            }
            if(count > 0) {
                for(int f=0; f<N_FEATURES; f++) {
                    centroids[c][f] = sum[f] / count;
                }
            }
        }
    }

    printf("Final cluster assignments:\n");
    for(int i=0; i<N_SAMPLES; i++) {
        printf("Sample %d: Cluster %d\n", i, cluster_assignments[i]);
    }

    printf("\nFinal centroid positions:\n");
    for(int c=0; c<K; c++) {
        printf("Centroid %d: ", c);
        for(int f=0; f<N_FEATURES; f++) {
            printf("%.4f ", centroids[c][f]);
        }
        printf("\n");
    }

    double wcss = 0.0;
    for(int c=0; c<K; c++) {
        for(int i=0; i<N_SAMPLES; i++) {
            if(cluster_assignments[i] == c) {
                double dist_sq = 0.0;
                for(int f=0; f<N_FEATURES; f++) {
                    double diff = data[i][f] - centroids[c][f];
                    dist_sq += diff*diff;
                }
                wcss += dist_sq;
            }
        }
    }
    printf("\nWithin-Cluster Sum of Squares (WCSS): %.4f\n", wcss);

    return 0;
}
