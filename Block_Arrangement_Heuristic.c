#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 100

void print_state(char state[][10], int n) {
    printf("State: ");
    for (int i = 0; i < n; i++) {
        printf("%s ", state[i]);
    }
    printf("\n");
}

int misplaced_blocks(char state[][10], char goal[][10], int n) {
    int misplaced = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(state[i], goal[i]) != 0) {
            misplaced++;
        }
    }
    return misplaced;
}

int distance_between_blocks(char state[][10], char goal[][10], int n) {
    int distance = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (strcmp(state[i], goal[j]) == 0) {
                distance += abs(i - j);
                break;
            }
        }
    }
    return distance;
}

int heuristic(char state[][10], char goal[][10], int n) {
    return misplaced_blocks(state, goal, n) + distance_between_blocks(state, goal, n);
}

int main() {
    int n;
    char initial_state[MAX_BLOCKS][10];
    char goal_state[MAX_BLOCKS][10];

    printf("Enter the number of blocks: ");
    scanf("%d", &n);

    printf("Enter the initial state of the blocks (space or comma-separated):\n");
    getchar(); // consume newline
    char initial_input[1000];
    fgets(initial_input, sizeof(initial_input), stdin);
    for (int i = 0; i < strlen(initial_input); i++) {
        if (initial_input[i] == ',')
            initial_input[i] = ' ';
    }
    int count1 = 0;
    char *token = strtok(initial_input, " \n");
    while (token != NULL && count1 < n) {
        strcpy(initial_state[count1++], token);
        token = strtok(NULL, " \n");
    }

    printf("Enter the goal state of the blocks (space or comma-separated):\n");
    char goal_input[1000];
    fgets(goal_input, sizeof(goal_input), stdin);
    for (int i = 0; i < strlen(goal_input); i++) {
        if (goal_input[i] == ',')
            goal_input[i] = ' ';
    }
    int count2 = 0;
    token = strtok(goal_input, " \n");
    while (token != NULL && count2 < n) {
        strcpy(goal_state[count2++], token);
        token = strtok(NULL, " \n");
    }

    if (count1 != n || count2 != n) {
        printf("Error: The state should contain exactly %d blocks.\n", n);
        return 1;
    }

    printf("\nInitial State:\n");
    print_state(initial_state, n);
    printf("Goal State:\n");
    print_state(goal_state, n);

    int h = heuristic(initial_state, goal_state, n);
    printf("Heuristic (misplaced + distance): %d\n", h);

    return 0;
}
