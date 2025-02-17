// includes zone of CMD.C
#include <windows.h>
#include <stdio.h>
#include "prototypes.h"
// end of includes

/*
Version and root directory
*/
char version[] = "1.0.0"; // Subsystem version
char kVer[] = "1.0.01A"; // Kernel version
char rootDir[] = ".\\rootDir\\J";  // Root directory for it to start on the proper endDir and limit itself to only create and edit files with the rootDir[] as ROOTDISK

/*
char variables
*/
extern char currentDir[256];
extern char formattedPath[256];

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

char osimsg[] =
    "Subsystem version: %s \n" // variable in version[256]
    "Windows Version: WIN11 Targeted |\\ NT |\\ \n" // local Windows variable
    "Kernel Logic Version: %s \n" // variable in kVer[256]
    "Version Channel: NULL\n";

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
    print("HLT \\n\n");
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
}

void clearScreen () {
    system("cls");
}

void OSInfo(){
    printf(osimsg, version, kVer);
}

/**
 * @brief Main function of the program.
 * 
 * Initializes the subsystem, displays a welcome message, and starts the shell.
 * 
 * @return integer = `0` status of the program.
 */
int main() {
    initSubsystem();
    printf("Welcome to J %s", version);
    startShell();
    return 0;
}