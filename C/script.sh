#!/bin/sh

declare -a files=("C1" "C2" "C3")

for i in ${files[@]}; do
  cmd="g++ -o lib$i.so "$i"_lib.cpp -fpic -shared -std=c++1z -rdynamic"
  echo $cmd
  $cmd
done
