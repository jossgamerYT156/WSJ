// error definitions for J
#ifndef ERRHANDLE_H
#define ERRHANDLE_H

/*
Errors Cheatsheet:

Starts With:>>
1 == File Handle Issue(J Handle Method Failure)
2 == File Not Found(J Handle Method Failure)
3 == File Already Exists or Cannot Be Created(J Handle Method Failure/Windows Error)
4 == File Cannot Be Opened or Does Not Exists(J Handle Method Failure/Windows Error)

5 == Fatal Unknown Error(J Internal Error/Windows Unexpected Behavior)
6 == Invalid Argument(J Handle Method Failure)

*/

 /**
  * @brief Error codes for the J Subsystem.
  */
 extern const int fsErrorCannotChangeDir;
 extern const int fsErrorCannotCreateDir;
 extern const int unknownError;

#endif