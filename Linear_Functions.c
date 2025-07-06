#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SAMPLES 10
#define FEATURES 3
#define EPOCHS 100
#define ALPHA 0.01

double true_function(double x1, double x2, double x3) {
    return 2 * x1 + 3 * x2 - x3 + 5;
}

int main() {
    srand(42);

    double X[SAMPLES][FEATURES];
    double y_true[SAMPLES];

    for (int i = 0; i < SAMPLES; i++) {
        for (int j = 0; j < FEATURES; j++) {
            X[i][j] = (double)rand() / RAND_MAX;
        }
        y_true[i] = true_function(X[i][0], X[i][1], X[i][2]);
    }

    double w[FEATURES], b;
    for (int i = 0; i < FEATURES; i++) w[i] = (double)rand() / RAND_MAX * 2 - 1;
    b = (double)rand() / RAND_MAX * 2 - 1;

    for (int epoch = 1; epoch <= EPOCHS; epoch++) {
        double total_error = 0;
        printf("\nEpoch %d: Weights => w1=%.4f, w2=%.4f, w3=%.4f, bias=%.4f\n", epoch, w[0], w[1], w[2], b);

        for (int i = 0; i < SAMPLES; i++) {
            double x1 = X[i][0], x2 = X[i][1], x3 = X[i][2];
            double target = y_true[i];

            double y_pred = w[0] * x1 + w[1] * x2 + w[2] * x3 + b;
            double error = target - y_pred;
            total_error += error * error;

            w[0] += ALPHA * error * x1;
            w[1] += ALPHA * error * x2;
            w[2] += ALPHA * error * x3;
            b += ALPHA * error;

            printf("Sample %d: x1=%.3f, x2=%.3f, x3=%.3f, target=%.3f, pred=%.3f, error=%.3f\n", i, x1, x2, x3, target, y_pred, error);
            printf("         Updated weights => w1=%.4f, w2=%.4f, w3=%.4f, bias=%.4f\n", w[0], w[1], w[2], b);
        }

        double mse = total_error / SAMPLES;
        printf("Epoch %d MSE: %.6f\n", epoch, mse);
        if (mse < 1e-6) {
            printf("\nStopping early due to very low error.\n");
            break;
        }
    }

    printf("\nFinal weights: w1=%.4f, w2=%.4f, w3=%.4f, bias=%.4f\n", w[0], w[1], w[2], b);
    return 0;
}
