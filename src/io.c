// the command I/O handler for Windows Subsystem J
#include <windows.h>
#include <stdio.h>

void print(const char *message) {
    DWORD written;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), message, strlen(message), &written, NULL);
}

void readInput(char *buffer, DWORD size) {
    DWORD bytesRead;
    ReadFile(GetStdHandle(STD_INPUT_HANDLE), buffer, size - 1, &bytesRead, NULL);
    buffer[bytesRead] = '\0';  // Null-terminate input
}
