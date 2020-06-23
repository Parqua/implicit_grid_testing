cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_COMPILER "/usr/tcetmp/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/tcetmp/bin/clang++") 
set(CMAKE_CUDA_HOST_COMPILER "${CMAKE_CXX_COMPILER}" CACHE PATH "")
set(CUDA_TOOLKIT_ROOT_DIR "/usr/tce/packages/cuda/cuda-10.1.243" CACHE PATH "")
set(CMAKE_CUDA_COMPILER "${CUDA_TOOLKIT_ROOT_DIR}/bin/nvcc" CACHE PATH "")
set(CUDA_ARCH "sm_60" CACHE STRING "")
set(CMAKE_CUDA_FLAGS "-restrict -arch ${CUDA_ARCH} -std=c++11" CACHE STRING "")
set(CMAKE_CUDA_LINK_FLAGS "-Xlinker -rpath -Xlinker /usr/tce/packages/spectrum-mpi/ibm/spectrum-mpi-rolling-release/lib" CACHE STRING "")
set(CUDA_LINK_WITH_NVCC ON CACHE BOOL "")
set(CUDA_SEPARABLE_COMPILATION ON CACHE BOOL "")
set(gtest_disable_pthreads ON CACHE BOOL "")

project(gridTime CXX C CUDA)
set(ENABLE_CUDA ON CACHE BOOL "")
include(blt/SetupBLT.cmake)

#add_subdirectory(rig)

set(AXOM_DIR /usr/workspace/suarez29/axom/install-lassen-blueos_3_ppc64le_ib_p9-gcc@7.3.1-debug)

find_package(axom REQUIRED
            NO_DEFAULT_PATH
            PATHS ${AXOM_DIR}/lib/cmake) 

blt_add_executable(NAME    gridTime
                   SOURCES app.cpp
                   DEPENDS_ON axom rig cuda)

