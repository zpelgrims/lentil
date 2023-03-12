
### There are two components to this project. The first of one is "pota" - short for "Polynomial optics to Arnold". The second one is "polynomial-optics", which is a fork of "Sparse high-degree polynomials for wide-angle lenses" (https://jo.dreggn.org/home/2016_optics.pdf)

  

To get started compiling the Arnold plugin - which I will assume most of the people here are interested in, you don't need to touch the "polynomial-optics" folder. The files have been pre-generated for compilation. However, if new lenses need to be added, this can be done with the code inside of "polynomial-optics".
  

### Arnold plug-in compile instructions:

  
Download the Arnold SDK from: https://arnoldrenderer.com/download/archive/ (under Arnold SDK). On my own machine, the environment variables look like this. Please modify for your needs/arnold version. Changing the Arnold Root version will change which Arnold version the plugin is compiled against.

```bash
    export LENTIL_ARNOLD_SDKS="/home/cactus/"
    export LENTIL_PATH="/home/cactus/lentil/polynomial-optics"
    export ARNOLD_ROOT="/home/cactus/Arnold-7.1.1.0-linux"
    export ARNOLD_VERSION="7.1.1.0"
    export PATH=$PATH:$LENTIL_PATH"/../Eigen/"
    export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$ARNOLD_ROOT/bin"
```

The project uses cmake for compilation. The build setup is a forked version from the Cryptomatte project.
```bash
    cd lentil
    cd pota
    mkdir build
    cd build
    make install ..
```

This will build the project to the `/dist` folder.

  

-------

  

### (POLYNOMIAL OPTICS) compile instructions:

  

TODO.


-----


MIT License

Copyright (c) [2023] [Zeno Pelgrims]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.