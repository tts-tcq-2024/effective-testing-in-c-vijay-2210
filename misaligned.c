#include <stdio.h>
#include <assert.h>
#include <string.h>

// Buffer to capture the output
#define BUFFER_SIZE 4096
char capturedOutput[BUFFER_SIZE];

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[j]);
        }
    }
    return i * j;
}

int main() {
    char buffer[1000] = {0};
    int result = printColorMap();
    
    const char* expectedMajorColors[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* expectedMinorColors[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    
    int position = 0;
    
    for (int majorIndex = 0; majorIndex < 5; majorIndex++) {
        for (int minorIndex = 0; minorIndex < 5; minorIndex++) {
            char expectedLine[50];
            snprintf(expectedLine, sizeof(expectedLine), "%d | %s | %s\n", position, expectedMajorColors[majorIndex], expectedMinorColors[minorIndex]);
            assert(strncmp(buffer + position * strlen(expectedLine), expectedLine, strlen(expectedLine)) == 0);
            
            position++;
        }
    }
    assert(result == 25);
    printf("All is well (maybe!)\n");
    return 0;
}
