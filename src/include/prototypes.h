#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <windows.h>

// defines Section
/**
 * @brief The Command count variable needed for our shell to get the number of commands in the prompt.
 * @category variables
 */
#define COMMAND_COUNT (sizeof(commands) / sizeof(commands[0]))

/** 
* @brief we define the root directory of the J subsystem here, change this to your own root directory.
* @category variables
* @note this is the default root directory for the J subsystem, not the root of your actual C: drive..
*/
#define ROOT_DIR "C:\\Users\\Lilly_Aizawa\\WSJ\\rootDir\\J"

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

/**
 * @brief The `wait` directive, used to wait for a specified amount of time.
 * @arg timeInSeconds `int` 1-9999
 * @returns void
 * @note This is a directive that is used to wait for a specified amount of time, it is used in the J subsystem's scripting language, J-LANG.
 */
extern void waitDirective(const char *args);

/**
 * @brief the `write` directive, used to write a string to console in UTF-8 format.
 * @arg args `char*` the string to write to console.
 * @returns void
 * @note This is a directive that is used to write a string to the console in UTF-8 format, it is used in the J subsystem's scripting language, J-LANG.
 */
extern void writeDirective(char args[]);

// moving through the FS
/**
 * @brief Changes the current directory to the specified path.
 * 
 * @param path The path to change to.
 * @returns void
 */
extern void changeDirectory(const char *path);

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
extern void makeFile(const char *pathandname);

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
extern int openDirective(const char *filename);

/**
 * @brief Lists the files in the current directory.
 */
extern void listFiles(const char *dir);

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

/** @brief Helper function to convert dot-separated paths back to backslash-separated paths.
 *  @param formattedPath: The path to remove `.` from and replace with `\`
 * 
 *  @returns void
 */
extern void convertDotToBackslash(char *formattedPath);

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

extern void createChildProcess();

/**
 * @brief Terminates all processes.
 */
extern void terminateAllProcesses();

/**
 * @brief Exits the command shell.
 * 
 * @param args Arguments passed to the exit command.
 */
extern void haltDirective(const char *args);

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

extern void startShell();

#endif