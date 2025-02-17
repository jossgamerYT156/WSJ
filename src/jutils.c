#include <windows.h>
#include <stdio.h>
#include "prototypes.h"


/*
JUTILS module in module(CORE):
the following code is part of the CORE structure of the J Subsystem Binary, this is IMPORTANT code that interacts with other parts of code like fs.c and cmd.c
it is NOT recommended to delete parts of the following code, since it could result in a un-compilable source.
*/

// Multipurpose
/*
Just a function to list the files inside .|
*/
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
                printf("%s%s [file]\n", findFileData.cFileName, ext);
            } else {
                printf("%s [file]\n", findFileData.cFileName);
            }
        }
    } while (FindNextFile(hFind, &findFileData));

    FindClose(hFind);
}

// Dirs Logic
/*
Basic function to create a directory
*/
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

/*
Function to delete a specified directory, and output the action if completted with exit0, or exit1.
*/
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
/*
Basic function to create a empty file.
*/
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

/*
Basic function to remove a file
*/
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


/*
Function to open files using a fileName specified
*/
void openFile(const char *filename) {
    /* Build the command to open the file using the "start" command*/
    char command[512];
    snprintf(command, sizeof(command), "start %s", filename);

    /* Execute the command using system()*/
    int result = system(command);
    if (result == 0) {
        print("File opened successfully.\n");
    } else {
        print("Failed to open file.\n ECOD: \n");
        printf("%d\n", GetLastError());
    }
}

/*
end of WINDOWS compatibility module
*/