#!/bin/bash

my_dir="$(dirname "$0")"

echo "zipping"

./zipSysprakOthello.sh

echo "zipping done "

rm -rf buildDir/ && "$my_dir/sysprak-abgabe.sh" buildDir valgrindlogXXX.txt sysprakOthello.zip --spectate
