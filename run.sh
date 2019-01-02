#!/bin/env sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $DIR
rm -r -f build 
make 
./dist/Debug/GNU-Linux/prototype 
