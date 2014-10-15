#!/bin/bash
unamestr=`uname`
if [[ "$unamestr" == 'Darwin' ]]; then
    OPTS='.. -DCMAKE_CXX_COMPILER=g++-4.9 -DCMAKE_C_COMPILER=gcc-4.9'
else
    OPTS='..'
fi

cd other
mkdir build
cd build
cmake $OPTS
make
cd ..
cd ..
cd parfor
mkdir build
cd build
cmake $OPTS
make
cd ..
cd ..
cd reduction
mkdir build
cd build
cmake $OPTS
make
cd ..
cd ..

