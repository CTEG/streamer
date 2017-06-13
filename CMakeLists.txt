CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)

set(TOPDIR ${CMAKE_CURRENT_SOURCE_DIR})

#include(${TOPDIR}/cmake/${TOOLCHAIN}.cmake)

set(OUTDIR ${TOPDIR}/cmake_build/out/)
set(BUILDDIR ${TOPDIR}/cmake_build/build)


#SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

#add_compile_options("--std=c++11")
#add_definitions(-DBUILD_SSL)
#add_compile_options(-DBUILD_SSL)

add_subdirectory(${TOPDIR}/shdl/src ${BUILDDIR}/shdl/src)
add_subdirectory(${TOPDIR}/shdl/test ${BUILDDIR}/shdl/test)

add_subdirectory(${TOPDIR}/yuvconverter/src ${BUILDDIR}/yuvconverter/src)
add_subdirectory(${TOPDIR}/yuvconverter/test ${BUILDDIR}/yuvconverter/test)

add_subdirectory(${TOPDIR}/yuv2h264/src ${BUILDDIR}/yuv2h264/src)
add_subdirectory(${TOPDIR}/yuv2h264/test ${BUILDDIR}/yuv2h264/test)

add_subdirectory(${TOPDIR}/jpg2yuv/test ${BUILDDIR}/jpg2yuv/test)