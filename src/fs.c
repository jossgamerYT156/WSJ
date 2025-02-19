// the FileSystem Handler for Windows Subsystem J

#include <windows.h>
#include <stdio.h>
#include "prototypes.h"
/**
* @brief Formatting function for JPATH, it formats the Windows' default path \dir\subdir\subdir\file.something to [root].dir.subdir.subdir.file\something
* @param formattedPath The formatted path to update
* @param path the source path.
*/
void formatPath(char *formattedPath, const char *path) {
    char tempPath[256];
    snprintf(tempPath, sizeof(tempPath), "%s", path);

    // Convert all `\` to `.`
    for (int i = 0; tempPath[i] != '\0'; i++) {
        if (tempPath[i] == '\\') {
            tempPath[i] = '.';
        }
    }

    if (strcmp(path, ROOT_DIR) == 0) {
        snprintf(formattedPath, 256, "[root]. "); // Format path with [root]
    } else {
        snprintf(formattedPath, 256, "[root].%s", tempPath); // Format path with [root] and proper `.` separator
    }
}

/*
Function to STAT the current directory using the variable currentDir and automatically format it with JPATH format.
*/
void printCurrentDirectory() {
    char formattedPath[256];
    formatPath(formattedPath, currentDir);
    print(formattedPath);
    print("\n");
    return formattedPath;
}

void updateFormattedPath(char *formattedPath) { 
    // Call formatPath to properly update formattedPath with dot separators
    formatPath(formattedPath, currentDir);  // formatPath already ensures the path is correct
    if (formattedPath[0] == '.') {
        // If the formattedPath starts with [root], remove any unnecessary leading dot
        memmove(formattedPath, formattedPath + 1, strlen(formattedPath));
    }

    // Check if formatting was successful (no errors)
    if (formattedPath[0] == '\0') {
        printf("Failed to update path format\n");
    }
}

void changeDirectory(const char *path) {
    // Handle `cd <<` to go back one directory level
    if (strcmp(path, "<<") == 0) {
        // Split currentDir by the `.` separator (converted from backslashes)
        char *lastDot = strrchr(currentDir, '.');
        if (lastDot) {
            *lastDot = '\0';  // Remove the last part after the last dot, going back one directory
        }

        // Ensure we don't go above ROOT_DIR
        if (strcmp(currentDir, "") == 0) {
            strcpy(currentDir, ROOT_DIR);
        }

        // Update the formattedPath to reflect this change visually
        formatPath(formattedPath, currentDir);
        print("Changed directory to: ");
        print(formattedPath);
        print("\n");
    } else if (strcmp(path, "\\") == 0 || strcmp(path, "/") == 0) {
        // If the path is the root directory, set currentDir to ROOT_DIR
        strcpy(currentDir, ROOT_DIR);
        SetCurrentDirectory(ROOT_DIR);
        formatPath(formattedPath, currentDir);
        print("Changed directory to: ");
        print(formattedPath);
        print("\n");
    } else {
        // Handle normal directory change
        if (SetCurrentDirectory(path)) {
            GetCurrentDirectory(sizeof(currentDir), currentDir);  // Get full path

            // Find the start of the relevant path inside ROOT_DIR
            char *relativePath = strstr(currentDir, ROOT_DIR);
            if (relativePath) {
                relativePath += strlen(ROOT_DIR); // Move past "rootDir\J"
                if (*relativePath == '\\') relativePath++;  // Remove extra `\`
            } else {
                relativePath = currentDir;  // If not inside ROOT_DIR, keep full path
            }

            // Update the currentDir to only hold the relative path
            strcpy(currentDir, relativePath);

            // Update formatted path (convert `\` to `.`)
            formatPath(formattedPath, currentDir);

            print("Changed directory to: ");
            print(formattedPath);
            print("\n");
        } else {
            print("Failed to change directory. \nECOD: \n");
            printf("%d\n", GetLastError());
        }
    }
}