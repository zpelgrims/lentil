### Command line instructions for setting up a windows machine

---

#### installed packages:

- > visual studio build tools
- > git
- > wget
- > lentil repo
- > a few of the latest arnold 5 sdk packages

---

- [ ] open admin cmd prompt:
    - probably will have to do this manually? will have to get into a shell to execute any command to begin with..
    

- [x] install chocolatey

    ```@"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"```

- [ ] restart admin cmd prompt:

    - there is probably a reboot command for the cmd prompt?

- [x] Install Visual Studio Command Line Tools:

    `choco install visualstudio2017buildtools --package-parameters "--allWorkloads --includeRecommended --includeOptional --passive --locale en-US"`

    .. or maybe full install is not necessary?

    `choco install visualstudio2017buildtools"`

- [x] install git

    - `choco install git -params '"/GitAndUnixToolsOnPath"'`
    - type `y`

- [x] install wget

    - `choco install wget`
    - type `y`

- [ ] clone lentil repository:
    
    `mkdir "C:\lentil-build"`

    `cd "C:\lentil-build"`

    `git clone https://github.com/zpelgrims/lentil.git`


- [ ] download arnold sdk packages using `wget` (should store these on a server somewhere for easy downloading)

    - something like:
    `wget https://www.dropbox.com/sh/rx57g4e3reamk3i/AAD5wLVnUQL1GEvDKv3MbbRfa?dl=1`

    could be dl=0 at end of link? untested


- [x] run the visual studio command line:

    - ```"C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvars64.bat"```

- 