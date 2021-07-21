cmake_minimum_required(VERSION 3.6.0)
project(CppChat VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(root_folder ${PROJECT_SOURCE_DIR}/src)
set(lib_folder ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_NAME CppChat)

set(CXX_FLAGS 
	-g -std=c++20
    -Wall -pedantic -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow
	-Wsign-conversion -Wsign-compare -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused
	-D_GLIBCXX_DEBUG)

#imgui
set(IMGUI_SOURCES 
		${lib_folder}/imgui/imgui.cpp 
		${lib_folder}/imgui/imgui_tables.cpp 
		${lib_folder}/imgui/imgui_widgets.cpp 
		${lib_folder}/imgui/imgui_draw.cpp 
		${lib_folder}/imgui/imgui_demo.cpp 
		${lib_folder}/imgui/imgui-SFML.cpp
	)

#profiles
include_directories(${root_folder}/profiles)
file(GLOB PROFILES ${root_folder}/profiles/*.cpp)
file(GLOB PROFILES_H ${root_folder}/profiles/*.h)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
	set(SUBSYSTEM "WIN32")
	add_definitions ( -DRELEASE=1 )
endif (${CMAKE_BUILD_TYPE} STREQUAL "Release")

add_executable(${EXECUTABLE_NAME} ${SUBSYSTEM} ${root_folder}/main.cpp ${root_folder}/basic.cpp ${PROFILES} ${PROFILES_H} ${PROTO_SRCS} ${PROTO_HDRS} ${IMGUI_SOURCES})

## LIBS
#openGL
find_package(OpenGL REQUIRED)
if(NOT OpenGL_OpenGL_FOUND)
    message(WARNING "OpenGL not found!\n")
endif()
target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})

#protobuf
find_package(Protobuf CONFIG REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SRC_PROTOS ${root_folder}/protos/*.proto)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${SRC_PROTOS})

target_link_libraries(${EXECUTABLE_NAME} ${Protobuf_LIBRARIES}) 

#sfml
find_package(SFML 2.5 CONFIG REQUIRED COMPONENTS graphics) 
include_directories(${lib_folder}/SFML/include)
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics)
set(GRAPHICS_DLL sfml-graphics-d-2.dll)
set(SYSTEM_DLL sfml-system-d-2.dll)
set(WINDOW_DLL sfml-window-d-2.dll)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
	message("Release mode")
	set(GRAPHICS_DLL sfml-graphics-2.dll)
	set(SYSTEM_DLL sfml-system-2.dll)
	set(WINDOW_DLL sfml-window-2.dll)
endif (${CMAKE_BUILD_TYPE} STREQUAL "Release")

file(COPY ${lib_folder}/SFML/bin/${GRAPHICS_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${lib_folder}/SFML/bin/${SYSTEM_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${lib_folder}/SFML/bin/${WINDOW_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#imgUI
include_directories(${lib_folder}/imgui)
target_link_libraries(${EXECUTABLE_NAME} -limm32)