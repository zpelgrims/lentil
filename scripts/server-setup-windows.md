### Command line instructions for setting up a windows machine

---

#### installed packages:

- > visual studio build tools
- > cmake
- > chocolatey
- > pathed
- > git
- > wget
- > lentil repository
- > a few of the latest arnold 5 sdk packages

---

#### commands:

- [ ] open admin cmd prompt:
    - probably will have to do this manually? will have to get into a shell to execute any command to begin with..

- [x] create lentil folder:

    - `mkdir "C:\lentil-build"`

    - `cd "C:\lentil-build"`
    

- [x] install chocolatey

   -  ```@"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"```

- [x] restart admin cmd prompt:

    - `start &exit`

- [x] install wget

    - `choco install wget`
    - type `y`

- [x] download pathed:

    - `mkdir "C:\lentil-build\tools"`
    - `cd "C:\lentil-build\tools"`
    - `wget http://p-nand-q.com/download/gtools/gtools-current.exe`

    first time it probably installs .net framework
    - `"C:\Program Files (x86)\p-nand-q.com\GTools\pathed"`


- [x] download tool to refresh the environment variables
    - `wget https://github.com/chocolatey/choco/raw/master/src/chocolatey.resources/redirects/RefreshEnv.cmd`


- [x] install git

    - `choco install git -params '"/GitAndUnixToolsOnPath"'`
    - type `y`
    - ~~`setx PATH "%PATH%;C:\Program Files\Git\bin" /M`~~
    - `"C:\Program Files (x86)\p-nand-q.com\GTools\pathed" /APPEND "C:\Program Files\Git\bin" /MACHINE`

- [x] install cmake

    - `choco install cmake`
    - type `y`
    - ~~`setx PATH "%PATH%;C:\Program Files\Cmake\bin" /M`~~
    - `"C:\Program Files (x86)\p-nand-q.com\GTools\pathed" /APPEND "C:\Program Files\Cmake\bin" /MACHINE`

- [x] refresh envvars

    - `C:\lentil-build\tools\RefreshEnv.cmd`


- [x] clone lentil repository:

    Would be nice if this didn't give a login popup due to private repo:
    
    - `git clone https://zpelgrims@github.com/zpelgrims/lentil.git`


- [x] download arnold sdk packages using `wget` (should store these on a server somewhere for easy downloading)

    - `wget -O https://www.dropbox.com/sh/rx57g4e3reamk3i/AAD5wLVnUQL1GEvDKv3MbbRfa?dl=1 arnold`


- [x] Install Visual Studio Command Line Tools:

     ~~`choco install visualstudio2017buildtools --package-parameters "--allWorkloads --includeRecommended --includeOptional --passive --locale en-US"`~~

    `choco install "visualstudio2017buildtools"`

    type `y` x3

    `choco install "visualstudio2017-workload-vctools"`

    type `y` x3



- [x] run the visual studio command line:

    - ```"C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvars64.bat"```



alternative for using pathed:

- `REG ADD "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v PATH /t REG_EXPAND_SZ /d "%PATH%;a_path_to_somewhere"`