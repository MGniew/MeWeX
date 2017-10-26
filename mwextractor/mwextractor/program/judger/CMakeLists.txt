set(JUDGER_SRCS
	Config.cpp
	Judger.cpp
	main.cpp)
add_executable(Judger ${JUDGER_SRCS})
target_link_libraries(Judger ${LIBS})
