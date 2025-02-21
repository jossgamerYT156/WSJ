#include <windows.h>
#include <stdio.h>
#include "prototypes.h"


/**
* JUTILS module in module(CORE):
* the following code is part of the CORE structure of the J Subsystem Binary, this is IMPORTANT code that interacts with other parts of code like fs.c and cmd.c
* it is NOT recommended to delete parts of the following code, since it could result in a un-compilable source.
*/

// Multipurpose commands.

void listFiles() {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("*.*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        print("No files found.\n");
        return;
    }

    do {
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            printf("%s [dir]\n", findFileData.cFileName);
        } else {
            // Extract file extension (if any)
            char *ext = strrchr(findFileData.cFileName, '.');
            if (ext) {
                // Replace '.' with '\'
                *ext = '\\';
                printf("%s [file]\n", findFileData.cFileName);
            } else {
                printf("%s [file]\n", findFileData.cFileName);
            }
        }
    } while (FindNextFile(hFind, &findFileData));

    FindClose(hFind);
}

// Directory Logic

void makeDirectory(const char *dirname) {
    if (CreateDirectory(dirname, NULL)) {
        print("Directory created: ");
        print(dirname);
        print("\n");
    } else {
        print("Failed to create directory.\n ECOD: \n");
        printf("%d\n", GetLastError());
    }
}

void removeDirectory(const char *dirname) {
    if (RemoveDirectory(dirname)) {
        print("Directory removed: ");
        print(dirname);
        print("\n");
    } else {
        print("Failed to remove directory.\n ECOD: \n");
        printf("%d\n", GetLastError());
    }
}

// File Management

void makeFile(const char *filename) {
    HANDLE hFile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (hFile != INVALID_HANDLE_VALUE) {
        print("File created: ");
        print(filename);
        print("\n");
        CloseHandle(hFile);
    } else {
        print("Failed to create file.\n ECOD: \n");
        printf("%d\n", GetLastError());
    }
}

void removeFile(const char *filename) {
    if (DeleteFile(filename)) {
        print("File removed: ");
        print(filename);
        print("\n");
    } else {
        print("Failed to remove file.\n ECOD: \n");
        printf("%d\n", GetLastError());
    }
}

/*
end of module (CORE)
*/

/*
Windows Compatibility module (WINDOWS.WINUTILS.sysapp)

code following is the structure for opening files in Windows, and managing Windows interaction.
*/

// Windows interaction WINUTILS.WINDOWSUTILS.sysapp
int openFile(const char *filename) {
    // Translate `\` to `.`
    char translatedFilename[256];
    snprintf(translatedFilename, sizeof(translatedFilename), "%s", filename);

    // Find the last backslash to separate the filename and extension
    char *lastBackslash = strrchr(translatedFilename, '\\');
    if (lastBackslash) {
        // Replace the backslash with a dot
        *lastBackslash = '.';
    }

    // Better implementation of openFile made by user "len" via discord server: Le Official WGE Discord Server
    char *command = (char*)malloc(strlen(translatedFilename) + 6); // skip first `6` characters because of the "start " length
    sprintf(command, "start %s", translatedFilename); // call the command to open the file with variable filename provided by *command
    int result = system(command); // return the result of *command

    if (result != 0) { // if failure
        fprintf(stderr, "Failed to open file %s.\n ECODE: %d\n", translatedFilename, GetLastError()); // return the error code
        free(command); // and free the memory given to *command
        return 1; // return with error code 1
    }
    printf("File opened successfully.\n"); // if success, we tell the user
    free(command); // we free the memory given to *command
    return 0; // return error code 0 (success)
}

/*
end of WINDOWS compatibility module : WINUTILS.WINDOWSUTILS.sysapp :
*/