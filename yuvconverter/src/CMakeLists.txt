include_directories(
	${TOPDIR}/yuvconverter/include
)

file(GLOB_RECURSE HEADERFILES "../include/*")
aux_source_directory(. DIR_SRCS)
add_library(yuvconverter ${DIR_SRCS} ${HEADERFILES})

