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

## Headless Configuration
PowerGL can render scenes without opening an on-screen window by using its
headless backend based on EGL. This is useful for automated tests or systems
without a graphical environment.

Install the Mesa EGL development package if it is not already present. On
Debian/Ubuntu you can do this with:

```sh
sudo apt-get install libegl1-mesa-dev
```

To run the demo cube example in headless mode, set the environment variable
`POWERGL_HEADLESS` to `1` before executing the program:

```sh
POWERGL_HEADLESS=1 ./tests/demo_cube
```

The headless backend creates an off-screen EGL context and renders frames to a
pbuffer surface. The example saves these frames as PNG images so they can be
inspected later without requiring a display.

## OpenGL Debug Output
PowerGL can register an OpenGL debug callback to print driver messages. Set
the environment variable `POWERGL_GL_DEBUG` to `1` to enable it:

```sh
POWERGL_GL_DEBUG=1 ./tests/demo_cube
```
