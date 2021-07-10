#!/bin/bash


SOURCE_PASCAL="$1"
SOURCE_LOWER="$(echo ${SOURCE_PASCAL,,})"
SOURCE_UPPER="$(echo ${SOURCE_PASCAL^^})"

TARGET_PASCAL="$2"
TARGET_LOWER="$(echo ${TARGET_PASCAL,,})"
TARGET_UPPER="$(echo ${TARGET_PASCAL^^})"

if [[ (! -z "$SOURCE_PASCAL") && (! -z "$TARGET_PASCAL") ]]
then
    echo "Not Empty"
    rename -v "$SOURCE_LOWER" "$TARGET_LOWER" *
    rename -v "$SOURCE_LOWER" "$TARGET_LOWER" resources/*
    rename -v "$SOURCE_LOWER" "$TARGET_LOWER" translations/*
    sed -i -e "s|$SOURCE_PASCAL|$TARGET_PASCAL|g" \
           -e "s|$SOURCE_LOWER|$TARGET_LOWER|g" \
           -e "s|$SOURCE_UPPER|$TARGET_UPPER|g" \
           *.cpp
    sed -i -e "s|$SOURCE_PASCAL|$TARGET_PASCAL|g" \
           -e "s|$SOURCE_LOWER|$TARGET_LOWER|g" \
           -e "s|$SOURCE_UPPER|$TARGET_UPPER|g" \
           *.h
    sed -i -e "s|$SOURCE_PASCAL|$TARGET_PASCAL|g" \
           -e "s|$SOURCE_LOWER|$TARGET_LOWER|g" \
           -e "s|$SOURCE_UPPER|$TARGET_UPPER|g" \
           *.ui
    sed -i -e "s|$SOURCE_PASCAL|$TARGET_PASCAL|g" \
           -e "s|$SOURCE_LOWER|$TARGET_LOWER|g" \
           -e "s|$SOURCE_UPPER|$TARGET_UPPER|g" \
           CMakeLists.txt
    sed -i -e "s|$SOURCE_PASCAL|$TARGET_PASCAL|g" \
           -e "s|$SOURCE_LOWER|$TARGET_LOWER|g" \
           -e "s|$SOURCE_UPPER|$TARGET_UPPER|g" \
           translations/*.desktop.yaml
else
    echo ""
    echo "Usage: ./renameproject.sh <current> <target>"
    echo "<current> and <target> in PascalCase."
    echo ""
    echo "example: ./renameproject.sh Example MainMenu"
fi

# echo "PASCALCASE $PASCALCASE"
# echo "LOWERCASE $LOWERCASE"
# echo "UPPERCASE $UPPERCASE"

# if [ ! -z "$NEWNAME" ]
# then

# fi

