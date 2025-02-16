@REM We disable command echoing, so we just see the output
@echo off
@REM clear the screen so we have no distractions when debugging problems
cls

@REM Just a message for no reason
echo "Building J-Kernel for Windows Subsystem: Windows Subsystem J"

@REM we call CL.EXE so we can compile the object files, we need those.
cl /c src\io.c src\fs.c src\cmd.c /Fo:bin\

@REM we link the file into a .EXE so you can use the Subsystem
cl bin\io.obj bin\fs.obj bin\cmd.obj /Fe:bin\subsystem.exe

@REM initialize a cleanup of .obj files for next run, to avoid leftover files, we also list the bin directory to see if the executable was created successfully.
del bin\*.obj | dir/w bin
