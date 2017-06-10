set(EXECUTABLE_OUTPUT_PATH ${OUTDIR}/shdl/test)

include_directories(
	${TOPDIR}/shdl/include
	${TOPDIR}/shdl/src
)

link_directories(
)


#################################
add_executable(TestHttp TestHttp.cpp)
target_link_libraries(TestHttp shdl curl)


#################################
add_executable(TestStreamDownload TestStreamDownload.cpp)
target_link_libraries(TestStreamDownload shdl curl)