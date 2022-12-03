#!/bin/bash

source utils.sh --source-specific get_rom_file

ROM=$(get_rom_file)

../opt/java/jre1.8.0_latest/bin/java -jar ../opt/nintaco/Nintaco_bin_2020-05-01/Nintaco.jar '../res/rom/'"${ROM}" &
