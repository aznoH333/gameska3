#!/bin/bash
target_files=""
output_directory="./out"

declare -a compile_paths=("./src" "./src/gameLib")

POSITIONAL_ARGS=()

clear

#set up flags
keep_output="false"
debug="false"
windows="false"
valg="false"
for flag in $@
do
    case $flag in
        keep) keep_output="true";;
        debug) debug="true";;
        valg) valg="true";;
        windows) windows="true";;
    esac
done


#compile
function compile_file() {
    file_name="${1/.\//}"
    target_name=$(basename $file_name)
    target_name=./$target_name
    target_files+=" ${target_name/.c/.o}"
    
    gcc -c $file_name -I ./src/gameLib
}


for p in "${compile_paths[@]}"; do 
    for f in $p/*.c; do
        compile_file $f
    done
done


#TODO windows
gcc $target_files -o $output_directory/a.out -I ./glib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
mv ./*.o "$output_directory"/


# run
if [ $debug = "true" ]; then
    gdb -ex=r --args "$output_directory"/a.out debug
elif [ $valg = "true" ]; then
    valgrind "$output_directory"/a.out debug
else
    "$output_directory"/a.out
fi
#clean up
if [ $keep_output = "false" ]; then
    rm $output_directory/*.o
    rm $output_directory/*.out
fi
