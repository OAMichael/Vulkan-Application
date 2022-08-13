#!/bin/bash

CURRENT_DIR=$PWD
BASEDIR=$(basename $CURRENT_DIR)

if [ $BASEDIR = "build" ];
then
	cd ../
else
	CURRENT_DIR="$CURRENT_DIR/build"
fi

echo "Compiling shaders..."
/usr/local/bin/glslc shaders/shader.vert -o shaders/shader.vert.spv
/usr/local/bin/glslc shaders/shader.frag -o shaders/shader.frag.spv
/usr/local/bin/glslc shaders/skybox.vert -o shaders/skybox.vert.spv
/usr/local/bin/glslc shaders/skybox.frag -o shaders/skybox.frag.spv

echo "Shaders have been compiled!"

mkdir -p build/cmake
cd build/cmake

echo "Building into $CURRENT_DIR..."
cmake ../..
make
mv MyApp.exe ../MyApp.exe

cd ../..