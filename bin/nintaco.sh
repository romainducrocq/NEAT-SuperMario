#!/bin/bash

ROM="Super Mario Bros (E).nes"

java/jre1.8.0_latest/bin/java -jar nintaco/Nintaco_bin_2020-05-01/Nintaco.jar '../res/rom/'"${ROM}" &
