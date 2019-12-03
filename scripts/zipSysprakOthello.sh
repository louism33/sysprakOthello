#!/bin/bash


DIR=$PWD
OUTPUT=sysprakOthello.zip
rm -rf buildDir/
rm -f $OUTPUT
cd ..
rm -f $OUTPUT
echo "*** zipping sysprakOthello"
git archive -o $OUTPUT HEAD
mv $OUTPUT $DIR
cd $DIR


