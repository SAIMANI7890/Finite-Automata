#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 1000
#define ASCII_SIZE 256

// Function to compute the Finite Automaton for the pattern
void computeFiniteAutomaton(char *pattern, int **finiteAutomaton) {
    int m = strlen(pattern);
    int state, x;

    // Initialize the finite automaton with all zeros
    for (state = 0; state <= m; state++) {
        for (x = 0; x < ASCII_SIZE; x++) {
            finiteAutomaton[state][x] = 0;
        }
    }

    // Fill in the transitions for the finite automaton
    for (state = 0; state <= m; state++) {
        for (x = 0; x < ASCII_SIZE; x++) {
            finiteAutomaton[state][x] = getNextState(pattern, m, state, x);
        }
    }
}

// Function to compute the next state in the Finite Automaton
int getNextState(char *pattern, int m, int state, int x) {
    // If the character matches the next character in the pattern, move to the next state
    if (state < m && x == pattern[state])
        return state + 1;

    int nextState, i;

    // Otherwise, find the longest prefix of the pattern that is also a suffix of the pattern[0...state-1]x
    for (nextState = state; nextState > 0; nextState--) {
        if (pattern[nextState - 1] == x) {
            for (i = 0; i < nextState - 1; i++) {
                if (pattern[i] != pattern[state - nextState + 1 + i])
                    break;
            }
            if (i == nextState - 1)
                return nextState;
        }
    }

    return 0;
}

// Function to search for the pattern in the text using the Finite Automaton
void searchPattern(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
	int i;
    int **finiteAutomaton = (int **)malloc((m + 1) * sizeof(int *));
    for (i = 0; i <= m; i++) 
	{
        finiteAutomaton[i] = (int *)malloc(ASCII_SIZE * sizeof(int));
    }

    computeFiniteAutomaton(pattern, finiteAutomaton);
	int j;
    int state = 0;
    for (j = 0; j < n; j++) {
        state = finiteAutomaton[state][(int)text[j]];
        if (state == m) {
            printf("Pattern found at index %d\n", j - m + 1);
        }
    }
	int k;
    for (k = 0; k <= m; k++) {
        free(finiteAutomaton[k]);
    }
    free(finiteAutomaton);
}

int main() {
    // Open the text file
    FILE *textFile = fopen("text.txt", "r");
    if (textFile == NULL) {
        perror("Error opening text file");
        return 1;
    }

    // Open the pattern file
    FILE *patternFile = fopen("pattern.txt", "r");
    if (patternFile == NULL) {
        perror("Error opening pattern file");
        fclose(textFile);
        return 1;
    }

    // Read text from the file
    char text[1000];
    fgets(text, sizeof(text), textFile);

    // Read pattern from the file
    char pattern[100];
    fgets(pattern, sizeof(pattern), patternFile);

    // Remove newline characters from text and pattern
    text[strcspn(text, "\n")] = '\0';
    pattern[strcspn(pattern, "\n")] = '\0';

    // Close the files
    fclose(textFile);
    fclose(patternFile);

    // Search for the pattern in the text
    searchPattern(text, pattern);

    return 0;
}

