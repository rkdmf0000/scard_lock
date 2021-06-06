cmake_minimum_required(VERSION 3.19)
project(scard_lock)

set(CMAKE_CXX_STANDARD 14)

link_directories( "C:/Program%20Files%20(x86)/Windows%20Kits/10/Lib/10.0.18362.0/um/x64" )
link_libraries( winscard )
include_directories( "A:/mingw_w64/mingw32/i686-w64-mingw32/include" )

add_executable(scard_lock WIN32 main.cpp)