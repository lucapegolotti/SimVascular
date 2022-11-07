#!/bin/bash

export CC=/usr/bin/gcc-8
export CXX=/usr/bin/g++-8

export ML2DSEGMENTATION_LIBRARY=/home/luca/repositories/ML2DSegmentation-install/lib/libml2dsegmentation.so
export ML2DSEGMENTATION_INCLUDE=/home/luca/repositories/ML2DSegmentation-install/include/

rm -r -f build
mkdir build
cd build
cmake -DML2DSEGMENTATION_LIBRARY=$ML2DSEGMENTATION_LIBRARY \
      -DML2DSEGMENTATION_INCLUDE_DIR=$ML2DSEGMENTATION_INCLUDE \
      ..

make