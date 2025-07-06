#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_SAMPLES 100
#define MAX_FEATURES 10

float rand_float() {
    return (float)rand() / RAND_MAX;
}

float dot_product(float *a, float *b, int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; i++)
        sum += a[i] * b[i];
    return sum;
}

void generate_dataset(int n_features, int n_samples, float X[][MAX_FEATURES], float y[], float true_w[], float *true_b) {
    for (int i = 0; i < n_features; i++) {
        true_w[i] = (rand_float() * 2.0f) - 1.0f;
    }
    *true_b = 5.0f;
    for (int i = 0; i < n_samples; i++) {
        for (int j = 0; j < n_features; j++) {
            X[i][j] = rand_float();
        }
        y[i] = dot_product(X[i], true_w, n_features) + *true_b;
    }
}

void train_perceptron(float X[][MAX_FEATURES], float y[], int n_samples, int n_features, float learning_rate, int epochs, float weights[], float *bias) {
    for (int i = 0; i < n_features; i++) {
        weights[i] = ((float)rand() / RAND_MAX) * 2 - 1;
    }
    *bias = ((float)rand() / RAND_MAX) * 2 - 1;
    for (int epoch = 1; epoch <= epochs; epoch++) {
        float total_error = 0.0f;
        for (int i = 0; i < n_samples; i++) {
            float y_pred = dot_product(X[i], weights, n_features) + *bias;
            float error = y[i] - y_pred;
            total_error += error * error;
            for (int j = 0; j < n_features; j++) {
                weights[j] += learning_rate * error * X[i][j];
            }
            *bias += learning_rate * error;
        }
        float mse = total_error / n_samples;
        printf("Epoch %3d | MSE: %.6f\n", epoch, mse);
    }
}

int main() {
    srand(42);
    int samples = 10;
    {
        int n_features = 4;
        float X[MAX_SAMPLES][MAX_FEATURES];
        float y[MAX_SAMPLES];
        float true_w[MAX_FEATURES];
        float true_b;
        printf("\n--- Training Perceptron with n = %d Features ---\n", n_features);
        generate_dataset(n_features, samples, X, y, true_w, &true_b);
        printf("True weights: ");
        for (int i = 0; i < n_features; i++) {
            printf("%.4f ", true_w[i]);
        }
        printf(", True bias: %.4f\n", true_b);
        float weights[MAX_FEATURES];
        float bias;
        train_perceptron(X, y, samples, n_features, 0.01f, 100, weights, &bias);
        printf("\nLearned Weights: ");
        for (int i = 0; i < n_features; i++) {
            printf("%.4f ", weights[i]);
        }
        printf("\nLearned Bias: %.4f\n", bias);
    }
    {
        int n_features = 5;
        float X[MAX_SAMPLES][MAX_FEATURES];
        float y[MAX_SAMPLES];
        float true_w[MAX_FEATURES];
        float true_b;
        printf("\n--- Training Perceptron with n = %d Features ---\n", n_features);
        generate_dataset(n_features, samples, X, y, true_w, &true_b);
        printf("True weights: ");
        for (int i = 0; i < n_features; i++) {
            printf("%.4f ", true_w[i]);
        }
        printf(", True bias: %.4f\n", true_b);
        float weights[MAX_FEATURES];
        float bias;
        train_perceptron(X, y, samples, n_features, 0.01f, 100, weights, &bias);
        printf("\nLearned Weights: ");
        for (int i = 0; i < n_features; i++) {
            printf("%.4f ", weights[i]);
        }
        printf("\nLearned Bias: %.4f\n", bias);
    }
    return 0;
}
