// includes zone of CMD.C
#include <windows.h>
#include <stdio.h>
#include "prototypes.h"
// end of includes

/*
Version and root directory
*/
char version[] = "0.0.2 ALPHA:REL"; // Subsystem version
char kVer[] = "1.0.02 A:R"; // Kernel version
char rootDir[] = ".\\rootDir\\J";  // Root directory for it to start on the proper endDir and limit itself to only create and edit files with the rootDir[] as ROOTDISK

/*
char variables
*/
extern char currentDir[256];
extern char formattedPath[256];

char commandList[] = 
    "## Multipurpose commands:\n"
    "- `hlt`    : exits the JSH Terminal(CORE.JSH)\n"
    "- `cd`     : change directories to the specified path(CORE)\n"
    "## File Management:\n"
    "- `mkd`    : removes a directory of the specified path (core)\n"
    "- `rmd`    : remove directories from the specified path (CORE)\n"
    "- `mkf`    : make a file with the specified name and path (CORE)\n"
    "- `rmf`    : removes the specified file (CORE)\n"
    "- `ls`     : Lists the contents of currentDir[256] (core)\n"
    "- `pwd`    : (still on development) gets the current working directory(CORE)\n"
    "## Windows Interaction\n"
    "- `dir`    : same as `ls` (WINCOMPAT.WINDOWSUTILS.sysapp)\n"
    "- `open`   : Open a file/url/cmd-applet specified by the user (WINCOMPAT.WINDOWSUTILS.sysapp)\n"
    "- `clt`    : clears the terminal(WINDOWS.WINDOWSUTILS.sysapp)\n"
    "## Process Logic\n"
    "- `cproc`  : create process (CORE.TSKMGR)\n"
    "- `killall : kills all processes (CORE.TSKMGR)\n"
    "- `addproc : adds a process to the processlist(CORE.TSKMGR)\n"
    "## Fun Commands\n"
    "- `write`  : Writes characters to screen using `write \"sometext!\" (CORE.JLANG)\n"
    "- `wait`   : waits for a specified amount of time (CORE.JLANG)\n"
    "- `**`     : comment string (CORE.JLANG)\n"
    "- `jrun`   : runs a jlang-formatted script file (CORE.JLANG)\n"
//    "## TODO: \nProcess Logic\nASF (Advanced Scripting Functions)\nShared Process Management\nChild Processes Creation and Management\nJTM(the J Task Manager)\nJASMIAFE (J Advanced Script Management Implementation And Function Expansion)\n\n"
    "\n\n"
    "For a more detailed list of commands and more in-depth explanation, see the README.MD file inside https://github.com/jossgamerYT156/WSJ/blob/main/README.md\n"
    "Or the shipped README.MD file inside the WSJ Project Root Directory.\n"
    "\n\n"
    "LDS LLC 2021-2025 (c) ALL RIGHTS RESERVED\n";

char osimsg[] =
    "Subsystem version: %s \n" // variable in version[256]
    "Windows Version: WINDOWS Targeted |\\ NT BASE |\\ \n" // local Windows variable
    "Kernel Logic Version: %s \n" // variable in kVer[256]
    "Version Channel: NULL\n";

void haltDirective(const char *args) {
    print("HLT\0\n");
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
    char initialDir[] = "[root]. ";
    char currentDir = initialDir;
}

void showHelp(){
    printf("Available commands are: \n");
    printf(commandList);
}

void clearScreen () {
    updateFormattedPath(formattedPath);
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