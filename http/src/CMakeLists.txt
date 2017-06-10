include_directories(
	${TOPDIR}/http/include
)

file(GLOB_RECURSE HEADERFILES "../include/*")
aux_source_directory(. DIR_SRCS)
add_library(httpdl ${DIR_SRCS} ${HEADERFILES})

