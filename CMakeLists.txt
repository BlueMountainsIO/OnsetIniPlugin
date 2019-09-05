cmake_minimum_required(VERSION 3.1)
project(ini-plugin VERSION 1.0)


list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

if(UNIX)
	# hide non-exported symbols
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)


set(HORIZONSDK_ROOT_DIR "${PROJECT_SOURCE_DIR}/libs/sdk")
find_package(HorizonPluginSDK REQUIRED)

# ini library
set(DEP_INI_SRC_FOLDER "${PROJECT_SOURCE_DIR}/libs/mini")
add_library(ini-lib INTERFACE)

target_include_directories(ini-lib INTERFACE ${DEP_INI_SRC_FOLDER}/src)
# ini library end

add_subdirectory(src)
