cmake_minimum_required(VERSION 3.19)
project(scard_lock)

set(CMAKE_CXX_STANDARD 14)

include_directories( "inc_lib" )
link_directories( "inc_lib" )

link_libraries( winscard )

link_libraries( Msimg32 ) #dependencies : TransparentBlt

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

set(SOURCE_FILES
        main_scard_fn.h
        main_scard_fn.cpp
        main_activity_type.h
        main_activity.h
        main_activity.cpp
        main_draws.h
        main_draws.cpp
        main_include.h
        main_fn.h
        main.h
        main_fn.cpp
        main.cpp
        )


file(GLOB_RECURSE RESOURCE_LIST "./resource/*.bmp" "./resource/*.jpg" "./resource/*.png")
set(RESOURCE_BASE_PATH "resource")
set(RESOURCE_AC_PATH)
set(RESOURCE_DEF_PATH)
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    foreach(resource_buffer IN LISTS RESOURCE_LIST)
        get_filename_component(FN "${resource_buffer}" NAME)
        list(APPEND RESOURCE_AC_PATH "./${RESOURCE_BASE_PATH}/${FN}")
        list(APPEND RESOURCE_DEF_PATH "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_BASE_PATH}/${FN}")
        add_custom_command(
                COMMENT "resource copy"
                OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_BASE_PATH}/${FN}"
                COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_BASE_PATH}/${FN}" "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_BASE_PATH}/${FN}"
                DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_BASE_PATH}/${FN}"
        )
        message(STATUS +RESOURCE-INPUT : "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_BASE_PATH}/${FN} ==>( MUST BE PLACED ON )==> ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_BASE_PATH}/${FN}")
    endforeach()
elseif()
    message(STATUS DO-NOT!)
endif()

# make _resource_path.h and append source file!
set(i 0)
set(file_of_resource_file_name "./_resource_path.h")
file(WRITE "${file_of_resource_file_name}" "// AUTO-CREATED DEFINITION HEADER FILE BY DEVELOPER WRITEN CMAKE-LISTS\n")
foreach(filename ${RESOURCE_AC_PATH})
    message(STATUS "header writing : RESOURCE_FILE_${i} = ${filename}")
    file(APPEND "${file_of_resource_file_name}" "#define RESOURCE_FILE_${i} \"${filename}\"\n")
    MATH(EXPR i "${i}+1")
endforeach(filename)
list(APPEND SOURCE_FILES ${file_of_resource_file_name})
unset(i)



# RESOURCE_COPY
add_custom_target(scard_resources_copy ALL DEPENDS ${RESOURCE_DEF_PATH})
# RESOURCE_HEADER WRITING
add_custom_target(scard_resources_header_write DEPENDS "${file_of_resource_file_name}")
add_dependencies(scard_resources_copy scard_resources_header_write)

add_executable(scard_lock WIN32 ${SOURCE_FILES})
unset(file_of_resource_file_name)
