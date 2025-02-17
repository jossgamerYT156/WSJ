# WSJ
The Windows Subsystem for J-Kernel

Basic Subsystem made for Windows Hosts to run a containerized version of J and try it out before jumping in with J-OS completely(which might as well won't ever happen, lol
---

# How To Build

___
> These instructions assume you already have a copy of Visual Studio Community Build Tools 2022 installed
---
1.- Start the Visual Studio PowerShell program and CD into the project root directory(where make.bat is located)

2.- Run the `make.bat` batch script, this will generate the necessary .obj files inside `bin\*` and link them to the `subsystem.exe` file, it is recommended to run this if you plan to build the source, since compiling files one by one would take long amounts of time.

## If Necessary

- If you plan on cleaning the compiled subsystem, simply run `clean.bat`, this will remove all the files from `bin\*`, and `rootDir\J\*` if necessary, this of course assumes that `.\rootDir\J\` exists.

# known issues

> can't cd to `rootDir\J`

Normally this issue appears when starting `subsystem.exe` from a directory other than `.\`, it is recommended that you create the directory `rootDir\J` inside `.\` before running the executable so the subsystem binary can find and properly setup it's containerized environment

> warnings on compilation:
```
src\sys.c(37): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(39): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(41): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(43): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(44): warning C4113: 'void (__cdecl *)(HANDLE,HANDLE,DWORD)' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(45): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(46): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
```

These warns are "normal" and do not affect directly to the binary's operation, these are just misstypes on function declaration that uses shipped-windows features.

> the `ECOD` abvrebiation

`ECOD` reffers to "**`ERROR_CODE`**", normally outs after a command can't be processed correctly(like when cd'ing into a directory that doesn't exist), this will return a Windows Error Code, which can be googled in case of needed debugging.

> Lilly has not found any further issues at the time of this edition.

---
# Features:

## Multipurpose commands:

- `hlt`      : HALTS the program (CORE)
- `cd`       : change directories to the specified path (CORE)
- `osi`      : shows MISC OS info and target info (CORE)
- `pcd`      : prints the current directory (CORE)
- `pwd`      : Same as `pcd`, added just for compatibility (CORE.*INUXCOMPAT)
File Management:
- *`mkd`*    : removes a directory of the specified path (CORE)
- *`rmd`*    : remove directories from the specified path (CORE)
- *`mkf`*    : make a file with the specified name and path (CORE)
- *`rmf`*    : removes the specified file (CORE)
- *`ls`*     : Lists the contents of currentDir[256] (CORE)
- *`pwd`*    : (still on development) gets the current working directory(CORE)

## Windows Interaction
- *`dir`*    : same as `ls` (WINCOMPAT.WINDOWSUTILS.sysapp)
- *`open`*   : Open a file specified by the user using Windows' START directive (WINCOMPAT.WINDOWSUTILS.sysapp)
- *`clt`*    : clears the terminal(WINDOWS.WINDOWSUTILS.sysapp)

## Process Logic
- *`cproc`*  : create process (CORE)
- *`killall`* : kills all processes (CORE)
- *`addproc`* : adds a process to the processlist(CORE)


# Files and Stuff:
---
```.\src\:
|-- cmd.c           : Main Command Logic, and Command Prompt interaction, this handles everything inside WSJ, which is Command Handling, CommandDef and I/O, the SHELL interface so denominated `JSH`
|-- fs.c            : FileSystem interaction, stuff like `cd`, `pcd` and Path Formatting.
|-- io.c            : Basic I/O stuff like `print();` for J-Lang Scripts(in development).
|-- jutils.c        : Subsystem Modules like `Core` and `WINDOWSUTILS`
|-- kernel.c        : J-Kernel Logic and JLScript handling(in development).
|-- sys.c           : Main System Program, this starts the shell and handles the MainLoop.
.\bin\
|-- subsystem.exe   : Main Executable (WSJ Itself)
.\rootDir\*         : WSJ's `/`
```
---

# Licence

> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---
## Developed by: Lilly Aizawa (2022 - 2025) LDS LLC
