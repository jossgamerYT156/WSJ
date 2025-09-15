# Error Handling and Other Definitions

This include directory contains the includes of the J "kernel" code(Our Monolithic binary file)

## What does this contains?
In the case of files like [src/prototypes.h](prototypes.h) it contains the prototypes so other files can use all of the features by each other files' contents.

EG:
```c
// FS.C:73-175:
void formatPath(char *formattedPath, const char *path)
{
    // ...
    // My Defined CD Logic, i am not copying the whole code.
    // ...
}
```

Is referrenced in:
```c
// prototypes.h:75:
extern void changeDirectory(const char *path);
```


For the case of [errHandle.h](errHandle.h), it contains the error code definitions for J Errors that we see in some versions of our "Kernel".
things like our errors:

- 306 : Writing File Error
- 403 : MKD Error

and many others.

how to fix these errors?
dunno, edit the code, i guess.