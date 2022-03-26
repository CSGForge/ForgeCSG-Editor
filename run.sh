#!/bin/bash

premake5 gmake2
make -C build
./bin/Debug/CSGForge-Editor
