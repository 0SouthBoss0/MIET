#!/bin/bash
 
for i in {1..150}; do
  echo $(od -A n -t d -N 1 /dev/random) >> numbers.txt
done
