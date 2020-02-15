cmake_minimum_required(VERSION 3.14)
project(20S-PA02-AutoIndexer)
set (EXE_NAME AutoIndexer)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....
# if you need more, add them here and in the foreach stmt below.
set (input01 "bookInput.txt")
set (input02 "wordsInput.txt")
set (input03 "")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 17)
add_executable(${EXE_NAME} main.cpp DSVector.h DSString.cpp DSString.h)
