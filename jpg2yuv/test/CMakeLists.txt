set(EXECUTABLE_OUTPUT_PATH ${OUTDIR}/jpg2yuv/test)

include_directories(
	${TOPDIR}/jpg2yuv/include
	${TOPDIR}/3rdparty/include/libjpeg-turbo
)

link_directories(
	${TOPDIR}/3rdparty/libs/libjpeg-turbo
)


#################################
add_executable(TestJpg2RGB TestJpg2RGB.cpp)
target_link_libraries(TestJpg2RGB jpeg)