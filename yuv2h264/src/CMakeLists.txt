include_directories(
	${TOPDIR}/yuv2h264/include
	${TOPDIR}/3rdparty/include/x264
)

file(GLOB_RECURSE HEADERFILES "../include/*")
aux_source_directory(. DIR_SRCS)
add_library(yuv2h264 ${DIR_SRCS} ${HEADERFILES})

