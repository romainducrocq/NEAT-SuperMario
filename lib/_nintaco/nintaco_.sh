#!/bin/bash

gcc -c -Wall nintaco.c

nm nintaco.o | grep --invert-match " U " | cut -d' ' -f3 > obj.txt

echo -n '' > nintaco.hpp

echo '#ifndef _NINTACO_HPP' >> nintaco.hpp
echo '#define _NINTACO_HPP' >> nintaco.hpp
echo '' >> nintaco.hpp

while IFS="" read -r LINE || [ -n "$LINE" ]
do
    echo '#define '"${LINE}"' nintaco_'"${LINE}" >> nintaco.hpp
done < obj.txt

echo '' >> nintaco.hpp
echo '#include "nintaco.h"' >> nintaco.hpp
echo '' >> nintaco.hpp

while IFS="" read -r LINE || [ -n "$LINE" ]
do
    echo '#undef '"${LINE}" >> nintaco.hpp
done < obj.txt

echo '' >> nintaco.hpp
echo '#endif' >> nintaco.hpp

while IFS="" read -r LINE || [ -n "$LINE" ]
do
    objcopy --redefine-sym ${LINE}=nintaco_${LINE} nintaco.o
done < obj.txt

ar -rcs libNintaco.a nintaco.o
