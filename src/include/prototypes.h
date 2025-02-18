#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <windows.h>

// defines Section
/**
 * @brief The Command count variable needed for our shell to get the number of commands in the prompt.
 * @category variables
 */
#define COMMAND_COUNT (sizeof(commands) / sizeof(commands[0]))

// end of defines section

/**
 * @brief The current Sub-OS version value.
 * @category variables
 */
char version[256];

/**
 * @brief The current directory variable.
 * @category variables
 */
char currentDir[256];

/**
 * @brief The formatted path variable for the `formatPath();` function and others inside fs.c.
 * @category variables
 */
char formattedPath[256];

/**
 * @brief A list of available commands for users to write hlp and get a debrief on which commands exist.
 * @returns A string containing multiline markdown.
 */
extern char commandList[];

/**
 * @brief Simple message defining the Sub-OS version, Sub-OS kernel version, and target Windows version.
 * @returns A string containing multiline markdown.
 */
extern char osimsg[];

// Function prototypes

// moving through the FS
/**
 * @brief Changes the current directory to the specified path.
 * 
 * @param path The path to change to.
 */
void changeDirectory(const char *path);

// file management function prototypes
/**
 * @brief Creates a directory with the specified name.
 * 
 * @param dirname The name of the directory to create.
 */
extern void makeDirectory(const char *dirname);

/**
 * @brief Creates a file with the specified name.
 * 
 * @param filename The name of the file to create.
 */
extern void makeFile(const char *filename);

/**
 * @brief Removes the specified file.
 * 
 * @param filename The name of the file to remove.
 */
extern void removeFile(const char *filename);

/**
 * @brief Removes a directory with the specified name.
 * 
 * @param dirname The name of the directory to remove.
 */
extern void removeDirectory(const char *dirname);

// path stuff
/*
* @brief directive to open a file in the default application associated.
* EG: open file.txt will open file.txt in the default text editor.(Windows' notepad.exe)
* @param filename
*/
extern void openFile(const char *filename);

/**
 * @brief Lists the files in the current directory.
 */
extern void listFiles();

/**
 * @brief Prints the current directory.
 */
extern void printCurrentDirectory();

/**
 * @brief Updates the formatted path.
 * 
 * @param formattedPath The formatted path to update.
 */
extern void updateFormattedPath(char *formattedPath);

// process based logic
/**
 * @brief Creates a new process and tracks it.
 * 
 * @param exePath The path to the executable.
 */
extern void createProcessAndTrack(const char *exePath);

/**
 * @brief Adds a process to the process list.
 * 
 * @param hProcess The process handle.
 * @param hThread The thread handle.
 * @param processID The process ID.
 */
extern void addProcess(HANDLE hProcess, HANDLE hThread, DWORD processID);

/**
 * @brief Terminates all processes.
 */
extern void terminateAllProcesses();

/**
 * @brief Exits the command shell.
 * 
 * @param args Arguments passed to the exit command.
 */
extern void exitCommand(const char *args);

/**
 * @brief Initializes the subsystem by setting the initial directory.
 */
extern void initSubsystem();

/**
 * @brief Displays the help message with available commands.
 */
extern void showHelp();

/**
 * @brief Displays Target-OS/Sub-OS information.
 */
extern void OSInfo();

/**
 * @brief Clears the terminal screen to avoid cluttering.
 */
extern void clearScreen();

#endif