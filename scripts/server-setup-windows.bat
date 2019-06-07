:: run through this script manually from administrator cmdprompt!

title "Windows build machine set-up"


:: create lentil-build home folder
mkdir "C:\lentil-build"
cd "C:\lentil-build"


:: install chocolatey
@"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"


:: possibly might have to restart cmd prompt here


:: install .net framework 3.5
::powershell.exe -Command "Dism.exe /online /enable-feature /featurename:NetFX3 /All /Source:C:\sources\sxs /LimitAccess"
choco install dotnet3.5 --yes


:: install wget
choco install wget --yes


:: install pathed for easy %PATH% manipulation
mkdir "C:\lentil-build\tools"
cd "C:\lentil-build\tools"
wget http://p-nand-q.com/download/gtools/gtools-current.exe
C:\lentil-build\tools\gtools-current.exe


:: pathed dryrun to force install .net framework
call "C:\Program Files (x86)\p-nand-q.com\GTools\pathed"


:: download envvar refresher by chocolatey
:: maybe not needed
wget https://github.com/chocolatey/choco/raw/master/src/chocolatey.resources/redirects/RefreshEnv.cmd --no-check-certificate


:: install git
choco install git -params '"/GitAndUnixToolsOnPath"' --yes
"C:\Program Files (x86)\p-nand-q.com\GTools\pathed" /APPEND "C:\Program Files\Git\bin" /MACHINE


:: install 7zip
choco install 7zip --yes
"C:\Program Files (x86)\p-nand-q.com\GTools\pathed" /APPEND "C:\Program Files\7-Zip" /MACHINE

choco install openssh --yes
:: follow instructions here: https://github.com/PowerShell/Win32-OpenSSH/wiki/Install-Win32-OpenSSH
:: generate keys and cross-copy (see server_setup_instructions.txt)
"C:\Program Files (x86)\p-nand-q.com\GTools\pathed" /APPEND "C:\Program Files\OpenSSH-Win64" /MACHINE


:: refresh envvars, is this needed?
:: this currently quits the batch script.. fix! Manual entering is OK
C:\lentil-build\tools\RefreshEnv.cmd


:: clone lentil repo
cd "C:\lentil-build"
git clone --recurse-submodules https://zpelgrims@github.com/zpelgrims/lentil.git


:: download arnold sdk's
:: maybe should put absolute path
wget -O arnold.zip https://www.dropbox.com/sh/rx57g4e3reamk3i/AAD5wLVnUQL1GEvDKv3MbbRfa?dl=1


:: unzip arnold sdk's
7z x arnold.zip -oarnold

:: possibly need to restart the cmd prompt? or open it in regular (non-admin) mode?
:: install visual studio 2017 build tools
choco install "visualstudio2017buildtools" --yes --passive
choco install "visualstudio2017-workload-vctools" --yes --passive


:: initialize x64 developer command line environment:
"C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvars64.bat"


:: change directory to lentil repo
cd "C:\lentil-build\lentil"