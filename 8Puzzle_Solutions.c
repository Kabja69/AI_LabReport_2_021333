#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 9

int goal[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};

int manhattan(int state[]) {
    int dist = 0;
    for (int i = 1; i <= 8; i++) {
        int stateIndex, goalIndex;
        for (int j = 0; j < SIZE; j++) {
            if (state[j] == i)
                stateIndex = j;
            if (goal[j] == i)
                goalIndex = j;
        }
        int x1 = stateIndex / 3, y1 = stateIndex % 3;
        int x2 = goalIndex / 3, y2 = goalIndex % 3;
        dist += abs(x1 - x2) + abs(y1 - y2);
    }
    return dist;
}

void printPuzzle(int state[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", state[i]);
        if ((i + 1) % 3 == 0)
            printf("\n");
    }
}

void copyState(int dest[], int src[]) {
    for (int i = 0; i < SIZE; i++)
        dest[i] = src[i];
}

int generateSuccessors(int state[], int best_state[]) {
    int blank_index;
    for (int i = 0; i < SIZE; i++) {
        if (state[i] == 0) {
            blank_index = i;
            break;
        }
    }

    int row = blank_index / 3;
    int col = blank_index % 3;

    int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int min_dist = 1000;

    printf("Generating successors...\n");

    for (int i = 0; i < 4; i++) {
        int new_row = row + moves[i][0];
        int new_col = col + moves[i][1];
        if (new_row >= 0 && new_row < 3 && new_col >= 0 && new_col < 3) {
            int new_index = new_row * 3 + new_col;
            int new_state[SIZE];
            copyState(new_state, state);
            new_state[blank_index] = new_state[new_index];
            new_state[new_index] = 0;

            int dist = manhattan(new_state);

            printf("\nSuccessor:\n");
            printPuzzle(new_state);
            printf("Manhattan Distance: %d\n", dist);

            if (dist < min_dist) {
                min_dist = dist;
                copyState(best_state, new_state);
            }
        }
    }

    return min_dist;
}

int isGoal(int state[]) {
    for (int i = 0; i < SIZE; i++) {
        if (state[i] != goal[i])
            return 0;
    }
    return 1;
}

int main() {
    int state[SIZE];

    printf("Enter the initial state of the puzzle (0 for blank):\n");
    for (int i = 0; i < SIZE; i++) {
        if (scanf("%d", &state[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    if (isGoal(state)) {
        printf("Puzzle Already Solved!\n");
        return 0;
    }

    while (!isGoal(state)) {
        int next_state[SIZE];
        int h = generateSuccessors(state, next_state);

        printf("\nBest State Chosen:\n");
        printPuzzle(next_state);

        copyState(state, next_state);

        if (isGoal(state)) {
            printf("Puzzle Solved!\n");
            break;
        }
    }

    return 0;
}
