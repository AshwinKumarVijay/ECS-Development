#!/bin/bash
# find the number of lines for this project, not including ./include/*
find . \( -iname "*.h" -o -iname "*.hpp" -o -iname "*.cpp" \) -not -ipath "./include/*" -print0 | xargs -0 wc -l
