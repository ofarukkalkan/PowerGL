#!/bin/sh
# Automake executes tests from their build directory, so the built
# vertexcoloredcube_demo binary is available in the current working
# directory.  Simply invoke it directly to work both in the build tree
# and in "make distcheck".
POWERGL_HEADLESS=1 EGL_PLATFORM=surfaceless ./vertexcoloredcube_demo
