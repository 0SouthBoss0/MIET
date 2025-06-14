#!/bin/bash

summa=0
len=$#

for val in "$@";
do
    summa=$(($summa+$val))
done
avrg=$(($summa/$len))
echo "Число аргументов: "$#
echo "Среднее арифметическое аргументов: "$avrg

