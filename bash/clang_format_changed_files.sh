#!/bin/bash

thisBranch=$(git rev-parse --symbolic-full-name --abbrev-ref HEAD);

for f in $(git diff --name-only master $thisBranch); do
   clang-format-5.0 -i $f;
done

