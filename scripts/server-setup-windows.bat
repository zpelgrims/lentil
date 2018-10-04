title "Windows build machine set-up"


:: create lentil-build home folder
mkdir "C:\lentil-build"
cd "C:\lentil-build"


:: install chocolatey
@"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"


:: possibly might have to restart cmd prompt here


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
wget https://github.com/chocolatey/choco/raw/master/src/chocolatey.resources/redirects/RefreshEnv.cmd


:: install git
choco install git -params '"/GitAndUnixToolsOnPath"' --yes
"C:\Program Files (x86)\p-nand-q.com\GTools\pathed" /APPEND "C:\Program Files\Git\bin" /MACHINE


:: install cmake
choco install cmake --yes
"C:\Program Files (x86)\p-nand-q.com\GTools\pathed" /APPEND "C:\Program Files\Cmake\bin" /MACHINE


:: install 7zip
choco install 7zip --yes
"C:\Program Files (x86)\p-nand-q.com\GTools\pathed" /APPEND "C:\Program Files\7-Zip" /MACHINE


:: refresh envvars
C:\lentil-build\tools\RefreshEnv.cmd


:: download arnold sdk's
:: maybe should put absolute path
wget -O arnold.zip https://www.dropbox.com/sh/rx57g4e3reamk3i/AAD5wLVnUQL1GEvDKv3MbbRfa?dl=1

:: unzip arnold sdk's
7z arnold.zip

:: install visual studio 2017 build tools
choco install "visualstudio2017buildtools" --yes --passive
choco install "visualstudio2017-workload-vctools" --yes --passive


:: initialize x64 developer command line environment:
"C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvars64.bat"

