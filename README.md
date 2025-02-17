# WSJ
The Windows Subsystem for J-Kernel

Basic Subsystem made for Windows Hosts to run a containerized version of J and try it out before jumping in with J-OS completely(which might as well won't ever happen, lol
---
---
# Features:

## Multipurpose commands:
- `cd`     : change directories to the specified path(CORE)
File Management:
- *`mkd`*    : removes a directory of the specified path (core)
- *`rmd`*    : remove directories from the specified path (CORE)
- *`mkf`*    : make a file with the specified name and path (CORE)
- *`rmf`*    : removes the specified file (CORE)
- *`ls`*     : Lists the contents of currentDir[256] (core)
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
