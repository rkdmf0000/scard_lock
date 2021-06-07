cmake_minimum_required(VERSION 3.19)
project(scard_lock)

set(CMAKE_CXX_STANDARD 14)

include_directories( "./inc_lib" )
link_directories( "./inc_lib" )

#include_directories( "A:/mingw_w64/mingw32/i686-w64-mingw32/include" )
#link_directories( "C:/Program Files%20(x86)/Windows Kits/10/Lib/10.0.18362.0/um/x64" )
link_libraries( winscard )


set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(scard_lock WIN32 main.h main.cpp)