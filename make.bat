:: We disable command echoing, so we just see the output
@echo off
:: clear the screen so we have no distractions when debugging problems
cls

:: Just a message for no reason
echo "Building J-Kernel for Windows Subsystem: Windows Subsystem J"

:: we call CL.EXE so we can compile the object files, we need those.
cl /MP /c src\io.c src\jutils.c src\sys.c src\fs.c src\kernel.c src\cmd.c /Fo:bin\ /I src\include

:: we link the file into a .EXE so you can use the Subsystem
cl bin\io.obj bin\jutils.obj bin\sys.obj bin\fs.obj bin\kernel.obj bin\cmd.obj /Fe:bin\subsystem.exe

:: initialize a cleanup of .obj files for next run, to avoid leftover files, we also list the bin directory to see if the executable was created successfully.
del bin\*.obj | dir/w bin\*.exe
