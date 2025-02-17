// kernel.c
#include <windows.h>
#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD processID;
} Process;

Process processList[MAX_PROCESSES];
int processCount = 0;

void addProcess(HANDLE hProcess, HANDLE hThread, DWORD processID) {
    if (processCount < MAX_PROCESSES) {
        processList[processCount].hProcess = hProcess;
        processList[processCount].hThread = hThread;
        processList[processCount].processID = processID;
        processCount++;
    } else {
        printf("Process list is full!\n");
    }
}

void terminateAllProcesses() {
    for (int i = 0; i < processCount; i++) {
        TerminateProcess(processList[i].hProcess, 1); // Forcefully terminate with exit code 1
        CloseHandle(processList[i].hProcess);
        CloseHandle(processList[i].hThread);
    }
    processCount = 0;  // Reset process count after termination
}

void createProcessAndTrack(const char *exePath) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES saAttr;
    HANDLE hStdoutRead, hStdoutWrite;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    // Set up the security attributes for the pipe
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // Create the pipe for stdout
    if (!CreatePipe(&hStdoutRead, &hStdoutWrite, &saAttr, 0)) {
        printf("CreatePipe failed. Error: %lu\n", GetLastError());
        return;
    }

    // Set up the STARTUPINFO structure for redirection
    si.cb = sizeof(si);
    si.hStdOutput = hStdoutWrite;
    si.hStdError = hStdoutWrite;
    si.dwFlags |= STARTF_USESTDHANDLES;

    // Create the process with the redirection
    if (CreateProcess(
        exePath,   // Application name (path to executable)
        NULL,      // Command line arguments (if any)
        NULL,      // Process security attributes
        NULL,      // Thread security attributes
        TRUE,      // Inherit handles
        0,         // Creation flags
        NULL,      // Environment (use parent)
        NULL,      // Current directory
        &si,       // Startup info
        &pi        // Process info
    ) == 0) {
        printf("CreateProcess failed. Error: %lu\n", GetLastError());
        return;
    }

    // Add the new process to the process list
    addProcess(pi.hProcess, pi.hThread, pi.dwProcessId);

    // Close the write end of the pipe, we're only reading from it
    CloseHandle(hStdoutWrite);

    // Optionally, read from the pipe here
    char buffer[512];
    DWORD bytesRead;
    while (ReadFile(hStdoutRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';  // Null terminate the string
        printf("Child process output: %s", buffer);  // Output the data from the child process
    }

    printf("Started process with PID: %lu\n", pi.dwProcessId);
}
