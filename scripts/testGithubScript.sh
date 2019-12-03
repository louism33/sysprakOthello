#!/bin/bash
# VERSION: 1.1.0
set -e

function finish() {
	echo
	echo "Done all tests"
    rm -rf buildDir/
}
PUNKTE=0

PLAYER1=1
PLAYER2=2
EXECNAME=sysprak-client

trap finish EXIT

VALGRIND_LOG=VALGRINDTESTLOGgithub.log
FILE=sysprakOthello.zip
BUILD_DIR=buildDir

rm -f $FILE
rm -rf $BUILD_DIR

my_dir="$(dirname "$0")"
"$my_dir/zipSysprakOthello.sh"

## Test 1: Check size maximum of 500 KiB
if [ $(unzip -p "$FILE" | wc -c) -lt 512000 ]; then
	echo "Filesize: OK"
else
	echo "Filesize too big!"
	exit
fi

## create empty build dir
if [ -d "$BUILD_DIR" ]; then
	echo "$BUILD_DIR already exists"
	exit 1
fi

mkdir -p $BUILD_DIR

## unzip files and compile
unzip -q $FILE -d $BUILD_DIR
cd $BUILD_DIR
make -B
make -s clean

## Test 2: makeflags
MAKEFLAGS=$(make -n)
if [[ $MAKEFLAGS == *"-Wall"* ]] \
&& [[ $MAKEFLAGS == *"-Wextra"* ]] \
&& [[ $MAKEFLAGS == *"-Werror"* ]]; then
	echo "***** Makeflags: OK *****"
else
	echo "***** Makeflags do not contain -Wall, -Wextra or -Werror! *****"
	exit
fi

## Test 3: Check if the project compiles without errors or warnings
if make -s; then
	echo "***** Compilation: OK *****"
else
	echo "***** Compilation did not complete without warnings or errors! *****"
	exit
fi

echo "***** checking valgrind for test *****"

## check Valgrind
rm -f $VALGRIND_LOG
valgrind --log-file=$VALGRIND_LOG -q --leak-check=full --trace-children=yes ./sysprak-client TEST


echo "***** finished checking valgrind for test *****"

# check valgrind errors
if [[ $(cat $VALGRIND_LOG) == "" ]]; then
	echo "***** Valgrind1: OK *****"
else
	echo "***** Valgrind1 did find errors: *****"
	cat $VALGRIND_LOG
    exit
fi

echo "***** checking valgrind for perft command *****"

## check Valgrind with perft command
rm -f $VALGRIND_LOG
valgrind --log-file=$VALGRIND_LOG -q --leak-check=full --trace-children=yes ./sysprak-client perft 8

echo "***** finished checking valgrind for perft command *****"

# check valgrind errors
if [[ $(cat $VALGRIND_LOG) == "" ]]; then
	echo "***** Valgrind2: OK*****"
else
	echo "***** Valgrind2 did find errors: *****"
	cat $VALGRIND_LOG
    exit
fi



