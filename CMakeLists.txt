# CMakeList.txt : CMake project for TCPClientTutorial, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.17)

project ("TCPClientTutorial" LANGUAGES CXX VERSION 1.0)

find_program(CMAKE_CUDA_COMPILER nvcc)
find_package(CUDA REQUIRED)
set(CUDAToolkitDir "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.1/")
include_directories( ${CUDA_INCLUDE_DIRS} )
enable_language(CUDA)

file(GLOB cpu_source_files "${CMAKE_SOURCE_DIR}/*.cpp")
file(GLOB gpu_source_files "${CMAKE_SOURCE_DIR}/*.cu")
file(GLOB cpu_header_files "${CMAKE_SOURCE_DIR}/*.h")
file(GLOB gpu_header_files "${CMAKE_SOURCE_DIR}/*.cuh")

# Add source to this project's executable.
add_executable (TCPClientTutorial ${cpu_source_files} ${cpu_header_files} ${gpu_source_files} ${gpu_header_files})

# TODO: Add tests and install targets if needed.
