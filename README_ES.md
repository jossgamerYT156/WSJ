# WSJ
El Subsistema J-Kernel para Windows

Un Subsistema basico hecho para que Hosts utilizando Windows ejecuten una version contenida de J y lo prueben antes de saltar a J-OS completamente (Aunque es poco probable que eso pase, XD)
___

# Como Compilar
__
> Estas instrucciones asumen que usted ya possee una copia de Visual Studio Community 2022 y sus Build Tools 2019 instalada en su sistema

> Version de Visual Studio Build Tools que usa Lilly como ejemplo:
> PowerShell: Visual Studio 2022 Developer PowerShell v17.14.0-pre.1.0
>
> Compiler: Microsoft (R) C/C++ Optimizing Compiler Version 19.44.34823.2 for x64
>
> Linker: Microsoft (R) Incremental Linker Version 14.44.34823.2

WSJ Ha sido compilado en:
> SO: Windows 11 Pro 24H2 N.C.: 26100.3194
>
> CPU: AMD Ryzen 7 PRO 4750U(16) Arquitectura: X86_64(64Bit)
>
> RAM: 16GB LDDR4

___
1.- Inicia el programa `Terminal Para Desarrolladores PowerShell` y [`cd`](https://es.wikipedia.org/wiki/Cd_(commando)) hacia el directorio raiz del projecto(donde `make.bat` esta localizado)

2.- Ejecuta el script `make.bat`(dentro de la Terminal Para Desarrolladores PowerShell), esto generara los archivos .obj necesarios dentro de `.\bin\*` y los enlazara (Utilizando el [Enlazador](https://es.wikipedia.org/wiki/Enlazador) Proveeido por VSBT 2019) para formar el binario `subsystem.exe`, es recomendable ejecutar esto si planea en compilar el codigo fuente, ya que compilar cada archivo manualmente toma largas cantidades de tiempo.

## De ser necesario:

- Si planea en limpiar el Subsystema compilado, simplemente ejecute `clean.bat`(desde la raiz del projecto), esto eliminara todos los archivos dentro de `.\bin\*`, y `rootDir\J\*` de ser necesario, esto assume que el directorio `.\rootDir\J\` existe.

# Errores Conocidos

> can't cd to `rootDir\J` / No se puede cambiar Directorio a `rootDir\J`

Este problema suele ocurrir cuando se ejecuta `subsystem.exe` desde un directorio distinto al de la raíz del proyecto, es recomendable que crees `rootDir\J` dentro de la raiz del projecto antes de ejecutar el programa para que el binario del subsystema pueda encontrar el archivo y iniciar apropiadamente.

> Advertencias durante la compilación:
```
src\sys.c(37): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(39): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(41): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(43): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(44): warning C4113: 'void (__cdecl *)(HANDLE,HANDLE,DWORD)' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(45): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
src\sys.c(46): warning C4113: 'void (__cdecl *)()' differs in parameter lists from 'void (__cdecl *)(const char *)'
```

Estas advertencias son comunes y no afectan el funcionamiento del binario, estos son simplemente re-declaraciones de funciones que utilizan caracterizticas de Windows ya incluidas, aunque sean re-declaraciones, estas son menores errores los cuales parecen no causar problemas mayores.

> La abreviacion `ECOD`

`ECOD` se refiere a "**`ERROR_CODE`**", Normalmente aparece cuando un comando no puede ser procesado correctamente(como al intentar hacer `cd` hacia un directorio que no existe), esto regresara un Codigo De Error De Windows, al cual Google tal vez no tenga resultados para hacerle Debugging.

> Lilly no ha encontrado mas errores al momento de esta edicion.

__
# Caracteristicas

## Comandos Multiproposito:

- *`hlt`*      : Detiene el programa (NUCLEO)
- *`cd`*       : cambia el directorio de trabajo hacia el directorio especificado (NUCLEO)
- *`osi`*      : Muestra informacion miscelanea sobre J y el SO Objetivo (NUCLEO)
- *`pcd`*      : Muestra el directorio actual (NUCLEO)
- *`pwd`*      : Lo mismo que `pcd` (NUCLEO)

## Manejo de archivos

- *`mkd`*       : Crea un directorio con el nombre especificado. (NUCLEO)
- *`rmd`*       : Borra un directorio con el nombre especificado. (NUCLEO)
- *`mkf`*       : Crea un archivo vacío con el nombre especificado. (NUCLEO)
- *`rmf`*       : Lo mismo que `rmf` pero para archivos. (NUCLEO)
- *`ls`*        : Muestr alos contenidos de `currentDir[256]` (NUCLEO.*INUXCOMPAT)

## Interaccion Con Windows

- *`dir`*       : hace lo mismo que `ls` (WINCOMPAT.WINDOWSUTILS.sysapp)
- *`open`*      : Abre un archivo en la aplicacion por defecto utilizando la directiva `START` de Windows (WINCOMPAT.WINDOWSUTILS.sysapp)
- *`clt`*       : Limpia la terminal (WINCOMPAT.WINDOWSUTILS.sysapp)

## Logica de ProgMan

> Caracteristicas En Desarrollo

- *`cproc`*     : Crea un processo (NUCLEO)
- *`killall`*   : Termina todos los processos (NUCLEO)
- *`addproc`*   : agrega un proceso a la Lista_De_Procesos (NUCLEO)

# Estructura Del Projecto:
___
```
$RAIZ_DEL_PROJECTO [DIRECTORIO]
├──  LICENCE [ARCHIVO]                      // Licencia de software de tipo MIT del projecto
├──  README.md [ARCHIVO]                    // archivo leeanme con documentacion breve
├──  README_ES.md [ARCHIVO]                 // traduccion en espanol para el archivo leeanme
├──  .gitignore [ARCHIVO]                   // archivo conteniendo que archivos para ignorar por el comando `git commit`
├──  rootDir [DIRECTORIO]                   // directorio Raiz de J, inicio de la raiz de J Subsystem
│      └── J [DIRECTORIO]                   // Raiz de subsystem.exe/J-System
│          └──* [DIRECTORIO]                // archivos que usted cree dentro de J seran guardados aqui
├── src [DIRECTORIO]                        // directorio con el codigo fuente de J
│    └──include [DIRECTORIO]                // Directorio con archivos .h del projecto, crea tus headerfiles aqui para incluirlos en compilacion automaticamente
│    │    └──prototypes.h [ARCHIVO]         // archivo conteniendo los prototipos de las funciones para el uso project-broad.
│    ├── fs.c [ARCHIVO]                     // Interaccion con el sistema de archivos
│    ├── io.c [ARCHIVO]                     // operaciones I/O basicas
│    ├── jutils.c [ARCHIVO]                 // modulos NUCLEO, *INUXCOMPAT y WINDOWSCOMPAT
│    ├── kernel.c [ARCHIVO]                 // Logica de Kernel (En desarrollo)
│    ├── sys.c [ARCHIVO]                    // Caracteristicas del sistema como la lista de comandos
├── bin [DIRECTORIO]                        // directorio de salida de make.bat, /Fe:bin\subsystem.exe
│   └── subsystem.exe [BINARIO DE WINDOWS]  // Binario de J
├── clean.bat [SCRIPT DE LIMPIEZA]          // archivo de limpieza de archivos
└── make.bat [SCRIPT DE LIMPIEZA]           // archivo de compilacion para VS Powershell Para Desarrolladores
```

# Que Esperar

J Es un projecto mantenido por **UNA** persona, lo que significa que muchas cosas pasan desapercibidas de Lilly.

- Espera encontrar pequeños errores o funciones que aún no están completamente implementadas, Lilly experimenta muchas cosas y metodos todo el tiempo.
- No esperes actualizaciones frecuentes, Lilly también tiene vida fuera de GitHub.
- **Muy Probablemente** Lilly reimplemente cosas que Windows ya hace con una funcion sencilla, Lilly tiene el habito de hacer eso sin razon aparente.
- Espera refactorizaciones de codigo constantes y comentarios en lineas que son auto-explicables, Lilly es tan nueva con codigo como cualquier persona con 3-4 anos de experiencia en programacion.
- Espera constantes menciones hacia la ayuda de [*Techlm77*](https://github.com/Techlm77), *Hugh P. Hulme* & [Tiadrop](https://github.com/tiadrop) en cualquier momento, ya que Lilly siempre los molesta para preguntarles por ayuda.

___

# Licencia
___

## Bajo Licencia De Tipo MIT
> EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O
IMPLÍCITA, INCLUYENDO, ENTRE OTRAS, LAS GARANTÍAS DE COMERCIABILIDAD,
ADECUACIÓN PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN.
EN NINGÚN CASO LOS AUTORES O TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE RECLAMACIONES, DAÑOS U OTRA
RESPONSABILIDAD, YA SEA EN UNA ACCIÓN CONTRACTUAL, AGRAVIO O DE OTRO MODO, QUE SURJA DE,
DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTRAS OPERACIONES EN EL
SOFTWARE.

___

___
## Desarrollado por: Lilly Aizawa (2022 - 2025) LDS LLC

___

___

[Explicacion Rapida por Lilly Aizawa| Pagina En Ingles](https://lillydevstudios.neocities.org/home/about/J-OS/)

[J Basado En Linux| Pagina En Espanol](https://techlm77.co.uk/J-OS/index-spanish.html) por [Techlm77| Perfil En Ingles](https://www.github.com/Techlm77/)