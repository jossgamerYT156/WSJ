#include <windows.h>
#include <stdio.h>

char version[] = "1.0.0";

void startShell() {
    char input[256];

    while (1) {
        print("\n> ");
        readInput(input, sizeof(input));
        input[strcspn(input, "\r\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            print("Exiting subsystem...\n");
            break;
        } else if (strcmp(input, "ls") == 0) {
            listFiles();
        } else {
            print("Unknown command: ");
            print(input);
            print("\n");
        }
    }
}

int main() {
    printf("Welcome to J %s", version);
    startShell();
    return 0;
}