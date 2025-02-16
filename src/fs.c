// the FileSystem Handler for Windows Subsystem J

#include <windows.h>
#include <stdio.h>
char currentDir[256];  // To hold the current directory


/*
whole CD logic, DO NOT touch mf.
*/
void changeDirectory(const char *path) {
    if (SetCurrentDirectory(path)) {
        print("Changed directory to: ");
        print(path);
        print("\n");
        strcpy(currentDir, path);  // Keep track of new directory
    } else {
        print("Failed to change directory. Error Code: ");
        printf("%d\n", GetLastError());  // Print actual Windows error code
    }
}


/*
Basic function to create a directory
*/
void makeDirectory(const char *dirname) {
    if (CreateDirectory(dirname, NULL)) {
        print("Directory created: ");
        print(dirname);
        print("\n");
    } else {
        print("Failed to create directory.\n");
    }
}

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
        print("Failed to create file.\n");
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
        print("Failed to remove file.\n");
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
        print("Failed to remove directory.\n");
    }
}

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

/*
Formatting function for JPATH
*/
void formatPath(char *formattedPath, const char *path) {
    /*
    Example: Format like "(root).dir.subdir.file\type"
    */
    snprintf(formattedPath, 256, "(root)%s", path);
}

/*
Function to STAT the current directory using the variable currentDir and automatically format it with JPATH format.
*/
void printCurrentDirectory() {
    char formattedPath[256];
    formatPath(formattedPath, currentDir);
    print(formattedPath);
    print("\n");
}

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
        print("Failed to open file.\n");
    }
}


void updateFormattedPath(char *formattedPath) { 
    snprintf(formattedPath, sizeof(formattedPath), "(root)%s", currentDir);
}