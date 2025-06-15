# PowerGL
PowerGL is a graphics engine implemented with C using OpenGL

![C/C++ CI](https://github.com/ofarukkalkan/PowerGL/workflows/C/C++%20CI/badge.svg)


## Running Tests
After cloning, initialize submodules:
```sh
git submodule update --init
```
Generate build files and run the test suite:
```sh
autoreconf -i
./configure
make check
```
