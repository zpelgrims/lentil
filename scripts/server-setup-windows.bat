title "Windows build machine set-up"


:: create lentil-build home folder
mkdir "C:\lentil-build"
cd "C:\lentil-build"


:: install chocolatey
@"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"


:: restart cmd prompt
:: is this possible like this in a batch script? nope! 
start
:: &exit


:: install wget
choco install wget --yes


:: install pathed for easy %PATH% manipulation
mkdir "C:\lentil-build\tools"
cd "C:\lentil-build\tools"
wget http://p-nand-q.com/download/gtools/gtools-current.exe


:: pathed dryrun to force install .net framework
"C:\Program Files (x86)\p-nand-q.com\GTools\pathed"


:: download envvar refresher by chocolatey
https://github.com/chocolatey/choco/raw/master/src/chocolatey.resources/redirects/RefreshEnv.cmd


:: install git
choco install git -params '"/GitAndUnixToolsOnPath"' --yes
"C:\Program Files (x86)\p-nand-q.com\GTools\pathed" /APPEND "C:\Program Files\Git\bin" /MACHINE


:: install cmake
choco install cmake --yes
"C:\Program Files (x86)\p-nand-q.com\GTools\pathed" /APPEND "C:\Program Files\Cmake\bin" /MACHINE


:: refresh envvars
C:\lentil-build\tools\RefreshEnv.cmd


:: download arnold sdk's
:: maybe should put absolute path
wget -O https://www.dropbox.com/sh/rx57g4e3reamk3i/AAD5wLVnUQL1GEvDKv3MbbRfa?dl=1 arnold


:: install visual studio 2017 build tools
choco install "visualstudio2017buildtools" --yes
choco install "visualstudio2017-workload-vctools" --yes


:: initialize x64 developer command line environment:
"C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvars64.bat"

