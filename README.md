# PowerGL
PowerGL is a graphics engine implemented with C using OpenGL

![C/C++ CI](https://github.com/ofarukkalkan/PowerGL/workflows/C/C++%20CI/badge.svg)


## Running Tests
Install the Google Test development package (for example `libgtest-dev` on
Debian/Ubuntu) and then generate build files and run the test suite:
```sh
autoreconf -i
./configure
make check
```

## Coverage
After running the tests you can generate coverage reports using [gcovr](https://gcovr.com/):
Install gcovr via apt:
```sh
sudo apt-get install gcovr
```
```sh
gcovr -r . --html --html-details -o coverage/index.html --gcov-ignore-errors no_working_dir_found
```
