#!/bin/bash

# Get git information
thisBranch=$(git rev-parse --symbolic-full-name --abbrev-ref HEAD);
topLevelDir=$(git rev-parse --show-toplevel);

tempfile="clang_formatter.tmp";

# Make terminal hrule
width=$(tput cols);
hrule="";
for ((i=0;i<$(($width - 9));i++)); do
    hrule="${hrule}.";
done

# Go through the list of changed files
for f in $(git diff --name-only master $thisBranch); do
    fname="${topLevelDir}/${f}";
    cp $fname $tempfile;
    clang-format-5.0 -i $fname;
    theDiff=$(diff $fname clang_formatter.tmp);
    theString="${f} ${hrule:${#f}}";
    if [ ${#theDiff} -gt 0 ] ; then
        theString="${theString} [FIXED]";
    else
        theString="${theString} [ OK  ]";
    fi
    echo "${theString}";
    rm $tempfile;
done
