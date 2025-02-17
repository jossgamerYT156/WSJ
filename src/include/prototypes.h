#ifndef PROTOTYPES_H
#define PROTOTYPES_H
#include <windows.h>


//defines Section
// necessary define for JSH
#define COMMAND_COUNT (sizeof(commands) / sizeof(commands[0]))

// end of defines section

char version[256];
char formattedPath[256];
/*
char variables
*/
char currentDir[256];
char formattedPath[256];

//Function prototypes
// moving through the FS
void changeDirectory(const char *path);

// file management function prototypes
extern void makeDirectory(const char *dirname);
extern void makeFile(const char *filename);
extern void removeFile(const char *filename);
extern void removeDirectory(const char *dirname);

// path stuff
extern void openFile(const char *filename);
extern void listFiles();
extern void printCurrentDirectory();
extern void updateFormattedPath(char *formattedPath);

// process based logic
extern void createProcessAndTrack(const char *exePath);
extern void addProcess(HANDLE hProcess, HANDLE hThread, DWORD processID);
extern void terminateAllProcesses();
extern void exitCommand(const char *args);

extern void showHelp();
extern void OSInfo();
extern void clearScreen();

#endif