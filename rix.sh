#!/bin/bash
#   THIS SCRIPT FILE WILL REPLACE YOUR CURRENT "rix.sh" FILE
#   IN THE COMPILED RIX FOLDER
RIX_HOME_=${RIX_HOME:-.}
RIX_FILE=${1}

#Grab the rix file's fullpath and directory
RIX_FILE_PATH=$( realpath "$RIX_FILE" )
RIX_FILE_DIR=$( dirname "$RIX_FILE" )

#Creates a test.rit.h  /  test.rit.c  / test.rit.log  / test.rit.sh  / rix_temp_file.rit

#Tyler's modifications
${RIX_HOME}/rixc -q -o ${RIX_FILE_PATH} ${RIX_FILE}
echo "$RIX_FILE"
if [ $? -eq 0 ]; then
	chmod +x ./${RIX_FILE}.sh
	./${RIX_FILE}.sh
fi
shift
./${RIX_FILE}.out $@
rm ${RIX_FILE}.out ${RIX_FILE}.c ${RIX_FILE}.h ${RIX_FILE}.sh ${RIX_FILE}.log
rm "rix_temp_file.rit"

#ORIGINAL CODE BELOW
#${RIX_HOME}/rixc -q -o ${RIX_FILE} ${RIX_FILE}
#if [ $? -eq 0 ]; then
#	chmod +x ./${RIX_FILE}.sh
#	./${RIX_FILE}.sh
#fi
#shift
#./${RIX_FILE}.out $@
#rm ${RIX_FILE}.out ${RIX_FILE}.c ${RIX_FILE}.h ${RIX_FILE}.sh ${RIX_FILE}.log
