#!/bin/bash
target_files=""
output_directory="./out"
src_path="./src"
declare -a compile_paths=()

clear


#find compile paths
function search_for_compile_paths() {
    compile_paths+=("$1")

    
    for entry in "$1"/*
    do
        if [ -d "$entry" ]; then
            search_for_compile_paths "$entry" 
        fi
    done
}

# section break ================================
echo done searching for fompile paths
# ==============================================


search_for_compile_paths "$src_path"

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


# section break ================================
echo arg setup complete
# ==============================================


#compile
function compile_file() {
    file_name="${1/.\//}"
    target_name=$(basename $file_name)
    target_name=./$target_name
    
    if [[ $1 == *.c ]]; then 
        target_files+=" ${target_name/.c/.o}"
    elif [[ $1 == *.h ]]; then 
        target_files+=" ${1/.c/.o}"
    fi
    
    gcc -c $file_name -I ./src
}


for path in "${compile_paths[@]}" 
do
    for file in "$path"/* 
    do 
        if [[ -f $file ]]; then
            compile_file "$file"
        fi
    done
done

# section break ================================
echo precompile done
# ==============================================


#create out
if [ ! -d "$output_directory" ]; then 
    mkdir "$output_directory"
fi


# section break ================================
echo output initialized
# ==============================================


#TODO windows
gcc $target_files -o $output_directory/a.out -I ./glib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
mv ./*.o "$output_directory"/


# section break ================================
echo compile done
# ==============================================

# run
if [ $debug = "true" ]; then
    gdb -ex=r --args "$output_directory"/a.out debug
elif [ $valg = "true" ]; then
    valgrind --leak-check=full --show-leak-kinds=definite,possible --track-origins=yes "$output_directory"/a.out 
else
    "$output_directory"/a.out
fi
clean up
if [ $keep_output = "false" ]; then
    rm $output_directory/*.o
    rm $output_directory/*.out
fi
#clean up accidental gch files
find . -type f -name '*.*.gch' -print -delete

# section break ================================
echo build complete
# ==============================================
