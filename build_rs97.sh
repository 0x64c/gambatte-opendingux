#!/bin/sh

echo "cd libgambatte && scons"
(cd libgambatte && scons -Q target=rs97) || exit

echo "cd gambatte_sdl && scons"
(cd gambatte_sdl && scons -Q target=rs97)
