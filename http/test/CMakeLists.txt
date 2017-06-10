set(EXECUTABLE_OUTPUT_PATH ${OUTDIR}/http/test)

include_directories(
	${TOPDIR}/http/include
	${TOPDIR}/http/src
)

link_directories(
)


#################################
add_executable(TestHttp TestHttp.cpp)
target_link_libraries(TestHttp httpdl curl)


#################################
add_executable(TestStreamDownload TestStreamDownload.cpp)
target_link_libraries(TestStreamDownload httpdl curl)