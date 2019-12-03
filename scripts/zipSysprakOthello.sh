#!/bin/bash


DIR=$PWD
OUTPUT=sysprakOthello.zip
rm -rf buildDir/
rm -f sysprakOthello.zip

cd ..
rm -f sysprakOthello.zip
echo "*** zipping sysprakOthello"
git archive -o $OUTPUT HEAD
mv $OUTPUT $DIR
cd $DIR


