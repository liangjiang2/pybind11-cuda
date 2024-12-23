cmake minimum_required(VERSION 3.11)
project(pydemo)
find package(CUDA REQUIRED)# 启用CUDA语言
enable language(CUDA)
#包含目录
include directories(${CMAKE_SOURCE_DIR})# 假设hello.h在include目录下
file(GLOB CUDA_SRC
	"${CMAKE_SOURCE_DIR}/* .cu'
)
add_executable(test main.cpp ${CUDA_SRC})

execute_process(COMMAND python -m pybind11 --includes OUTPUT_VARIABLE PYBIND_INCLUDE_FLAG)
string(STRIP ${PYBIND_INCLUDE_FLAG} PYBIND_INCLUDE_FLAG)
set(CMAKE_CXX_FLAGS " -O2-g -Wall -std=c++11 -pthread -fPIC -fopenmp -w -pipe -fpermissive ${CMAKE_CXX_FLAGS} ${PYBIND_INCLUDE_FLAG} ")

set(EXTRA_LIBS ${EXTRA_LIBS} cuda cudart)
execute_process(COMMAND python3-config --extension-suffix OUTPUT_VARIABLE PYTHON_VERSION)

Set(PROJ_NAME "PYDEMO${PYTHON_VERSION}")
string(STRIP ${PROJ_NAME} PROJ_NAME)
string(REPLACE ".so" "" PROJ_NAME "${PROJ_NAME}")
Message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
set(REPO_ROOT ${PROJECT_SOURCE_DIR}/..)
file(STRINGS "${REPO_ROOT}/VERSION_NUMBER" INFER_VERSION)
add_library(${PROJ_NAME} SHARED pybind.cpp ${CUDA SRC})
target_link_libraries(${PROJ_NAME} ${EXTRA_LIBS} )
set(PATH ${PROJECT_SOURCE_DIR})
set_target_properties(${PROJ_NAME}
	PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PATH}
	PREFIX""
	OUTPUT_NAME ${PROJ_NAME}
)
