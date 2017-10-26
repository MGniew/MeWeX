set(DIGGER_SRCS
	Config.cpp
	Digger.cpp
	main.cpp)
add_executable(Digger ${DIGGER_SRCS})
target_link_libraries(Digger ${LIBS})
