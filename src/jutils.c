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
    char translatedDirname[256];
    snprintf(translatedDirname, sizeof(translatedDirname), "%s", dirname);

    // Replace '.' with '\'
    for (char *p = translatedDirname; *p; p++) {
        if (*p == '.') {
            *p = '\\';
        }
    }

    // Create directories recursively
    char *subdir = translatedDirname;
    while ((subdir = strchr(subdir, '\\')) != NULL) {
        *subdir = '\0';
        CreateDirectory(translatedDirname, NULL);
        *subdir = '\\';
        subdir++;
    }
    CreateDirectory(translatedDirname, NULL);
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        print("Directory already exists: ");
        print(translatedDirname);
        print("\n");
    } else if (GetLastError() == ERROR_PATH_NOT_FOUND) {
        print("Failed to create directory. Path not found.\n ECOD: \n");
        printf("%d\n", GetLastError());
    } else {
        print("Directory created: ");
        print(translatedDirname);
        print("\n");
    }
}

void removeDirectory(const char *dirname) {
    int recursive = 0;
    char translatedDirname[256];
    snprintf(translatedDirname, sizeof(translatedDirname), "%s", dirname);

    // Check for /rd argument
    if (strncmp(dirname, "/rd ", 4) == 0) {
        recursive = 1;
        snprintf(translatedDirname, sizeof(translatedDirname), "%s", dirname + 4);
    }

    // Replace '.' with '\'
    for (char *p = translatedDirname; *p; p++) {
        if (*p == '.') {
            *p = '\\';
        }
    }

    if (recursive) {
        // Remove directories recursively
        WIN32_FIND_DATA findFileData;
        char searchPath[512];
        snprintf(searchPath, sizeof(searchPath), "%s\\*", translatedDirname);
        HANDLE hFind = FindFirstFile(searchPath, &findFileData);

        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
                    char path[512];
                    snprintf(path, sizeof(path), "%s\\%s", translatedDirname, findFileData.cFileName);

                    if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        removeDirectory(path);
                    } else {
                        DeleteFile(path);
                    }
                }
            } while (FindNextFile(hFind, &findFileData));
            FindClose(hFind);
        }
    }

    // Update translatedDirname to remove trailing backslashes
    size_t len = strlen(translatedDirname);
    while (len > 0 && translatedDirname[len - 1] == '\\') {
        translatedDirname[--len] = '\0';
    }

    if (RemoveDirectory(translatedDirname)) {
        print("Directory removed: ");
        print(translatedDirname);
        print("\n");
    } else {
        print("Failed to remove directory.\n ECOD: \n");
        printf("%d\n", GetLastError());
    }
}

// File Management

void makeFile(const char *filename) {
    // Translate `\` to `.`
    char translatedFilename[256];
    snprintf(translatedFilename, sizeof(translatedFilename), "%s", filename);

    // Find the last backslash to separate the filename and extension
    char *lastBackslash = strrchr(translatedFilename, '\\');
    if (lastBackslash) {
        // Replace the backslash with a dot
        *lastBackslash = '.';
    }

    HANDLE hFile = CreateFile(translatedFilename, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (hFile != INVALID_HANDLE_VALUE) {
        print("File created: ");
        print(translatedFilename);
        print("\n");
        CloseHandle(hFile);
    } else {
        print("Failed to create file.\n ECOD: \n");
        printf("%d\n", GetLastError());
    }
}

void removeFile(const char *filename) {
    // Translate `\` to `.`
    char translatedFilename[256];
    snprintf(translatedFilename, sizeof(translatedFilename), "%s", filename);

    // Find the last backslash to separate the filename and extension
    char *lastBackslash = strrchr(translatedFilename, '\\');
    if (lastBackslash) {
        // Replace the backslash with a dot
        *lastBackslash = '.';
    }

    if (DeleteFile(translatedFilename)) {
        print("File removed: ");
        print(translatedFilename);
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

    // Better implementation of openFile made by user "lenanya" / https://github.com/lenanya | over Discord Server: "Le Official WGE Discord Server"
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