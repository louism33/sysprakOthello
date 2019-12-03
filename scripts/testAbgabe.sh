#!/bin/bash

my_dir="$(dirname "$0")"

rm -rf buildDir/ && clear && "$my_dir/sysprak-abgabe.sh" buildDir valgrindlog.txt sysprakOthello.zip --spectate
