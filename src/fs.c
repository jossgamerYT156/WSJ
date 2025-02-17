// the FileSystem Handler for Windows Subsystem J

#include <windows.h>
#include <stdio.h>
char currentDir[256];  // To hold the current directory


/*
whole CD logic, DO NOT touch mf.
*/
void changeDirectory(const char *path) {
    if (SetCurrentDirectory(path)) {
       if(path != 1){
        print("Failed to change directory. \n ECOD: \n"); // error message
        printf("%d\n", GetLastError());  // Print actual Windows error code
       } else {
        print("Changed directory to: "); // status
        print(path); // target directory
        print("\n"); // new line directory to avoid overlapping strings after cd
        strcpy(currentDir, path);  // Keep track of new directory
       }
    } else {
        print("Failed to change directory. \n ECOD: \n");
        printf("%d\n", GetLastError());  // Print actual Windows error code
    }
}

/*
Formatting function for JPATH
*/
void formatPath(char *formattedPath, const char *path) {
    /*
    Example: Format like "(root).dir.subdir.file\type"
    */
    snprintf(formattedPath, 256, "[root]%s", path);
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

void updateFormattedPath(char *formattedPath) { 
    /*
    Loop to properly update the path and return a error-code for mishandled updates of `"[root].%s", currentPath`
    */
    if (sprintf(formattedPath, "[root]%s", currentDir) < 0) {
        printf("Failed to update PATH\nECOD: %d\n", GetLastError());
    } else {
        // Success, do nothing.
    }
    
}