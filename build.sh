#!/bin/bash
target_files=""
output_directory="./out"

declare -a compile_paths=("./src")

POSITIONAL_ARGS=()

#set up flags
keep_output="false"
debug="false"
windows="false"
for flag in $@
do
    case $flag in
        keep) keep_output="true";;
        debug) debug="true";;
        windows) windows="true";;
    esac
done


#compile
function compile_file() {
    file_name="${1/.\//}"
    target_name=$(basename $file_name)
    target_name=./$target_name
    target_files+=" ${target_name/.c/.o}"
    
    gcc -c $file_name -I ./glib
}


for p in "${compile_paths[@]}"; do 
    for f in $p/*.c; do
        compile_file $f
    done
done


#TODO windows
gcc $target_files -o $output_directory/a.out -I ./glib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
mv ./game.o "$output_directory"/game.o

# run
if [ $debug = "false" ]; then
    "$output_directory"/a.out
else
    valgrind "$output_directory"/a.out
fi
#clean up
if [ $keep_output = "false" ]; then
    rm $output_directory/*.out
fi
