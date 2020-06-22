cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CUDA_FLAGS="-arch=sm_70")
set(CMAKE_C_COMPILER "/usr/tcetmp/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/tcetmp/bin/clang++") 


project(gridTime CXX C CUDA)
add_executable(gridTime ./app.cpp)

set(AXOM_DIR /usr/workspace/suarez29/axom/install-lassen-blueos_3_ppc64le_ib_p9-gcc@7.3.1-debug)

find_package(axom REQUIRED
            NO_DEFAULT_PATH
            PATHS ${AXOM_DIR}/lib/cmake) 

target_include_directories(gridTime PRIVATE ${AXOM_INCLUDE_DIRS})

target_link_libraries(gridTime axom)

add_subdirectory(rig)

set_target_properties(rig PROPERTIES LINKER_LANGUAGE CXX)

#target_link_libraries(gridTime Grid_Storage)

target_include_directories(gridTime PUBLIC
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}/rig")

set(ENABLE_CUDA ON CACHE BOOL "")

set(RAJA_ENABLE_CUDA ON CACHE BOOL "")

set(CUDA_TOOLKIT_ROOT_DIR "/usr/tce/packages/cuda/cuda-10.1.243" CACHE PATH "")

set(CMAKE_CUDA_COMPILER "${CUDA_TOOLKIT_ROOT_DIR}/bin/nvcc" CACHE PATH "")

set(CUDA_SEPARABLE_COMPILATION ON CACHE BOOL "")

set(AXOM_ENABLE_ANNOTATIONS ON CACHE BOOL "")

set(AXOM_ENABLE_CUB OFF CACHE BOOL "")

set(AXOM_CUDA_ARCH "sm_60" CACHE PATH "")

set(CMAKE_CUDA_FLAGS "-restrict -arch ${AXOM_CUDA_ARCH} -std=c++11 --expt-extended-lambda -G " CACHE PATH "")

set(CMAKE_CUDA_HOST_COMPILER "${MPI_CXX_COMPILER}" CACHE PATH "")

# nvcc does not like gtest's 'pthreads' flag
set(gtest_disable_pthreads ON CACHE BOOL "")
