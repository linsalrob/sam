cmake_minimum_required(VERSION 3.13)
project(sam_length)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(sam sam_len.cpp)


set(SOURCE_FILES main.c)
add_executable(sam_length ${SOURCE_FILES})
install (TARGETS sam_length DESTINATION bin)

        #g++ -o sam.out   -Ihtslib -Lhtslib  main.cpp  /usr/lib/x86_64-linux-gnu/libhts.a -lz -lpthread -lcurl -lbz2 -llzma -lcurl -lcrypto