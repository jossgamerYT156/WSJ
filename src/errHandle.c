#include "prototypes.h"

/**
 * @brief Definitions for error codes.
 */
const int fsError = 4;
const int fsErrorCannotChangeDir = 8;
const int fsErrorCannotCreateDir = 406;
const int unknownError = 50;
const int directoryException = 3; // Add this definition

#pragma section
    int jErrorHandler(char *reason, int *number){
        if (reason == 0 || number == 0) {
            printf("J-ERROR: 0x00:0x00\n INVALID ARGUMENTS PASSED TO HANDLER\n\n%dx%d%d\n", unknownError, unknownError, GetLastError());
            return -1; // Invalid arguments
        }

        if (*number == 3) {
            printf("J-ERROR: 0x10:0xF0\n FS_ERR\n\n%dx%d%d\n", directoryException, unknownError, GetLastError());
            return; // Invalid arguments
        }

        if (*number == 4) {
            printf("J-ERROR: 0x40:0xA1\n FS_ERR\n\n%dx%d%d\n", fsError, unknownError, GetLastError());
            return; // Invalid arguments
        }
    }

#pragma endsection