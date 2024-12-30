#!/bin/bash
target_files=""
output_directory="./out"
src_path="./src"
declare -a compile_paths=()

clear


#find compile paths
function search_for_compile_paths() {
    compile_paths+=" $1"

    
    for entry in "$1"/*
    do
        if [ -d "$entry" ]; then
            search_for_compile_paths "$entry" 
        fi
    done
}

search_for_compile_paths "$src_path"

for test in "$compile_paths"
do 
    echo "$test"
done

POSITIONAL_ARGS=()


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
    
    gcc -c $file_name -I ./src
}


#create out
if [ ! -d "$output_directory" ]; then 
    mkdir "$output_directory"
fi

#TODO windows
gcc $target_files -o $output_directory/a.out -I ./glib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
mv ./*.o "$output_directory"/


# run
if [ $debug = "true" ]; then
    gdb -ex=r --args "$output_directory"/a.out debug
elif [ $valg = "true" ]; then
    valgrind --leak-check=full --show-leak-kinds=definite,possible --track-origins=yes "$output_directory"/a.out 
else
    "$output_directory"/a.out
fi
#clean up
if [ $keep_output = "false" ]; then
    rm $output_directory/*.o
    rm $output_directory/*.out
fi
