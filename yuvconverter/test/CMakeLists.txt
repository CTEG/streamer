set(EXECUTABLE_OUTPUT_PATH ${OUTDIR}/yuvconverter/test)

include_directories(
	${TOPDIR}/yuvconverter/include
)

link_directories(
)


#################################
add_executable(TestYuvConverter TestYuvConverter.cpp)
target_link_libraries(TestYuvConverter yuvconverter)
