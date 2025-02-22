#include <windows.h>
#include <stdio.h>

#include "prototypes.h"
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
    {"hlt", exitCommand}, // hlt directive taken from ASM `hlt` instruction, this itself being the same as UNIX's `exit` command.
    {"ls", (void (*)(const char *))listFiles}, // taken from UNIX-General List(ls) command.
    {"hlp", showHelp}, // simple help command, added just because we could, same as Linux's manpages.    
    {"osi", OSInfo}, // OS Information about J and target Windows version, like neofetch, but worse and more basic.
    
    // Directory interaction
    {"cd", changeDirectory}, // same as any UNIX cd command.
    {"mkd", makeDirectory}, // taken from UNIX mkdir command, abvreviated to mkd for fast typing.
    {"rmd", removeDirectory}, // taken from Linux's rm -rf directive, avreviated to rmd for fast typing and ease of understanding
    {"pwd", printCurrentDirectory}, // taken from Linux, added for ease of understanding and pairity.
    {"pcd", printCurrentDirectory}, // same as PWD, J-Formatted Command/Logic avreviation.
    {"dir", (void (*)(const char *))listFiles}, // taken from Windows, added for ease of understanding and pairity.

    // windows interaction
    {"open", openFile}, // Windows interaction, added so Lilly could avoid packing a version of Vim or any other program and use Windows' defaults
    {"clt", clearScreen}, // to avoid CMD cluttering
    
    // file interaction
    {"mkf", makeFile}, // taken from UNIX touch command, abvreviated to mkf for fast typing and ease of understanding
    {"rmf", removeFile}, // taken from UNIX rm command, abvreviated to rmf for fast typing and ease of understanding
    

    // todo: process logic
    {"cproc", createProcessAndTrack}, // TODO: Create a process and track it
    {"cchproc", createChildProcess}, // TODO: Create a child process
    {"killall", terminateAllProcesses}, // TODO: terminate all processes
    {"addproc", addProcess}, // TODO: add a process to the process list
};

void startShell() {
    char input[2256];
    char formattedPath[256]; // Ensure formattedPath is in the correct scope

    while (1) {
        updateFormattedPath(formattedPath);  // Update the formattedPath based on currentDir
        printf("\n%s \\> ", formattedPath);  // Print the updated formattedPath
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

        print("Unknown command: "); // if the command is not found within commandList, print this message.
        print(cmd); // then we call the prompt again.
        print("\n");

        next:;
    }
}
