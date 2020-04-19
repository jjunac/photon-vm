#!/bin/bash

TESTDIR="samples"
BINARY=bin/strix

in_files="$TESTDIR/*.pasm"
nb_files=$(ls -l $in_files | wc -l)

echo -e "\e[32m#==========#\e[0m Running $nb_files tests"

nb_ran=0
nb_failed=0

start=$(date +%s%N)

for f in $in_files; do
    echo -e "\e[32m# RUN      #\e[0m $f"
    out_file=$(echo "$f" | sed s/.pasm/.out/)
    case_start=$(date +%s%N)
    if $BINARY $f | diff --color $out_file -; then
        echo -e "\e[32m#       OK #\e[0m $out_file ($((( ($(date +%s%N) - case_start) / 1000000 ))) ms)"
    else
        echo -e "\e[31m#  FAILED  #\e[0m $out_file ($((( ($(date +%s%N) - case_start) / 1000000 ))) ms)"
        ((nb_failed++))
    fi
    ((nb_ran++))
done

echo -e "\e[32m#==========#\e[0m Ran $nb_ran tests for $1 ($((( ($(date +%s%N) - start) / 1000000 ))) ms total)"
echo -e "\e[32m#  PASSED  #\e[0m $(((nb_ran-nb_failed))) tests"

if [[ $nb_failed > 0 ]]; then
    echo -e "\e[31m#  FAILED  #\e[0m $nb_failed tests"
fi
