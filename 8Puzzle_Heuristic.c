#include <stdio.h>
#include <stdlib.h>

int manhattan(int state[], int goal[]) {
    int dist = 0;
    for (int i = 1; i <= 8; i++) {
        int stateIndex, goalIndex;
        for (int j = 0; j < 9; j++) {
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

void printPuzzle(int puzzle[]) {
    for (int i = 0; i < 9; i++) {
        printf("%d ", puzzle[i]);
        if ((i + 1) % 3 == 0)
            printf("\n");
    }
}

int main() {
    int state[9];
    int goal[9] = {1, 2, 3,
                   4, 5, 6,
                   7, 8, 0};

    printf("Enter the current state of the puzzle (0 for blank):\n");
    for (int i = 0; i < 9; i++) {
        if (scanf("%d", &state[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    printf("\nInput State:\n");
    printPuzzle(state);

    printf("\nGoal State:\n");
    printPuzzle(goal);

    int heuristic = manhattan(state, goal);
    printf("\nManhattan Distance Heuristic Value: %d\n", heuristic);

    return 0;
}
