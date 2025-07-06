#include <stdio.h>

#define MAX_INPUTS 10
#define MAX_COMBINATIONS (1 << MAX_INPUTS)

int data[MAX_COMBINATIONS][MAX_INPUTS];
int targets[MAX_COMBINATIONS];

void generate_data(int n, int *total_samples) {
    int combinations = 1 << n;
    for (int i = 0; i < combinations; i++) {
        int or_result = 0;
        for (int j = 0; j < n; j++) {
            data[i][j] = (i >> (n - j - 1)) & 1;
            or_result |= data[i][j];
        }
        targets[i] = or_result;
    }
    *total_samples = combinations;
}

void print_table(int n, int total_samples) {
    printf("Truth Table with %d inputs for OR gate:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%c", 'A' + i);
    }
    printf("\tOutput(Y)\n");
    for (int i = 0; i < total_samples; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", data[i][j]);
        }
        printf("\t\t%d\n", targets[i]);
    }
}

void print_output(int n, int total_samples, float weights[], float bias) {
    printf("\nTruth Table with Learned Outputs (after training):\n");
    for (int i = 0; i < total_samples; i++) {
        float s = bias;
        for (int j = 0; j < n; j++) {
            s += weights[j] * data[i][j];
        }
        int out = s >= 0 ? 1 : 0;
        for (int j = 0; j < n; j++) {
            printf("%d", data[i][j]);
        }
        printf("\t%d\n", out);
    }
}

int main() {
    int n;
    printf("Enter the number of inputs for OR Gate: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX_INPUTS) {
        printf("Invalid number of inputs. Choose between 1 and %d.\n", MAX_INPUTS);
        return 1;
    }

    int total_samples;
    generate_data(n, &total_samples);
    print_table(n, total_samples);

    float weights[MAX_INPUTS] = {0};
    float bias = 0;
    float lr = 0.1;
    int epoch = 0, max_epochs = 100, converged = 0;

    while (epoch < max_epochs && !converged) {
        epoch++;
        int total_errors = 0;

        for (int i = 0; i < total_samples; i++) {
            float s = bias;
            for (int j = 0; j < n; j++) {
                s += weights[j] * data[i][j];
            }
            int output = s >= 0 ? 1 : 0;
            int error = targets[i] - output;

            if (error != 0) {
                total_errors++;
                for (int j = 0; j < n; j++) {
                    weights[j] += lr * error * data[i][j];
                }
                bias += lr * error;
            }
        }

        printf("Epoch %d: Total Errors = %d\n", epoch, total_errors);

        if (total_errors == 0) {
            converged = 1;
            printf("Training Converged!\n");
            printf("Final Weights: ");
            for (int i = 0; i < n; i++) {
                printf("%.2f ", weights[i]);
            }
            printf("\nFinal Bias: %.2f\n", bias);
            print_output(n, total_samples, weights, bias);
        }
    }

    if (!converged) {
        printf("Training did not converge within the maximum number of epochs.\n");
        printf("Final Weights: ");
        for (int i = 0; i < n; i++) {
            printf("%.2f ", weights[i]);
        }
        printf("\nFinal Bias: %.2f\n", bias);
    }

    return 0;
}
