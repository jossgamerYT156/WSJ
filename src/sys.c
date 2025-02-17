#include <windows.h>
#include <stdio.h>

#include "prototypes.h"

//defines Section
// necessary define for JSH
#define COMMAND_COUNT (sizeof(commands) / sizeof(commands[0]))
//end of defines section

char version[256];
char formattedPath[256];
/*
char variables
*/
char currentDir[256];
char formattedPath[256];

extern char commandList[];

/*
Definition of the STRUCT array that holds the commands, NECESSARY for command processing*/
typedef struct {
    const char *name; // we hold the name variable
    void (*func)(const char *args); // so then we can call the void function that holds the command with it's arguments(if any).
} Command;

// Define command table
Command commands[] = {
    {"hlt", exitCommand},
    {"ls", (void (*)(const char *))listFiles},
    {"cd", changeDirectory},
    {"mkd", makeDirectory},
    {"mkf", makeFile},
    {"rmf", removeFile},
    {"rmd", removeDirectory},
    {"pwd", printCurrentDirectory},
    {"dir", (void (*)(const char *))listFiles},
    {"hlp", showHelp},
    {"open", openFile},
    {"clt", clearScreen},
    {"cproc", createProcessAndTrack},
    {"killall", terminateAllProcesses},
    {"addproc", addProcess},
    {"osi", OSInfo},
    {"pcd", printCurrentDirectory}
};

void startShell() {
    char input[256];
    char formattedPath[256]; // Ensure formattedPath is in the correct scope

    while (1) {
        updateFormattedPath(formattedPath);  // Update the formattedPath based on currentDir
        printf("\n%s|-> ", formattedPath);  // Print the updated formattedPath
        readInput(input, sizeof(input));
        input[strcspn(input, "\r\n")] = 0; // Trim newline

        // Extract command name
        char *cmd = strtok(input, " ");
        char *args = strtok(NULL, "");

        if (!cmd) continue;

        // Lookup command
        for (size_t i = 0; i < COMMAND_COUNT; i++) {
            if (strcmp(cmd, commands[i].name) == 0) {
                commands[i].func(args ? args : "");
                goto next;
            }
        }

        print("Unknown command: ");
        print(cmd);
        print("\n");

        next:;
    }
}
