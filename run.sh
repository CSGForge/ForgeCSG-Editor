#!/bin/bash

premake5 gmake2
make -C build
cd bin/Debug
./CSGForge-Editor
cd ../../