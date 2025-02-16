// includes zone of CMD.C
#include <windows.h>
#include <stdio.h>

// end of includes zone of CMD.C


/*
Version and root directory
*/
char version[] = "1.0.0";
char rootDir[] = ".\\rootDir\\J";  // Root directory setup

/*
char variables
*/
char currentDir[256];
char formattedPath[256];

/*
Huge list of commands for no reason at all other than actually being able to use the hlp command.
*/
char commandList[] = 
    "Multipurpose commands:\n"
    "- `cd`     : change directories to the specified path(CORE)\n"
    "File Management:\n"
    "- `mkd`    : removes a directory of the specified path (core)\n"
    "- `rmd`    : remove directories from the specified path (CORE)\n"
    "- `mkf`    : make a file with the specified name and path (CORE)\n"
    "- `rmf`    : removes the specified file (CORE)\n"
    "- `ls`     : Lists the contents of currentDir[256] (core)\n"
    "- `pwd`    : (still on development) gets the current working directory(CORE)\n"
    "Windows Interaction\n"
    "- `dir`    : same as `ls` (WINCOMPAT.WINDOWSUTILS.sysapp)\n"
    "- `open`   : Open a file specified by the user (WINCOMPAT.WINDOWSUTILS.sysapp)\n"
    "- `clt`    : clears the terminal(WINDOWS.WINDOWSUTILS.sysapp)\n"
    "Process Logic\n"
    "- `cproc`  : create process (CORE)\n"
    "- `killall : kills all processes (CORE)\n"
    "- `addproc : adds a process to the processlist(CORE)\n"
    "\n\n"
    "For a more detailed list of commands and more in-depth explanation, see the README.MD file inside https://www.github.com/josgamer_YT156/WSJ/README.md";

/*
Definition of the STRUCT array that holds the commands, NECESSARY for command processing*/
typedef struct {
    const char *name; // we hold the name variable
    void (*func)(const char *args); // so then we can call the void function that holds the command.
} Command;

//Function prototypes
// moving through the FS
void changeDirectory(const char *path);

// file management function prototypes
void makeDirectory(const char *dirname);
void makeFile(const char *filename);
void removeFile(const char *filename);
void removeDirectory(const char *dirname);

// path stuff
void openFile(const char *filename);
void listFiles();
void printCurrentDirectory();
void updateFormattedPath(char *formattedPath);

// process based logic
void createProcessAndTrack(const char *exePath);
void addProcess(HANDLE hProcess, HANDLE hThread, DWORD processID);
void terminateAllProcesses();

void exitCommand(const char *args) {
    print("Exiting subsystem...\n");
    exit(0);
}

void initSubsystem() {
    // Set the initial directory to rootDir
    if (!SetCurrentDirectory(rootDir)) {
        // Handle the error if the directory doesn't exist or can't be accessed
        fprintf(stderr, "Error: Could not set current directory to %s\n", rootDir);
        // You might want to exit the program here, or take other corrective action
        exit(1); // Example: Exit with an error code
    }
    strcpy(currentDir, rootDir); // Keep currentDir in sync (optional, but good practice)
}

void showHelp(){
    printf("Available commands are: \n");
    printf(commandList);
    printf("read the README.MD file to know each command's function in detail.\n");
}

void clearScreen () {
    system("cls");
}

// Define command table
Command commands[] = {
    {"exit", exitCommand},
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
    {"addproc", addProcess}
};

#define COMMAND_COUNT (sizeof(commands) / sizeof(commands[0]))

void startShell() {
    char input[256];

    while (1) {
        updateFormattedPath(formattedPath);  // Update the formattedPath based on currentDir
        printf("\n%s|-> ", formattedPath);
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

int main() {
    initSubsystem();
    printf("Welcome to J %s", version);
    startShell();
    return 0;
}
