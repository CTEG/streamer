include_directories(
	${TOPDIR}/shdl/include
)

file(GLOB_RECURSE HEADERFILES "../include/*")
aux_source_directory(. DIR_SRCS)
add_library(shdl ${DIR_SRCS} ${HEADERFILES})

