cmake_minimum_required(VERSION 3.6.0)
project(CppChat VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME CppChat)

set(CXX_FLAGS 
	-g -std=c++20
    -Wall -pedantic -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow
	-Wsign-conversion -Wsign-compare -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused
	-D_GLIBCXX_DEBUG)

#profiles
include_directories(${PROJECT_SOURCE_DIR}/src/profiles)
file(GLOB PROFILES ${PROJECT_SOURCE_DIR}/src/profiles/*.cpp)
file(GLOB PROFILES_H ${PROJECT_SOURCE_DIR}/src/profiles/*.h)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
	set(SUBSYSTEM "WIN32")
	add_definitions ( -DRELEASE=1 )
endif (${CMAKE_BUILD_TYPE} STREQUAL "Release")

add_executable(${EXECUTABLE_NAME} ${SUBSYSTEM} src/main.cpp src/basic.cpp ${PROFILES} ${PROFILES_H} ${PROTO_SRCS} ${PROTO_HDRS})

## LIBS

#protobuf
find_package(Protobuf CONFIG REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SRC_PROTOS ${PROJECT_SOURCE_DIR}/src/protos/*.proto)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${SRC_PROTOS})

target_link_libraries(${EXECUTABLE_NAME} ${Protobuf_LIBRARIES}) 

#sfml
find_package(SFML 2.5 CONFIG REQUIRED COMPONENTS graphics) 
include_directories(${PROJECT_SOURCE_DIR}/lib/SFML/include)
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

file(COPY ${PROJECT_SOURCE_DIR}/lib/SFML/bin/${GRAPHICS_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/lib/SFML/bin/${SYSTEM_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/lib/SFML/bin/${WINDOW_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})