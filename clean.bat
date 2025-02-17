@echo off
:: we delete old binaries even if user doesn't prompts for it.
echo Deleting old binaries...
del /Q bin\*.*

:: Ask user for input
choice /C YN /M "Delete files inside J Root?"
:: If the choice is N, we return that the cleanup of it will skip, so users know what is happening
if errorlevel 2 (
    echo Skipping ROOTDIR cleanup
) else (
:: if choice is Y, we delete the rootDir of J recursively, and re-create it.
    rd /S /Q rootDir\J\
    mkdir rootDir\J\
    echo Cleanup of J's ROOT DIR completed!
)

echo Cleanup complete!
pause
