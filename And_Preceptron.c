#include <stdio.h>
#include <math.h>

#define MAX_INPUTS 10
#define MAX_COMBINATIONS 1024

int data[MAX_COMBINATIONS][MAX_INPUTS];
int targets[MAX_COMBINATIONS];
int total_data;

void generate_data(int n) {
    total_data = (int)pow(2, n);
    for (int i = 0; i < total_data; i++) {
        int all_ones = 1;
        for (int j = 0; j < n; j++) {
            data[i][n - j - 1] = (i >> j) & 1;
            if (data[i][n - j - 1] == 0)
                all_ones = 0;
        }
        targets[i] = all_ones ? 1 : 0;
    }
}

void print_table(int n) {
    printf("Truth Table with %d inputs for AND gate:\n", n);
    for (int i = 0; i < n; i++)
        printf("%c", 'A' + i);
    printf("\tOutput(Y)\n");
    for (int i = 0; i < total_data; i++) {
        for (int j = 0; j < n; j++)
            printf("%d", data[i][j]);
        printf("\t\t%d\n", targets[i]);
    }
}

void print_learned_output(float weights[], float bias, int n) {
    printf("\nTruth Table with Learned Outputs (after training):\n");
    for (int i = 0; i < total_data; i++) {
        float sum = bias;
        for (int j = 0; j < n; j++)
            sum += weights[j] * data[i][j];
        int output = sum >= 0 ? 1 : 0;

        for (int j = 0; j < n; j++)
            printf("%d", data[i][j]);
        printf("\t%d\n", output);
    }
}

int main() {
    int n;
    printf("Enter the number of inputs for AND Gate: ");
    scanf("%d", &n);

    if (n > MAX_INPUTS) {
        printf("Maximum number of inputs supported is %d\n", MAX_INPUTS);
        return 1;
    }

    generate_data(n);
    print_table(n);

    float weights[MAX_INPUTS] = {0};
    float bias = 0;
    float lr = 0.1f;

    int epoch = 0, max_epochs = 100;
    int converged = 0;

    while (epoch < max_epochs && !converged) {
        epoch++;
        int total_errors = 0;

        for (int i = 0; i < total_data; i++) {
            float sum = bias;
            for (int j = 0; j < n; j++)
                sum += weights[j] * data[i][j];

            int output = sum >= 0 ? 1 : 0;
            int error = targets[i] - output;

            if (error != 0) {
                total_errors++;
                for (int j = 0; j < n; j++)
                    weights[j] += lr * error * data[i][j];
                bias += lr * error;
            }
        }

        printf("Epoch %d: Total Errors = %d\n", epoch, total_errors);
        if (total_errors == 0) {
            converged = 1;
            printf("Training Converged!\n");
            printf("Final Weights: ");
            for (int i = 0; i < n; i++)
                printf("%.2f ", weights[i]);
            printf("\nFinal Bias: %.2f\n", bias);
            print_learned_output(weights, bias, n);
        }
    }

    if (!converged) {
        printf("Training did not converge within the maximum number of epochs.\n");
        printf("Final Weights: ");
        for (int i = 0; i < n; i++)
            printf("%.2f ", weights[i]);
        printf("\nFinal Bias: %.2f\n", bias);
    }

    return 0;
}
