#!/bin/bash
unamestr=`uname`
if [[ "$unamestr" == 'Darwin' ]]; then
    OPTS='../src -DCMAKE_CXX_COMPILER=g++-4.9 -DCMAKE_C_COMPILER=gcc-4.9'
else
    OPTS='../src'
fi

mkdir build
cd build
cmake $OPTS
make
