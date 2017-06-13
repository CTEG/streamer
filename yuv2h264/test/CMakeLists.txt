set(EXECUTABLE_OUTPUT_PATH ${OUTDIR}/yuv2h264/test)

include_directories(
	${TOPDIR}/yuv2h264/src
	${TOPDIR}/yuv2h264/include
	${TOPDIR}/3rdparty/include/x264
)

link_directories(
	${TOPDIR}/3rdparty/libs/x264
)


#################################
add_executable(TestX264Encoder TestX264Encoder.cpp VideoCapture.cpp)
target_link_libraries(TestX264Encoder yuv2h264 x264 pthread dl)
