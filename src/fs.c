// the FileSystem Handler for Windows Subsystem J

#include <windows.h>
#include <stdio.h>
#include "prototypes.h"

/**
 * @brief Formatting function for JPATH, it formats the Windows' default path \dir\subdir\subdir\file.something to [root].dir.subdir.subdir.file\something
 * @param formattedPath The formatted path to update
 * @param path the source path.
 */
void formatPath(char *formattedPath, const char *path)
{
    char tempPath[256];
    snprintf(tempPath, sizeof(tempPath), "%s", path);

    // Convert all `\` to `.`
    for (int i = 0; tempPath[i] != '\0'; i++)
    {
        if (tempPath[i] == '\\')
        {
            tempPath[i] = '.';
        }
    }

    if (strcmp(path, ROOT_DIR) == 0)
    {
        snprintf(formattedPath, 256, "[root]. "); // Format path with [root]
    }
    else
    {
        snprintf(formattedPath, 256, "[root].%s", tempPath); // Format path with [root] and proper `.` separator
    }
}

/*
Function to STAT the current directory using the variable currentDir and automatically format it with JPATH format.
*/
void printCurrentDirectory()
{
    char formattedPath[256];
    formatPath(formattedPath, currentDir);
    print(formattedPath);
    print("\n");
    return formattedPath;
}

void updateFormattedPath(char *formattedPath)
{
    // Call formatPath to properly update formattedPath with dot separators
    formatPath(formattedPath, currentDir); // formatPath already ensures the path is correct
    if (formattedPath[0] == '.')
    {
        // If the formattedPath starts with [root], remove any unnecessary leading dot
        memmove(formattedPath, formattedPath + 1, strlen(formattedPath));
    }

    // Check if formatting was successful (no errors)
    if (formattedPath[0] == '\0')
    {
        printf("Failed to update path format\n");
    }
}

void convertDotToBackslash(char *formattedPath) { // admits a char array of 256 for `formattedPath`.
    for (int i = 0; formattedPath[i] != '\0'; i++) { // iterate over the formattedPath until a NULL terminator is found.
        if (formattedPath[i] == '.') { // if a dot is found, replace it with a backslash.
            formattedPath[i] = '\\';  // Character replacement(`\`).
        }
    }
}

void changeDirectory(const char *path)
{
    char translatedDottedPath[256];
    strcpy(translatedDottedPath, path);  // Copy the path to work with it

    // Convert any dot-separated path into backslash-separated path
    convertDotToBackslash(translatedDottedPath);

    // Handle `cd <<` to go back one directory level (like `cd ..` in UNIX)
    if (strcmp(path, "<<") == 0)
    {
        // Check if we are at the root directory already
        if (strcmp(currentDir, ROOT_DIR) == 0)
        {
            print("Already at root. Cannot go back any further.\n");
            return;
        }

        // Find the last backslash in the currentDir (representing a directory level)
        char *lastBackslash = strrchr(currentDir, '\\');

        // If there's a backslash, remove everything after it (go back one level)
        if (lastBackslash)
        {
            *lastBackslash = '\0'; // Remove the last directory segment
        }

        // After modifying currentDir, we need to ensure it reflects the correct relative path:
        char relativePath[256];
        snprintf(relativePath, sizeof(relativePath), "[root]%s", currentDir);  // Ensure proper formatting

        // Update the formattedPath after changing the directory
        formatPath(formattedPath, relativePath);  // Reformat to match the relative path
        print("Changed directory to: ");
        print(formattedPath);
        print("\n");
    }
    else if (strcmp(path, "/") == 0)
    {
        // If the path is the root directory, set currentDir to ROOT_DIR
        strcpy(currentDir, ROOT_DIR);
        SetCurrentDirectory(ROOT_DIR);
        formatPath(formattedPath, currentDir);
        print("Changed directory to: ");
        print(formattedPath);
        print("\n");
    }
    else
    {
        // If we reach here, treat the path as a directory (only . separator paths)
        DWORD attributes = GetFileAttributes(translatedDottedPath);  // Use translated path

        if (attributes == INVALID_FILE_ATTRIBUTES)
        {
            print("Failed to change directory. \nECOD: \n");
            printf("%d\n", GetLastError());
            return;
        }

        if (attributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            // Handle normal directory change
            if (SetCurrentDirectory(translatedDottedPath))  // Use translated path here
            {
                GetCurrentDirectory(sizeof(currentDir), currentDir); // Get full path

                // Find the start of the relevant path inside ROOT_DIR
                char *relativePath = strstr(currentDir, ROOT_DIR);
                if (relativePath)
                {
                    relativePath += strlen(ROOT_DIR); // Move past "rootDir\J"
                    if (*relativePath == '\\')
                        relativePath++; // Remove extra `\`
                }
                else
                {
                    relativePath = currentDir; // If not inside ROOT_DIR, keep full path
                }

                // Update the currentDir to only hold the relative path
                strcpy(currentDir, relativePath);

                // Update formatted path (convert `\` to `.`)
                formatPath(formattedPath, currentDir);

                print("Changed directory to: ");
                print(formattedPath);
                print("\n");
            }
        }
        else
        {
            print("Failed to change directory. \nECOD: \n");
            printf("%d\n", GetLastError());
        }
    }
}
